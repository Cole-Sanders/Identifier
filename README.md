# Identifier
Scans a text file to find instances of a chosen word

How it works:
This program takes a text file and a string of characters called an identifier as input. It then searches through the text file and prints out all the lines
that contain that identifier, highlighting the identifier in red. The identifier must be surrouned by whitespace characters and not be a part of a larger word or
string. It can also optionally print out the line number for each line and or a user specified
number of lines before and after the identifier line as context. No line will be printed twice, and the number of context lines will only extend up or down 
to the first and last lines in the file but not past.

How to run it:
Running from the command line, first enter "make" to build the object files. Identifier takes input in the form of four command line arguments. Before the arguments
enter ./ident and then follow with the two optional arguments in any order: "-n" for numbered lines and "-c <context>" where <context> is a number. Finally enter the input file name and then
the identifier you are searching for.
