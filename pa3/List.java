// Connor Monson 1461818 cmonson@ucsc.edu
// pa1 10/2/17
// List.java 

public class List {

 //***Private Classes for node (classic 12b type set uppre)***//
 private class Node {
  //Node Fields
  Object data;
  Node prevNode;
  Node nextNode;

  //Constructor
  Node(Object data) {
   this.data = data;
   this.prevNode = null;
   this.nextNode = null;
  }

  //toString(): Overrides Object's toString method.Returns a String 
  // representation of this List consisting of a space 
  // separated sequence of integers, with front on left.
  public String toString() {
   return String.valueOf(data);
  }
 }//end of private class Node

 //List Fields
 private Node front;
 private Node back;
 private Node cursor;//cursor node
 private int index; //index for cursor node
 private int length;//length of List by count of nodes.

 //***Constructor***//
 //Creates a new empty list.
 List() {
  this.front = null;
  this.back = null;
  this.cursor = null;
  this.index = -1; //cursor index; initialized to -1 means undefined
  this.length = 0;
 }

 //***Access functions***//
 //length()
 //Returns number of elements in this list.
 int length() {
  return this.length;
 }

 //index()
 // If cursor is defined, returns the index of the cursor element;
 // otherwise returns -1.
 int index() {
  return this.index;
 }

 //front()
 //Returns front element in this list. 
 //Pre: length()>0
 Object front() {
  if ( !(length()>0) ){
   throw new RuntimeException("List Error: front() called on empty List");
  }
  return this.front.data;
 }

 //back()
 //Returns back element in this List. 
 //Pre: length()>0
 Object back() {
  if ( !(length()>0) ) {
   throw new RuntimeException("List Error: back() called on empty List");
  }
  return this.back.data;
 }

 //get()
 //Returns cursor element in this list.
 //Pre: length()>0, index()>=0
 Object get() {
  if ( !(length()>0) ) {
   throw new RuntimeException("List Error: get() called on empty List");
  }
  if ( index()<0 ) {
   throw new RuntimeException("List Error: get() called undefined cursor");
  }
  return this.cursor.data;
 }

 //equals(List L) --> modified with Object and public
 // Returns true if and only if this List and L are the same 
 // integer sequence. The states of the cursors in the two Lists 
 // are not used in determining equality.
 public boolean equals(Object x) { //Using code provided by professor in examples (ended up doing that a decent amount) 
  boolean flag  = true;
  if(x instanceof List) { // is x an instant of list
        List L = (List)x;
        Node N = this.front;
        Node M = L.front;
        if( this.length==L.length ){
          while( flag && N!=null){
            flag = (N.data.equals(M.data)); //same? 
            N = N.nextNode;
            M = M.nextNode; //on to the next
          }
         return flag;
        }else{ //not the same length, therefore they can not be Equal
         return false;
        }
  
  }else{ // x not instance of list
    return false; 
  }

 }

 //***Manipulation Procedures***//
 //clear()
 // Resets this List to its original empty state.
 void clear() {
  this.front = null;
  this.back = null;
  this.cursor = null;
  this.index = -1;
  this.length = 0;
 }
 
 //moveFront()
 // If List is non-empty, places the cursor under the front element;
 // otherwise does nothing.
 void moveFront() {
   if ( !(length()>0) ) { throw new RuntimeException("List Error: moveFront() called on empty List"); }
   if(length() > 0) {
     cursor = front;
     index = 0;
   }
 }
 
 //moveBack()
 // If List is non-empty, places the cursor under the back element;
 // otherwise does nothing.
 void moveBack() {
   if ( !(length()>0) ) { throw new RuntimeException("List Error: moveBack() called on empty List"); }
   if(length() > 0) {
     cursor = back;
     index = length - 1;
   }
 }

 //movePrev()
 // If cursor is defined and not at front, moves cursor one step toward 
 // front of this List, if cursor is defined and at front, cursor becomes 
 // undefined, if cursor is undefined does nothing.
 void movePrev() {
  if ( (index()>0) && (index()<=length()-1) ){
   this.index = index()-1;
   this.cursor = this.cursor.prevNode;
  }else if (index()==0){
   this.index = -1;
   this.cursor = null;
  }
 }

 //moveNext()
 // If cursor is defined and not at back, moves cursor one step toward 
 // back of this List, if cursor is defined and at back, cursor becomes 
 // undefined, if cursor is undefined does nothing.
 void moveNext() {
  if ( (index()>=0) && (index()<length()-1) ){
   this.index = index()+1;//Moving one step toward back of the List
   this.cursor = this.cursor.nextNode;
  }else if (index() == length()-1){//If cursor index is length()-1, it is already at 
   //the back of List, so by moving to next it becomes undefined since it falls off List
   this.index = -1;
   this.cursor = null;
  }
 }

