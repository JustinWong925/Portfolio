//Program 4: Doubly Linked List
//Justin Wong jujwong@ucsc.edu
//CS101 Tantalo Fall 14


#include <stdlib.h>
#include "List.h"


typedef struct nodeObj* node;

struct nodeObj {
  int data;
  node prev;
  node next;
};

// struct of type ListObj
typedef struct ListObj {
  node cursor;
  node front;
  node back;
  int length;
  int index;
} ListObj;

// constructor for a new list
List newList() {
  List lone = malloc (sizeof(struct ListObj));
  lone->cursor = NULL;
  lone->front = NULL;
  lone->back = NULL;
  lone->length = 0;
  lone->index = -1;
  return lone;
}

//Frees list, then frees the pointer itself
void freeList (List* pL){
  if ((*pL) == NULL) {
    printf("List.c: 43: Passing Nullpointer to freeList()");
    return;
  }
  clear(*pL);
  free(*pL);
  *pL = NULL;
}

// returns the number of elements in the list
int length(List L){
  if (L == NULL){
    printf("List.c: 62: Passing Nullptr to length()");
    return -1;
  } 
  return L->length;
}

// returns the index of the cursor element or -1 if undefined
int getIndex(List L){
  if (L == NULL){
    printf("List.c : 70: Passing Nullptr to getIndex()");
    return -1;
  }
  return L->index;
}

// Returns the front element if length > 0
// Pre: length()>0
int front(List L){
  if (L == NULL){
    printf("List.c : 70: Passing Nullptr to front()");
    return -1;
  }
  if (L->length > 0) return L->front->data;
  return -1;
}

// Returns back element of length > 0
// Pre: length()>0
int back(List L){
  if (L == NULL){
    printf("List.c : 93: Passing Nullptr to back()");
    return -1;
  }
  if (L->length > 0) return L->back->data;
  return -1;
}

// Returns cursor element in the list
// Pre: length()>0, getIndex()>=0
int getElement(List L){
  if (L == NULL){
    printf("List.c : 103: Passing Nullptr to getElement()");
    return -1;
  }
  if (L->length > 0 && L->index >=0){
    return L->cursor->data;
  }
  return -1;
}

