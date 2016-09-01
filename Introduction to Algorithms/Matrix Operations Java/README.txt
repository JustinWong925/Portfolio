Programming Assignment 3
CS101 F14 Tantalo
Justin Wong jujwong

List.java
   This file is a list module. It is a doubly linked list, with nodes that have a next, curr and prev pointer.
   The list is used in a matrix to store objects in its nodes. It has been changed from a list of ints to a list of objects.
   
ListClient.java
   This is a client program that tests the functionality of list.java
   It has been modified from Program 1 to allow functionality with objects.
   
Matrix.java
   This file contains all the specified matrix operations. It has a private entry
   class for each entry of the matrix. It is a sparse matrix implemented using a list of objects.
   So it is possible to load/remove nodes and perform matrix operations using cursor iteration.
   
MatrixTest.java
   A test file from the class website, originally as MatrixClient.java but then modified to allow
   additional testing of methods in the List and Matrix ADT's.
   
Sparse.java
   The main program. It takes a valid input and output files and outputs the information
   from the matrix operations.
   
Makefile
   Compiles the files together
   
README
   You are reading me.