 //prepend(int data)
 //Inserts new element into this List. If list in non-empty,
 //insertion takes place before front element.
 void prepend(Object data) {
  Node newNode = new Node(data);
  
  if( length()==0 ){//If empty List, front and back set to newNode 
   this.front = newNode;
   this.back = newNode;
  }else{
   this.front.prevNode = newNode;
   newNode.nextNode = this.front;
   this.front = newNode;
  }
  this.length++;
 }

 //append(int data)
 //Inserts new element into this List. If list in non-empty,
 // insertion takes place after back element.
 void append(Object data) {
  Node newNode = new Node(data);
  
  if( length()==0 ){//If List empty, set front and back to newNode 
   this.front = newNode;
   this.back = newNode;
  }else{
   this.back.nextNode = newNode;
   newNode.prevNode = this.back;
   this.back = newNode;
  }
  this.length++;
 }

 //insertBefore(int data)
 //Inserts new element before cursor 
 //Pre: length()>0, index()>=0
 void insertBefore(Object data) {
  if ( !(length()>0) ) {
   throw new RuntimeException("List Error: insertBefore() called on empty List");
  }
  if ( !(index()>=0) ) {
   throw new RuntimeException("List Error: insertBefore() called on undefined cursor");
  }

  if (this.index == 0){
   prepend(data);
   this.index++;//increase index so cursor point to original node
  }else{
   Node newNode = new Node(data);
   newNode.prevNode = this.cursor.prevNode;
   newNode.nextNode = this.cursor;
   
   this.cursor.prevNode.nextNode = newNode; 
   this.cursor.prevNode = newNode;
   
   this.index++;
   this.length++;
  }
 }

 //insertAfter(int data)
 //Inserts new element after cursor 
 //Pre: length()>0, index()>=0
 void insertAfter(Object data) { //basically same as insertBefore
  if ( !(length()>0) ) {
   throw new RuntimeException("List Error: insertAfter() called on empty List");
  }
  if ( !(index()>=0) ) {
   throw new RuntimeException("List Error: insertAfter() called on undefined cursor");
  }

  if (this.index == this.length-1){
   append(data);
  }else{ 
   Node newNode = new Node(data);
   newNode.prevNode = this.cursor;
   newNode.nextNode = this.cursor.nextNode;
   
   this.cursor.nextNode.prevNode = newNode;
   this.cursor.nextNode = newNode;
   
   this.length++;
  }
 }

 //deleteFront()
 //Deletes the front element
 //Pre: length()>0
 void deleteFront() {
  if ( !(length()>0) ) {
   throw new RuntimeException("List Error: deleteFront() called on empty List");
  }

  if(length()==1){//If List has one node only, set values to null
   this.front = null;
   this.back = null;
   this.cursor = null;
  }else{//Otherwise, remove front node by letting front point to the next node
   this.front = this.front.nextNode;
   this.front.prevNode = null;
  }
  this.length--;
 }

 //deleteBack()
 //Deletes the back element 
 //Pre: length()>0
 void deleteBack() {
  if ( !(length()>0) ) {
   throw new RuntimeException("List Error: deleteBack() called on empty List");
  }

  if(length()==1){//If List has one node only, set values to null
   this.front = null;
   this.back = null;
   this.cursor = null;
  }else{//Otherwise, remove back node by letting back point to the previous node
   this.back = this.back.prevNode;
   this.back.nextNode = null;
  }
  this.length--;
 }

 //delete()
 // Deletes cursor element, making cursor undefined. 
 //Pre: length()>0, index()>=0
 void delete() {
  if ( !(length()>0) ) {
   throw new RuntimeException("List Error: delete() called on empty List");
  }
  if ( !(index()>=0) ) {
   throw new RuntimeException("List Error: delete() called on undefined cursor");
  }

  if( index()==0 && length()>=1 ){
   deleteFront();
  }else if( index()==length()-1 && length()>1){
   deleteBack();
  }else{
   Node nodeAfterCursor = this.cursor.nextNode;
   Node nodeBeforeCursor = this.cursor.prevNode;
   nodeBeforeCursor.nextNode = nodeAfterCursor;
   nodeAfterCursor.prevNode = nodeBeforeCursor;
   this.length--;
  }

  this.cursor = null; //set undefined
  this.index = -1;
  
 }

 //**********************Other Methods**********************//
 //toString()
 // Overrides Object's toString method. Returns a String 
 // representation of this List consisting of a space 
 // separated sequence of integers, with front on left.
 public String toString() {
  Node currentNode = this.front;
  String data = "";
  while(currentNode != null){
   data = data + currentNode.toString() + " ";// store data
   currentNode = currentNode.nextNode;//next
  }
  return data;
 }

}