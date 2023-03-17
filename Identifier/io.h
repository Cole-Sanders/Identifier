/**
    @file io.c
    @author Cole Sanders (cgsande2)
    Provides functionality to read in a line from the input file, count the number of lines in the input file, and
    print out a line with the correct highlighting for each character.
  */
#include <stdio.h>
#include <stdbool.h>

/** Maximum length of an input line. */
#define LINE_LIMIT 100

/** Used for element of the output line in the default color. */
#define DEFAULT_COLOR 0

/** Used for element of the output line colored like that target identifier. */
#define IDENT_COLOR 1

/** For the extra credit, this is the color value for operators  */
#define OP_COLOR 2

/** 
    Takes in a file pointer and returns the number of lines in that file. If the line is over the line length limit
    the program exits and prints a messege to standard error.
    @param fp a file pointer that points to the input file.
    @return the number of lines in the file.
  */
int countLines( FILE *fp );

/** 
    Reads a line from a file into a character array. Returns true if there is something to read,
    false if there is nothing left to read in the file.
    @param fp a file pointer to the input flie.
    @param line a character array to be filed with the contents of the file line.
    @return true if the file had something left to read. False otherwise.
  */
bool readLine( FILE *fp, char line[ LINE_LIMIT + 1 ] );

/** 
    Prints a given character array to output with the correct highlighting.
    @param line character array to be printed.
    @param color integer array flagging corresponding elements of the character array to highlight.
  */
void printLine( char line[ LINE_LIMIT + 1 ], int color[ LINE_LIMIT ] );