//Returns true if the two lists are the same
//checks the indices of two lists
//and also checks that they are same length
int equals (List A, List B){
  if (A == NULL || B == NULL){
    printf("List.c : 112: Passing Null ptrs to equals()");
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
    printf("List.c : 130: Passing null ptr to clear()");
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
  L->cursor = NULL;
  L->length = 0;
  L->index = -1;
}

// If 0<=i<=length()-1, moves the cursor to the element 
// at index i, otherwise the cursor becomes undefined.
void moveTo(List L, int i){
  if (L == NULL){
    printf("List.c : 146: Passiling null ptr to moveTo()");
    return;
  }
  L->cursor = L->front;
  L->index = i;
  if(i >= 0 && i < L->length){
    for(; i > 0; i--){
      L->cursor = L->cursor->next;
    }
  } else {
    L->cursor = NULL;
    L->index = -1;
  }
}

// If 0<getIndex()<=length()-1, moves the cursor one step toward the
// front of the list. If getIndex()==0, cursor becomes undefined. 
// If getIndex()==-1, cursor remains undefined. This operation is
// equivalent to moveTo(getIndex()-1).
void movePrev(List L){
  if (L == NULL) {
    printf("List.c : 161: passing null ptr to movePrev");
    return;
  }
  if(L->index > 0 && L->index < L->length){
    L->cursor = L->cursor->prev;
    L->index--;
  } else {
    L->cursor = NULL;
    L->index = -1;
  }
}

// If 0<=getIndex()<length()-1, moves the cursor one step toward the
// back of the list. If getIndex()==length()-1, cursor becomes
// undefined. If index==-1, cursor remains undefined. This
// operation is equivalent to moveTo(getIndex()+1).
void moveNext(List L){
  if (L == NULL) {
    printf("List.c: 179: passing null ptr to moveNext");
    return;
  }
  if(L->index >= 0 && L->index < L->length - 1){
    L->cursor = L->cursor->next;
    L->index++;
  } else {
    L->cursor = NULL;
    L->index = -1;
  }
}

// Inserts new element before front element in this List
// makes new node then checks if node is only element in list
// to determine the front, and back
void prepend(List L, int data){
  if(L == NULL) {
    printf("List.c: 195: passing null ptr to prepend()");
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
    printf("List.c: 215: passing null ptr to append()");
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

// inserts and element before the cursor
// Pre: length()>0, getIndex()>=0
void insertBefore(List L, int data){
  if (L == NULL){
    printf("List.c: 239: passing null ptr to insertBefore()");
    return;
  }
  if (!(L->length > 0 && L->index >= 0)) return;
  L->length++;
  node node = malloc(sizeof(struct nodeObj));
  node->data = data;
  node->prev = L->cursor->prev;
  node->next = L->cursor;
  if(node->prev != NULL){
    L->cursor->prev->next = node; 
  } else {
    L->front = node;
  }
  L->cursor->prev = node;
  L->index++;
}

// inserts an element after the cursor
// Pre: length()>0, getIndex()>=0
void insertAfter(List L, int data){
  if(L == NULL){
    printf("List.c: 239: passing null ptr to insertAfter()");
    return;
  }
  if (!(L->length > 0 && L->index >= 0)) return;
  L->length++;
  node node = malloc(sizeof(struct nodeObj));
  node->data = data;
  node->prev = L->cursor;
  node->next = L->cursor->next;
  if(node->next != NULL){
    L->cursor->next->prev = node;
  } else {
    L->back = node;
  }
  L->cursor->next = node;
}

// Deletes the front element in this List.
// Pre: length()>0
void deleteFront(List L){
  if(L == NULL){
    printf("List.c: 287: passing null ptr to deleteFront()");
    return;
  }
  if(L->length > 0){
    L->length--;
    if(L->index == 0) L->cursor = NULL;
    if(L->back == L->front) L->back = NULL;
    node temp = L->front;
    L->front = L->front->next;
    free(temp);
    L->front->prev = NULL;
    if(L->index != -1) L->index--;
  }
}

// Deletes the back element in this List. 
// Pre: length()>0
void deleteBack(List L){
  if(L == NULL){
    printf("List.c: 307: passing null ptr to deleteFront()");
    return;
  }
  if(L->length > 0){
    L->length--;
    if(L->index == L->length - 1){
      L->cursor = NULL;
      L->index = -1;
    }
    if(L->back == L->front){
      free(L->back);
      L->front = NULL;
      return;
    }
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
    printf("List.c: 328: passing null ptr to delete()");
    return;
  }
  if(L->cursor == L->front){
    deleteFront(L);
  } else if (L->cursor == L->back){
    deleteBack(L);
  }
  if (L->length > 0 && L->index > 0){
    L->length--;
    node temp = L->cursor;
    L->cursor->next->prev = L->cursor->prev;
    L->cursor->prev->next = L->cursor->next;
    L->cursor = NULL;
    L->index = -1;
    free(temp);
  }
}

//Prints list
void printList (FILE *out, List L){
  if (L == NULL){
    printf("List.c: 352 passing null List ptr to printList()");
    return;
  }
  if (out == NULL){
    printf("List.c: 355: passing null FILE ptr to printList()");
    return;
  }

  node temp = L->front;
  while (temp != L->back){
    fprintf(out, "%d ", temp->data);
    temp = temp->next;
  }
  if(temp != NULL) fprintf(out, "%d", temp->data);
  
}

// Returns a new list representing the same integer sequence as this
// list. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged
List copyList(List L){
  if(L == NULL){
    printf("List.c: 367: passing null ptr to copy()");
    return NULL;
  }
  List copy = newList();
  for(node tmp = L->front; tmp != NULL; tmp = tmp->next){
    append(copy, tmp->data);
  }
  return copy;
}

// Returns a new List which is the concatenation of the two
List concat(List A, List B){
  if(A == NULL || B == NULL) printf("List.c : 379: null parameter");
  List linked = copyList(A);
  for(node tmp = B->front; tmp != NULL; tmp = tmp->next){
    append(linked, tmp->data);
  }
  return linked;
}