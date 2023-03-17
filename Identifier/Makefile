ident: ident.o syntax.o io.o
	gcc ident.o syntax.o io.o -o ident

ident.o: ident.c syntax.h io.h
	gcc -g -Wall -std=c99 -c -o ident.o ident.c
	
syntax.o: syntax.c syntax.h io.h
	gcc -c -Wall -std=c99 -g syntax.c -o syntax.o
	
io.o: io.c io.h
	gcc -g -Wall -std=c99 -c -o io.o io.c
	
clean:
	rm -f *.o
	rm -f ident