// Connor Monson 1461818 cmonson@ucsc.edu
// pa2 10/2/17
// List.c 

#include <stdio.h>
#include <stdlib.h>
//#include <string.h> this caused so many hours of problems of not knowing what was wrong :(
#include "List.h"

 //*** "Private Classes" for node (classic 12b type set up) ***//
typedef struct NodeObj{
 //Node Fields
 int data;
 struct NodeObj* prevNode;
 struct NodeObj* nextNode;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
 //List Fields
 Node front;
 Node back;
 Node cursor;//cursor node
 int index;//index for cursor node
 int length;//length of List by keeping count of nodes
} ListObj;

//I try to be consistent with creating new nodes for functions as Node N 
// just as I did in 12B 
//literally the same thing as List.java just translated into c 

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes nextNode and data fields.
// Private.
Node newNode(int node_data){
   Node N = malloc(sizeof(NodeObj));
   N->data = node_data;
   N->prevNode = NULL;
   N->nextNode = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

//newList()
//Returns reference to new empty List object.
List newList(void){
 List L = malloc(sizeof(ListObj));
 L->front = NULL;
 L->back = NULL;
 L->cursor = NULL;
 L->index = -1;//Index of cursor, initialized to -1 means undefined
 L->length = 0;
 return(L);
}

//freeList()
//Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pN){
 if(pN != NULL && *pN != NULL){
  while(length(*pN) != 0){
   deleteFront(*pN);
  }
  free(*pN); //basically freeNode but im going to keep around freeNode() because,
  *pN = NULL; //it frees 1 specified node, I believe, rather than the whole list of nodes
 }
}

//***Access functions***//
//length()
 //Returns number of elements in this list.
int length(List L){
  if(L == NULL){
   printf("List Error: calling length() on NULL reference \n");
  exit(1);
  }
  return L->length; //this.length
 }

//index()
 // If cursor is defined, returns the index of the cursor element;
 // otherwise returns -1.
 int index(List L){
 if(L == NULL){
   printf("List Error: calling index() on NULL reference \n");
  exit(1);
 }
   return L->index;
 }

 //front()
 //Returns front element in this list. 
 //Pre: length()>0
 int front(List L){
  if(L == NULL){
   printf("List Error: calling front() on NULL reference \n");
  exit(1);
 }
 if ( !(length(L)>0) ){
   printf("List Error: calling front() on empty list \n");
  exit(1);
 }
   return L->front->data;
 }

 //back()
 //Returns back element in this List. 
 //Pre: length()>0
 int back(List L) {
   if(L == NULL){
   printf("List Error: calling back() on NULL reference \n");
  exit(1);
 }
 if ( !(length(L)>0) ){
   printf("List Error: calling back() on empty list \n");
  exit(1);
 }
   return L->back->data;
 }
 
  //get()
 //Returns cursor element in this list.
 //Pre: length()>0, index()>=0
int get(List L) {
   if(L == NULL){
   printf("List Error: calling get() on NULL reference \n");
  exit(1);
 }
 if ( !(length(L)>0) ){
   printf("List Error: calling get() on empty list \n");
  exit(1);
 }
 if( index(L)<0){
   printf("List Error: calling get() on undefined cursor \n");
  exit(1);
 }
  return L->cursor->data;
 }

 //equals(List L)
 // Returns true if and only if this List and L are the same  // 1 is true 0 is false in this C program
 // integer sequence. The states of the cursors in the two Lists 
 // are not used in determining equality.
 //Returns true (1) if A is identical to B, false (0) otherwise
 int equals(List A, List B) { //Using code provided by professor in examples 
  if( A==NULL || B==NULL ){ //(ended up doing that a decent amount ^)
  printf("List Error: calling equals() on NULL reference \n");
  exit(1);
 }
 int flag = 1;  //assumption begins as true, and "if" ...
 Node N = A->front;
 Node M = B->front; // onto nextNode
 if( A->length != B->length ){ //not same length, false
  return 0;
 }
 while( flag && N!=NULL){//While the values compared are equal and calling List not empty
  flag = (N->data == M->data);// same?
  N = N->nextNode;
  M = M->nextNode;
 } //relized in this program from my other java program that I have an unnecessary "else" statement
 return flag;
 }

//***Manipulation Procedures***// // translating to c

 //clear()
 // Resets this List to its original empty state.
