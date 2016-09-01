//Program 5: Doubly Linked List
//Justin Wong jujwong@ucsc.edu
//CS101 Tantalo Fall 14


#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>

typedef struct ListObj* List;

//Constructors-Destructors ------------------------------------
List newList(void);
void freeList(List* pL);

// Access functions -------------------------
// Returns number of elements in this list
int length(List L);
// returns -1 if cursor element is undefined
int getIndex(List L);
// returns front element in list. Pre: length() > 0
int front(List L);
// returns back element in this list. Pre: length() > 0
int back(List L);
// returns cursor element in this list
//pre : length() > 0, getIndex() >=0
int getElement(List L);

int equals(List A, List B);

//Manipulation procedures -------------------------------------
void clear (List L);
// if 0 <= i <= length() -1, moves cursor to element
void moveTo(List L, int i);
// if 0 < i <= length() -1, moves cursor to previous element
void movePrev(List L);
// if 0 <= i < length() -1, moves cursor to next element
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
// Pre: length() > 0, getIndex() >= 0
void insertBefore(List L, int data);
// Pre: length() > =, getIndex() >= 0
void insertAfter(List L, int data);
// Pre: length() > 0
void deleteFront(List L);
// Pre: length () > 0
void deleteBack(List L);
// Pre: length () > 0, getIndex() >= 0
void delete(List L);

//Other operations -------------------------------------------------
void printList (FILE* out, List L);
List copyList(List L);

#endif