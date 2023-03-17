/**
    @file io.c
    @author Cole Sanders (cgsande2)
    Provides functionality to read in a line from the input file, count the number of lines in the input file, and
    print out a line with the correct highlighting for each character.
  */
#include "io.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
/** The exit status code number for a file line that is too long */
#define LONG_LINE 1
/** The first number in the color red's escape sequence */
#define RED_ONE 0x1b
/** The second number in the color red's escape sequence */
#define RED_TWO 0x5b
/** The third number in the color red's escape sequence */
#define RED_THREE 0x33
/** The fourth number in the color red's escape sequence */
#define RED_FOUR 0x31
/** The fifth number in the color red's escape sequence */
#define RED_FIVE 0x6d
/** The first number in the default color's escape sequence */
#define DEFAULT_ONE 0x1b
/** The second number in the default color's escape sequence */
#define DEFAULT_TWO 0x5b
/** The third number in the default color's escape sequence */
#define DEFAULT_THREE 0x30
/** The fourth number in the default color's escape sequence */
#define DEFAULT_FOUR 0x6d


int countLines( FILE *fp )
{
  int lines = 0;
  int lineLen = 0;
  char ch = fgetc( fp );
  while ( ch != EOF ) {
    ++lineLen;
    if ( lines == 0 ) {
      ++lines;
    }
    if ( ch == '\n' ) {
      ++lines;
      lineLen = 0;
    }
    if ( lineLen > LINE_LIMIT ) {
      fprintf( stderr, "Input line too long\n" );
      exit( LONG_LINE );
    }
    ch = fgetc( fp );
  }
  rewind( fp );
  return lines;
}


bool readLine( FILE *fp, char line[ LINE_LIMIT + 1 ] )
{
  char ch = fgetc( fp );
  if ( ch == EOF ) 
    return false;
  int index = 0;
  while ( ch != EOF && ch != '\n' ) {
    line[ index ] = ch;
    ++index;
    ch = fgetc( fp );
  }
  line[ index ] = '\0';
  return true;
}


void printLine( char line[ LINE_LIMIT + 1 ], int color[ LINE_LIMIT ] )
{
  char red[] = { RED_ONE, RED_TWO, RED_THREE, RED_FOUR, RED_FIVE, '\0' };
  char regular[] = { DEFAULT_ONE, DEFAULT_TWO, DEFAULT_THREE, DEFAULT_FOUR, '\0' };
  int index = 0;
  while ( line[ index ] ) {
    if ( color[ index ] == DEFAULT_COLOR && index > 0 && color[ index - 1 ] == IDENT_COLOR ) {
      printf( "%s" , regular );
    } else if ( color[ index ] == IDENT_COLOR && ( index == 0 || color[ index - 1 ] == DEFAULT_COLOR )) {
      printf( "%s" , red );
    }
    putchar( line[ index ] );
    ++index;
  }
  if ( color[ index - 1 ] == IDENT_COLOR ) 
    printf( "%s" , regular );
  putchar( '\n' );
}
