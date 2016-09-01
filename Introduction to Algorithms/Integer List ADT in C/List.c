//Program 2: Doubly Linked List
//Justin Wong jujwong@ucsc.edu
//CS101 Tantalo Fall 14


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "List.h"



typedef struct nodeObj* node;

struct nodeObj {
  int data;
  node prev;
  node next;
};

typedef struct ListObj {
  node curr;
  node front;
  node back;
  int length;
  int index;
} ListObj;

// constructor for a new list
List newList() {
  List new = malloc (sizeof(struct ListObj));
  new->curr = NULL;
  new->front = NULL;
  new->back = NULL;
  new->length = 0;
  new->index = -1;
  return new;
}

//Frees list, then frees the pointer itself
void freeList (List* pL){
  if ((*pL) == NULL) {
    printf("Error: calling freeList() on NULL list reference");
    return;
  }
  clear(*pL);
  free(*pL);
  *pL = NULL;
}

// Returns number of elements in this list.
int length(List L){
  if (L == NULL){
    printf("Error: calling length() on NULL list reference");
    return -1;
  } 
  return L->length;
}

 // Returns the index of the cursor element in this list, or 
 // returns -1 if the cursor element is undefined.
int getIndex(List L){
  if (L == NULL){
    printf("Error: calling getIndex() on NULL list reference");
    return -1;
  }
  return L->index;
}

// Returns front element in this list. 
//Pre: length()>0
int front(List L){
  if (L == NULL){
    printf("Error: calling front() on NULL list reference");
    return -1;
  }
  if (L->length > 0) return L->front->data;
  return -1;
}

// Returns back element in this List. 
//Pre: length()>0
int back(List L){
  if (L == NULL){
    printf("Error: calling back() on NULL list reference");
    return -1;
  }
  if (L->length > 0) return L->back->data;
  return -1;
}

// Returns curr element in the list 
// Pre: length()>0, getIndex()>=0
int getElement(List L){
  if (L == NULL){
    printf("Error: calling getElement() on NULL list reference");
    return -1;
  }
  if (L->length > 0 && L->index >=0){
    return L->curr->data;
  }
  return -1;
}

//Returns true if the two lists are the same
//checks the indices of two lists
//and also checks that they are same length
int equals (List A, List B){
  if (A == NULL || B == NULL){
    printf("Error: calling equals() on NULL list reference");
    return -1;
  }
  node right = A->front;
  node left = B->front;
  while (right != NULL && left !=NULL){
    if(right->data != left->data) return 0;
    right = right->next;
    left = left->next;
  }
  if(right != NULL || left != NULL) return 0;
  return 1;
}

// Re-sets the list to the empty state
void clear(List L){
  if (L == NULL){
    printf("Error: calling clear() on NULL list reference");
    return;
  }
  node front = L->front;
  while (front != NULL){
    node temp = front->next;
    free(front);
    front = temp;
  }
  L->front = NULL;
  L->back = NULL;
  L->curr = NULL;
  L->length = 0;
  L->index = -1;
}

// If 0<=i<=length()-1, moves the cursor to the element 
// at index i, otherwise the cursor becomes undefined.
void moveTo(List L, int i){
  if (L == NULL){
    printf("Error: calling moveTo() on NULL list reference");
    return;
  }
  L->curr = L->front;
  L->index = i;
  if(i >= 0 && i < L->length){
    for(; i > 0; i--){
      L->curr = L->curr->next;
    }
  } else {
    L->curr = NULL;
    L->index = -1;
  }
}

// If 0<getIndex()<=length()-1, moves the cursor one step toward the
// front of the list. If getIndex()==0, cursor becomes undefined. 
// If getIndex()==-1, cursor remains undefined. This operation is
// equivalent to moveTo(getIndex()-1).
void movePrev(List L){
  if (L == NULL) {
    printf("Error: calling movePrev() on NULL list reference");
    return;
  }
  if(L->index > 0 && L->index < L->length){
    L->curr = L->curr->prev;
    L->index--;
  } else {
    L->curr = NULL;
    L->index = -1;
  }
}

// If 0<=getIndex()<length()-1, moves the cursor one step toward the
// back of the list. If getIndex()==length()-1, cursor becomes
// undefined. If index==-1, cursor remains undefined. This
// operation is equivalent to moveTo(getIndex()+1).
void moveNext(List L){
  if (L == NULL) {
    printf("Error: calling moveNext() on NULL list reference");
    return;
  }
  if(L->index >= 0 && L->index < L->length - 1){
    L->curr = L->curr->next;
    L->index++;
  } else {
    L->curr = NULL;
    L->index = -1;
  }
}

