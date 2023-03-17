/**
    @file syntax.h
    @author Cole Sanders (cgsande2)
    Provides functionality to determine if a string is a valid identifier and flag an integer array corresponding to the
    characters on a line determining which should be highlighted and which should not.
  */

/** 
    Takes in a string and returns true if it counts as a valid identifier and false otherwise.
    @param ident a null terminating character array of the letters of the identiiers.
    @return true if the string is a valid id.
  */
_Bool validIdentifier( char ident[] );

/** 
    Marks the corresponding elements of the color array with the highlighted color for each character in the
    input line that is in the identifier.
    @param word a character array containing the identifier
    @param line a character array containing the input line
    @param color an integer array that will flag which characters need to be printed in which color
    @return true if an identifier is found and colored from the input line.
  */
_Bool markIdentifier( char word[], char line[], int color[] );