void clear(List L){
 if(L == NULL){
  printf("List Error: calling clear() on NULL reference \n");
  exit(1);
 }
 while ( length(L)>0 ){
  deleteFront(L);
 }
 L->index = -1;
 L->length = 0;
}

//moveFront()
 // If List is non-empty, places the cursor under the front element;
 // otherwise does nothing.
void moveFront(List L){
 if ( !(length(L)>0) ) { 
  printf("List Error: calling moveFront() on empty list \n");
  exit(1); 
 }
    if(length(L) > 0) {
     L->cursor = L->front;  //cursor = front;
     L->index = 0;
   }
}

//moveBack()
 // If List is non-empty, places the cursor under the back element;
 // otherwise does nothing.
void moveBack(List L){
 if ( !(length(L)>0) ) { 
  printf("List Error: calling moveBack() on empty list \n");
  exit(1); 
 }
    if(length(L) > 0) {
     L->cursor = L->back;  //cursor = back;
     L->index = length(L)-1; //not sure about this line 
   }
}

//movePrev()
 // If cursor is defined and not at front, moves cursor one step toward 
 // front of this List, if cursor is defined and at front, cursor becomes 
 // undefined, if cursor is undefined does nothing.
void movePrev(List L){
 if(L == NULL){
  printf("List Error: calling movePrev() on NULL reference \n");
  exit(1);
 }

 if( (index(L)>0) && (index(L)<=length(L)-1) ){
   L->index = index(L)-1;
   L->cursor = L->cursor->prevNode;
 }
 else if (index(L) == 0){//If index is 0, it is at front; by moving to prevNode, becomes undefined (falls off List)
  L->index = -1;
  L->cursor = NULL;
 }
}

//moveNext()
 // If cursor is defined and not at back, moves cursor one step toward 
 // back of this List, if cursor is defined and at back, cursor becomes 
 // undefined, if cursor is undefined does nothing.
void moveNext(List L){
 if(L == NULL){
  printf("List Error: calling moveNext() on NULL reference \n");
  exit(1);
 }

 if( (index(L)>=0) && (index(L)<length(L)-1) ){
   L->index = index(L)+1;
   L->cursor = L->cursor->nextNode;
 }
 else if (index(L) == length(L)-1){ //same as movePrev but opposite
  L->index = -1;
  L->cursor = NULL;
 }
}

//prepend(int data)
 //Inserts new element into this List. If list in non-empty,
 //insertion takes place before front element.
void prepend(List L, int data){
 if(L == NULL){
  printf("List Error: calling prepend() on NULL reference \n");
  exit(1);
 }

 Node N = newNode(data);
 if(length(L) == 0){//If List empty, set front and back to new node 
  L->front = N;
  L->back = N;
 }
 else {
  L->front->prevNode = N;
  N->nextNode = L->front;
  L->front = N;
 }
 L->length++;
}

//append(int data)
//Inserts new element into this List. If list in non-empty,
// insertion takes place after back element.
void append(List L, int data){
 if(L == NULL){
  printf("List Error: calling append() on NULL reference \n");
  exit(1);
 }

 Node N = newNode(data);
 if(length(L) == 0){ //If List empty, set front and back to new node 
  L->front = N;
  L->back = N;
 }
 else {
  L->back->nextNode = N;
  N->prevNode = L->back;
  L->back = N;
 }
 L->length++;
}

//insertBefore(int data)
 //Inserts new element before cursor 
 //Pre: length()>0, index()>=0
void insertBefore(List L, int data){
 if(L == NULL){
  printf("List Error: calling insertBefore() on NULL reference \n");
  exit(1);
 }
 if( !(length(L)>0) ){
  printf("List Error: calling insertBefore() on an empty List \n");
  exit(1);
 }
 if( index(L)<0){
  printf("List Error: calling insertBefore() on undefined cursor \n");
  exit(1);
 }

 if(L->index == 0){//If cursor element is pointing to front element
  prepend(L, data);//then prepend new node to front of List.
  L->index++;//increase index so cursor continues to point to original node
 }
 else{//Otherwise create new node and insert into List accordingly 
  Node N = newNode(data);
  N->prevNode = L->cursor->prevNode;
  N->nextNode = L->cursor;

  L->cursor->prevNode->nextNode = N;
  L->cursor->prevNode = N;

  L->index++;
  L->length++;
 }
}

//insertAfter(int data)
 //Inserts new element after cursor 
 //Pre: length()>0, index()>=0
