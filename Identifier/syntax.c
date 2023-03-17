/**
    @file syntax.c
    @author Cole Sanders (cgsande2)
    Provides functionality to determine if a string is a valid identifier and flag an integer array corresponding to the
    characters on a line determining which should be highlighted and which should not.
  */
#include "syntax.h"
#include <string.h>
#include "io.h"


bool validIdentifier( char ident[] )
{
  if (  ident[ 0 ] != '_' && !( ident[ 0 ] >= 'A' && ident[ 0 ] <= 'Z' ) && !( ident[ 0 ] >= 'a' && ident[ 0 ] <= 'z' )) {
    return false;
  }
  int index = 0;
  while ( ident[ index ] ) {
    if ( ident[ index ] != '_' && !( ident[ index ] >= '0' && ident[ index ] <= '9' ) && !( ident[ index ] >= 'A' && ident[ index ] <= 'Z' ) && !( ident[ index ] >= 'a' && ident[ index ] <= 'z' )) {
      return false;
    }
    ++index;
  }
  return true;
}


bool markIdentifier( char word[], char line[], int color[] )
{
  //Set the color array values to 0 by default
  int lineIdx = 0;
  while ( line[ lineIdx ] ) {
    color[ lineIdx ] = DEFAULT_COLOR;
    ++lineIdx;
  }
  lineIdx = 0;
  
  
  int wordLen = 0;
  bool identFound = false;
  while ( word[ wordLen ] ) {
    ++wordLen;
  }
  char afterMatch[] = { line[ lineIdx + wordLen ], '\0' };
  if ( strncmp( word, &(line[ lineIdx ]), wordLen ) == 0 && !validIdentifier( afterMatch ) ) {
    for ( int i = 0; i < wordLen; ++i ) {
        color[ i + lineIdx ] = IDENT_COLOR;
        if ( i == wordLen - 1 ) {
          identFound = true;
        }
    }
  }
  
  while ( line[ lineIdx ] ) {
    char beforeMatch[] = { line[ lineIdx - 1 ], '\0'};
    char afterMatch[] = { line[ lineIdx + wordLen ], '\0' };
    if ( strncmp( word, &(line[ lineIdx ]), wordLen ) == 0 && !validIdentifier( beforeMatch ) && !validIdentifier( afterMatch ) ) {
      for ( int i = 0; i < wordLen; ++i ) {
        color[ i + lineIdx ] = IDENT_COLOR;
        if ( i == wordLen - 1 ) {
          identFound = true;
        }
      }
    }
    ++lineIdx;
  }
  return identFound;
}