// Inserts new element before front element in this List
// makes new node then checks if node is only element in list
// to determine the front, and back
void prepend(List L, int data){
  if(L == NULL) {
    printf("Error: calling prepend() on NULL list reference");
    return;
  }
  L->length++;
  node node = malloc(sizeof(struct nodeObj));
  node->data = data;
  node->prev = NULL;
  node->next = L->front;
  if (L->front == NULL){
    L->back = node;
  } else {
    L->front->prev = node;
  }  
  L->front = node;
  if (L->index >= 0) L->index++;
}

// Inserts new element after back element in this List.
// makes new node and checks if node is only element in list
// to determine the front, and back
void append(List L, int data){
  if(L == NULL){
    printf("Error: calling append() on NULL list reference");
    return;
  }
  L->length++;
  node node = malloc(sizeof(struct nodeObj));
  node->data = data;
  node->prev = L->back;
  node->next = NULL;
  if(L->back == NULL){
    L->front = node;
  } else {
    L->back->next = node;
  }
  L->back = node;
}

// Inserts new element before cursor element
// Pre: length()>0, getIndex()>=0
void insertBefore(List L, int data){
  if (L == NULL){
    printf("Error: calling insertBefore() on NULL list reference");
    return;
  }
  if (!(L->length > 0 && L->index >= 0)) return;
  L->length++;
  node node = malloc(sizeof(struct nodeObj));
  node->data = data;
  node->prev = L->curr->prev;
  node->next = L->curr;
  if(node->prev != NULL){
    L->curr->prev->next = node; 
  } else {
    L->front = node;
  }
  L->curr->prev = node;
  L->index++;
}

// Inserts new element before cursor element
//Pre: length()>0, getIndex()>=0
void insertAfter(List L, int data){
  if(L == NULL){
    printf("Error: calling insertAfter() on NULL list reference");
    return;
  }
  if (!(L->length > 0 && L->index >= 0)) return;
  L->length++;
  node node = malloc(sizeof(struct nodeObj));
  node->data = data;
  node->prev = L->curr;
  node->next = L->curr->next; 
  if(node->next != NULL){
    L->curr->next->prev = node;
  } else {
    L->back = node;
  }
  L->curr->next = node;
}

// Deletes the front element in this List. 
//Pre: length()>0
void deleteFront(List L){
  if(L == NULL){
    printf("Error: calling deleteFront() on NULL list reference");
    return;
  }
  if(L->length > 0){
    L->length--;
    if(L->index == 0) L->curr = NULL;
    if(L->back == L->front) L->back = NULL;
    node temp = L->front;
    L->front = L->front->next;
    free(temp);
    L->front->prev = NULL;
    if(L->index != -1) L->index--;
  }
}

// Deletes the back element in this List. 
//Pre: length()>0
void deleteBack(List L){
  if(L == NULL){
    printf("Error: calling deleteBack() on NULL list reference");
    return;
  }
  if(L->length > 0){
    L->length--;
    if(L->index == L->length - 1){
      L->curr = NULL;
      L->index = -1;
    }
    if(L->back == L->front) L->front = NULL;
    node temp = L->back;
    L->back = L->back->prev;
    free(temp);
    L->back->next = NULL;
  }
}

// Deletes cursor element in this List. 
// Cursor is undefined after this operation. 
// Pre: length()>0, getIndex()>=0
void delete(List L){
  if(L == NULL){
    printf("Error: calling delete() on NULL list reference");
    return;
  }
  if(L->curr == L->front){
    deleteFront(L);
  } else if (L->curr == L->back){
    deleteBack(L);
  }
  if (L->length > 0 && L->index > 0){
    L->length--;
    node temp = L->curr;
    L->curr->next->prev = L->curr->prev;
    L->curr->prev->next = L->curr->next;
    L->curr = NULL;
    L->index = -1;
    free(temp);
  }
}

//Prints list
void printList (FILE *out, List L){
  if (L == NULL){
    printf("Error: calling printList() on NULL list reference");
    return;
  }
  if (out == NULL){
    printf("Error: out file is NULL");
    return;
  }
  node temp = L->front;
  while (temp != NULL){
    fprintf(out, "%d ", temp->data);
    temp = temp->next;
  }
}

// Returns a new list representing the same integer sequence as this
// list. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged
List copyList(List L){
  if(L == NULL){
    printf("Error: calling copyList() on NULL list reference");
    return NULL;
  }
  List copy = newList();
  for(node temp = L->front; temp != NULL; temp = temp->next){
    append(copy, temp->data);
  }
  return copy;
}

// Returns a new List which is the concatenation of the two
List concat(List A, List B){
  if(A == NULL || B == NULL) printf("Error: List is NULL");
  List catList = copyList(A);
  for(node temp = B->front; temp != NULL; temp = temp->next){
    append(catList, temp->data);
  }
  return catList;
}