void insertAfter(List L, int data){
 if(L == NULL){
  printf("List Error: calling insertAfter() on NULL reference \n");
  exit(1);
 }
 if( !(length(L)>0) ){
  printf("List Error: calling insertAfter() on an empty List \n");
  exit(1);
 }
 if( index(L)<0){
  printf("List Error: calling insertAfter() on undefined cursor \n");
  exit(1);
 }

 if(L->index == L->length-1){//If cursor element is pointing to last element
  append(L, data);//then append new node to end of List
 }
 else{//Otherwise create new node and insert into List accordingly
  Node N = newNode(data);
  N->prevNode = L->cursor;
  N->nextNode = L->cursor->nextNode;

  L->cursor->nextNode->prevNode = N;
  L->cursor->nextNode = N;

  L->length++;
 }
}

//deleteFront()
 //Deletes the front element
 //Pre: length()>0
void deleteFront(List L){
 if(L == NULL){
  printf("List Error: calling deleteFront() on NULL reference \n");
  exit(1);
 }
 if( !(length(L)>0) ){
  printf("List Error: calling deleteFront() on an empty List \n");
  exit(1);
 }

 Node N = L->front;//Let pointer N point to front node

 if(length(L)==1){//If List has one node only, set values to null
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
 }
 else{
  L->front = L->front->nextNode;
  L->front->prevNode = NULL;
 }
 L->length--;
 freeNode(&N);
}

//deleteBack()
 //Deletes the back element 
 //Pre: length()>0
void deleteBack(List L){
 if(L == NULL){
  printf("List Error: calling deleteBack() on NULL reference \n");
  exit(1);
 }
 if( !(length(L)>0) ){
  printf("List Error: calling deleteBack() on an empty List \n");
  exit(1);
 }

 Node N = L->back;//Let pointer N point to back node

 if (length(L)==1){//If List has one node only, set values to null
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
 }
 else{
  L->back = L->back->prevNode;
  L->back->nextNode = NULL;
 }
 L->length--;
 freeNode(&N);
}

 //delete()
 // Deletes cursor element, making cursor undefined. 
 //Pre: length()>0, index()>=0
void delete(List L){
 if(L == NULL){
  printf("List Error: calling delete() on NULL reference \n");
  exit(1);
 }
 if( !(length(L)>0) ){
  printf("List Error: calling delete() on an empty List \n");
  exit(1);
 }
 if( index(L)<0){
  printf("List Error: calling delete() on undefined cursor \n");
  exit(1);
 }

 if( index(L)==0 && length(L)>=1 ){
  deleteFront(L);
 }
 else if ( index(L)==length(L)-1 && length(L)>1 ){
  deleteBack(L);
 }
 else{//Otherwise, cursor points somewhere in the middle, remove cursor node by changing 
  //the prevNode and nextNode nodes the cursor points to.
  Node N = L->cursor;

  Node nodeAfterCursor = L->cursor->nextNode;
  Node nodeBeforeCursor = L->cursor->prevNode;
  nodeBeforeCursor->nextNode = nodeAfterCursor;
  nodeAfterCursor->prevNode = nodeBeforeCursor;
  
  L->length--;
  freeNode(&N);
 }
 L->index = -1;
 L->cursor = NULL;
}


//***Other Methods***// //LETS GET IT ONLY 2 MORE FOR THE ADT

 //toString()
 // Overrides Object's toString method. Returns a String 
 // representation of this List consisting of a space 
 // separated sequence of integers, with front on left.
void printList(FILE* out, List L){
 if(L == NULL){
  printf("List Error: calling printList() on NULL List reference \n");
  exit(1);
 }
 Node N = L->front;
 while(N != NULL){
  if(N->data != 0){
    fprintf(out, "%d ", N->data);//Print value of node
  }
  N = N->nextNode;
 }
}

//List copy()
 //Returns a new list representing the same integer sequence as this
 //list. The cursor in the new list is undefined, regardless of the
 //state of the cursor in this List. This List is unchanged.
//copyList()
List copyList(List L){
 if(L == NULL){
  printf("List Error: calling copyList() on NULL List reference \n");
  exit(1);
 }
 List newListCopy = newList();//Create/init new List
 Node N = L->front;//Start with 'temp' node at front of List

 while(N != NULL){
  append(newListCopy, N->data);
  N = N->nextNode;
 }
 return newListCopy;

}