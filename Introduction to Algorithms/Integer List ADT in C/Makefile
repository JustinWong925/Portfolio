#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 2
# Justin Wong jujwong@ucsc.edu
#       make                   makes Lex
#       make ListClient        makes ListClient
#       make submit            submits all files to cmps101-pt.f14
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient : ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o
	
submit :
	submit cmps101-pt.f14 pa2 Lex.c List.c List.h ListClient.c Makefile README 
 