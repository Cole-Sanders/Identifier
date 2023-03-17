/**
    @file ident.c
    @author Cole Sanders (cgsande2)
    Scans an input file for occurances of a user picked identifier. It prints out the line with the identifier highlighted
    in red along with the options to print context lines around the identifier as well as to number the lines being printed.
  */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "io.h"
#include "syntax.h"

/** Number of arguments required on the command line. */
#define REQUIRED_ARGS 2
/** Exit status number for the program if it has the wrong number of command line arguments */
#define BAD_ARGS 1
/** Exit status number for the program if it has an invalid identifier */
#define BAD_ID 1
/** Exit status number for the program if it cannot read the input file */
#define BAD_FILE 1
/** The distace from the last command argument at which the file should be found */
#define FILE_OFFSET 2
/** The required number to move a number to the next places coloum from multiplication */
#define PLACE_CHANGER 10

/** Lines of context to show around an identifier. */
static int context = 0;

/** True if we're printing line numbers. */
static bool numbers = false;
  
/** True if we're showing operators (for the extra credit). */
//static bool operators = false;

/** 
    Error checks all of the command line arguments except for the input file
    and identifier.
  */
static void processArgs( int argc, char *argv[] )
{
  if ( argc < REQUIRED_ARGS + 1 ) {
    fprintf( stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n" );
    exit( BAD_ARGS );
  }
  int cIdx = 0;
  for ( int i = 1; i < argc - FILE_OFFSET; ++i ) {
    int idx = 0;
    bool numArray = true;
    while ( argv[ i ][ idx ] ) {
      if ( argv[ i ][ idx ] < '0' || argv[ i ][ idx ] > '9' )
        numArray = false;
      ++idx;
    }
    if ( strcmp(argv[ i ], "-n") == 0 ) {
      numbers = true;
    } else if ( strcmp(argv[ i ], "-c") == 0 ) {
      cIdx = i;
    } else if ( !numArray ) {
      fprintf( stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n" );
      exit( BAD_ARGS );
    }
  }
  
  if ( cIdx ) {
    int idx = 0;
    bool numArray = true;
    while ( argv[ cIdx + 1 ][ idx ] ) {
      if ( argv[ cIdx + 1 ][ idx ] < '0' || argv[ cIdx + 1 ][ idx ] > '9' )
        numArray = false;
      ++idx;
    }
    if ( !numArray ) {
      fprintf( stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n" );
      exit( BAD_ARGS );
    } else {
      int number = 0;
      int idx = 0;
      while ( argv[ cIdx + 1][ idx ] ) {
        number = number * PLACE_CHANGER;
        number += argv[ cIdx + 1 ][ idx ] - '0';
        ++idx;
      }
      context = number;
    }
  }
}

/** 
    Takes a file, identifier and context and numbering commands from the command line
    and prints out the lines containing the identifier, along with context or numbering
    if needed.
    @return program exit status
  */
int main( int argc, char *argv[] )
{
  //Error checks all the args but the filename and identifier
  processArgs( argc, argv );
  
  //Error checks the filename
  FILE *fp = fopen( argv[ argc - FILE_OFFSET ], "r" );
  if ( !fp ) {
    fprintf( stderr, "Can't open file: %s\n", argv[ argc - FILE_OFFSET ] );
    exit( BAD_FILE );
  }
  
  //Error checks the identifier
  if ( !validIdentifier( argv[ argc - 1 ] ) ) {
    fprintf( stderr, "Invalid identifier: %s\n", argv[ argc - 1 ] );
    exit( BAD_ID );
  }
  
  //Gets the number of lines in the file
  int numLines = countLines( fp );
  
  //Counts the maximum number of decimal places to print the lines
  int numZeros = 1;
  int moreZeros = numLines;
  while ( moreZeros >= 1 ) {
    moreZeros = moreZeros / PLACE_CHANGER;
    ++numZeros;
  }
  
  
  //Holds a memory of past lines plus the last index of the current line
  char contextField[ context + 1 ][ LINE_LIMIT + 1 ];
  
  int lineIdx = 0;
  char line[ LINE_LIMIT + 1 ];
  int color[ LINE_LIMIT ] = { 0 };
  int defaultColor[ LINE_LIMIT ] = { 0 };
  
  //Counts the number of context lines read in to print
  int contextCount = 0;
  
  //Iterates through the lines
  while ( readLine( fp, line ) ) {
    
    //Shift the contents of the context array over to hold the new line
    if ( context != 0 ) {
      for ( int i = 1; i <= context; ++i ) {
        strcpy( contextField[ i - 1 ], contextField[ i ] );
      }
      if ( contextCount <= context )
        ++contextCount;
    }
    
    //Check if the processed line has a copy of the identifier
    bool identLine = markIdentifier( argv[ argc - 1 ], line, color );
    
    //Copy the line to the last index of the contents array
    strcpy( contextField[ context ], line );
    
    ++lineIdx;
    
    //If the line contained an identifier, print out the context lines around it
    if ( identLine ) {
      
      //Print the context lines before the identifier
      if ( context != 0 ) {
        int contextIterator = context + 1 - contextCount;
        int numberPrinter = lineIdx - contextCount + 1;
        while ( contextCount > 1 && context != 0) {
          
          //If -n was used, print out the numbers for each line
          if ( numbers ) {
            int numDigits = 1;
            int moreDigits = numberPrinter;
            while ( moreDigits >= 1 ) {
              ++numDigits;
              moreDigits = moreDigits / PLACE_CHANGER;
            }
            for ( int i = 0; i < numZeros - numDigits; ++i ) {
              putchar( ' ' );
            }
            printf( "%d: " , numberPrinter );
            ++numberPrinter;
          }
          
          printLine( contextField[ contextIterator ], defaultColor );
          ++contextIterator;
          --contextCount;
        }
      }
      
      //If -n was used, print out the numbers for the identifier line
      if ( numbers ) {
        int numDigits = 1;
        int moreDigits = lineIdx;
        while ( moreDigits >= 1 ) {
          ++numDigits;
          moreDigits = moreDigits / PLACE_CHANGER;
        }
        for ( int i = 0; i < numZeros - numDigits; ++i ) {
          putchar( ' ' );
        }
        printf( "%d: " , lineIdx );
      }
      
      //Print the identifier line
      printLine( contextField[ context ], color );
      
      //Print out the lines after the identifier line
      if ( context != 0 ) {
        bool secondIdent = false;
        int contextIdx = 0;
        while ( contextIdx < context && readLine( fp, line )) {
          
          ++lineIdx;
          
          //Check if there is another identifer line in the context lines
          secondIdent = markIdentifier( argv[ argc - 1 ], line, color );
          
          //Shift the previous context lines to account for the new line
          for ( int i = 1; i <= context; ++i ) {
            strcpy( contextField[ i - 1 ], contextField[ i ] );
          }
          
          //Set the new line at the end of the context field
          strcpy( contextField[ context ], line );
          
          //If -n was used, print the number before the lines
          if ( numbers ) {
            int numDigits = 1;
            int moreDigits = lineIdx;
            while ( moreDigits >= 1 ) {
              ++numDigits;
              moreDigits = moreDigits / PLACE_CHANGER;
            }
            for ( int i = 0; i < numZeros - numDigits; ++i ) {
              putchar( ' ' );
            }
            printf( "%d: " , lineIdx );
          }
          
          //If an identifer line was printed, reset the context line counter and keep printing
          if ( secondIdent ) {
            contextIdx = 0;
            printLine( line, color );
          } else {
            printLine( line, defaultColor );
            ++contextIdx;
          }
        }
      }
      
    }
  }
  
  return EXIT_SUCCESS;
}
