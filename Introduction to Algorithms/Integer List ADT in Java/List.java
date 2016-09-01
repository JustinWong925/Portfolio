// Program 1: Doubly Linked List
//Justin Wong jujwong

import java.util.*;
import java.util.NoSuchElementException;

class List{

   //defining the node
   private class Node{
      //fields
      int data;
	  Node next;
	  Node prev;
	  
	  //constructor
	  Node(int data){
	     this.data = data;
		 next = prev = null;
	  }
	  public String toString() {return String.valueOf(data);}
   }
   
   //Fields
   private Node front;
   private Node back;
   private Node curr;
   private int length;
   
   //constructor
    List() {
	front = back = curr = null; 
	length = 0;
	}
	
	//Access Functions
   boolean isEmpty() {return length == 0;}
   boolean off() {return (this.curr == null);}
   
   int length() {return length;}
   
   //Pre: length() > 0
   int front() {
      if (this.isEmpty()){
      throw new RuntimeException("Error: front called on empty list");}
	  return front.data;
   }
   
   //Pre: length() > 0
   int back() {
      if (this.isEmpty()){
      throw new RuntimeException("Error: back called on empty list");}
	  return back.data;
   }
   
   //returns the index of cursor element in list or -1 if cursor is undefined
   int getIndex(){
      int index;
	  if(this.off()){
	     index = -1;
		 return index;
	  }else{
      Node temp = new Node(this.front.data);
	  temp = this.front;
      for(index = 0; this.curr != temp; ++index){
	     temp = temp.next;
	  }
	  return index;
	  }
   }
   
   // Returns cursor element in this list. 
   // Pre: length()>0, getIndex()>=0
   int getElement(){
   if(this.isEmpty()){
      throw new RuntimeException("Error: empty list");
   }else if(this.getIndex() < 0){
	  throw new RuntimeException("Error: out of bounds");
   }
   return this.curr.data;
   }
   
   //returns true if this List and L are same integer sequence, cursor is ignored in both lists
   boolean equals(List L){
      boolean flag = true;
	  Node M = this.front;
	  Node N = L.front;
	  if(this.length == L.length){
	     while( flag && M != null){
		    flag = (N.data == M.data);
			N = N.next;
			M = M.next;
		 }
		 return flag;
	  } else {
	     return false;
	  }
   }
   
   //Manipulation Procedures
   
   //resets list to empty state
   void clear(){
      this.back = null;
	  while ( !this.isEmpty()){
	     this.curr = this.front;
		 this.curr = this.curr.next;
		 if ( this.curr != null) this.curr.prev = null;
		 this.front.next = null;
		 --length;
	  }
	  this.front = null;
   }
   
   //If 0<=i<=length()-1, moves the cursor to the element 
   //at index i, otherwise the cursor becomes undefined.
   void moveTo(int i){
      if(i < 0 && i > (this.length)){
	     throw new RuntimeException("Error: not in list");
	   }
       this.curr = this.front;
       for(int t = 0; t < i; ++t){
          this.curr = this.curr.next;
       }	   
	  }
   
   // If 0<getIndex()<=length()-1, moves the cursor one step toward the
   // front of the list. If getIndex()==0, cursor becomes undefined. 
   // If getIndex()==-1, cursor remains undefined. This operation is
   // equivalent to moveTo(getIndex()-1).
   void movePrev(){
      if(this.isEmpty()){
	     throw new RuntimeException("Error: empty list");
	  }else if(this.getIndex() == -1){
	     this.curr = null;
	     //throw new RuntimeException("Error: pointer off list");
	  }else if(this.getIndex() == 0){
	     this.curr = null;
	  }
      else if((this.getIndex() > 0) && (this.getIndex() <=(this.length() - 1))){
	     //this.curr = this.curr.prev; //this line doesnt work
		 this.moveTo(this.getIndex() -1); //works
		 }
   }
   
   
   // If 0<=getIndex()<length()-1, moves the cursor one step toward the
   // back of the list. If getIndex()==length()-1, cursor becomes
   // undefined. If index==-1, cursor remains undefined. This
   // operation is equivalent to moveTo(getIndex()+1).
   void moveNext(){
      if(this.isEmpty()){
	     throw new RuntimeException("Error: empty list");
	  }else if(this.off()){
	     this.curr = null;
	  }else if (this.getIndex() == (this.length() -1)){
	     this.curr = null;
	  }
      if((this.getIndex() >= 0) && ((this.length() - 1) > this.getIndex())){
	     this.curr = this.curr.next;
		 }
   }
   
   // Inserts new element before front element in this List.
   void prepend(int data){
      Node temp = new Node(data);
	  if (this.isEmpty()){front = back = temp;}
	  else { temp.next = front; temp.prev = temp; front = temp;}
	  ++length;
   }
   
   // Inserts new element after back element in this List.
   void append(int data){
      Node temp = new Node(data);
	  if(this.isEmpty()){front = back = temp;}
	  else { temp.prev = back; back.next = temp; back = temp;}
	  ++length;
   }
   
   // Inserts new element before cursor element in this
   // List. Pre: length()>0, getIndex()>=0
   void insertBefore(int data){
      if(this.length < 0){
        throw new RuntimeException("Error: empty list");
        }
      else if(this.getIndex() < 0){
         throw new RuntimeException("Error: cursor is undefined");
      }
      Node temp = new Node(data);
	  if(curr.prev == null){
	     temp.next = front;
		 front.prev = temp;
		 front = temp;
	  } else {
	     temp.prev = curr.prev;
		 temp.next = curr;
		 curr.prev.next = temp;
		 curr.prev = temp;
	  }
	  ++length;
   }
   
   // Inserts new element after cursor element in this 
   // List. Pre: length()>0, getIndex()>=0
   void insertAfter(int data){
      if(this.length < 0){
	     throw new RuntimeException("Error: length is < 0");
	  }
	  else if(this.getIndex() < 0){
	     throw new RuntimeException("Error: cursor is undefined");
	  }
	  Node temp = new Node(data);
	  if(curr.next == null){
	     back.next = temp;
		 back = temp;
		 back.prev = curr;
	  }else{
	     temp.prev = curr;
		 temp.next = curr.next;
		 curr.next.prev = temp;
		 curr.next = temp;
	  }
	  ++length;
   }
   
   // Deletes the front element in this List. Pre: length()>0
   // doesn't return a node
   void deleteFront(){
      if(this.isEmpty()){
	     throw new RuntimeException("Error: List is empty");
	  }
	  if(this.length > 1){ //if there is more than one element in list
	     front = front.next;
	     front.prev = null;
	  }else{ //if there is only 1 element in list
	  front = back = curr = null;
	  }
	  --length;
   }
   
   // Deletes the back element in this List. Pre: length()>0
   void deleteBack(){
      if(this.isEmpty()){
	     throw new RuntimeException("Error: List is empty");
	  }
	  if(this.length > 1){
	     back = back.prev;
		 back.next = null;
	  }else{
	     front = back = curr = null;
	  }
	  --length;
   }
   
   
   // Deletes cursor element in this List. Cursor is undefined after this 
  // operation. Pre: length()>0, getIndex()>=0
   void delete(){
      if(this.length < 0){
	     throw new RuntimeException("Error: length is < 0");
	  }
	  else if(this.getIndex() < 0){
	     throw new RuntimeException("Error: cursor is undefined");
	  }
	  if(this.length > 1){
	     if(curr.prev == null){
		    front = curr.next;
			curr.next = null;
		 }else if(curr.next == null){
		    back = curr.prev;
			curr.prev = null;
		 }else{
		    curr.prev.next = curr.next;
			curr.next.prev = curr.prev;
			curr.prev = curr.next = null;
		 }
		 curr = null;
	  }
	  else{ front = back = curr = null;}
	  --length;
   }
   
   //Other methods
   
   public String toString(){
      String str = "";
	  for (Node temp = front; temp != null; temp = temp.next){
	     str += temp.toString() + " ";
	  }
	  return str;
   }
   
   // Returns a new list representing the same integer sequence as this
   // list. The cursor in the new list is undefined, regardless of the
   // state of the cursor in this List. This List is unchanged.
   List copy(){
      List copyL = new List();
	  Node temp = this.front;
	  while(temp != null){
	     copyL.append(temp.data);
		 temp = temp.next;
	  }
      return copyL;
   }
   
    // Returns a new List which is the concatenation of 
    // this list followed by L. The cursor in the new list
    // is undefined, regardless of the states of the cursors
    // in this list and L. The states of this list and L are
    // unchanged.
   List concat(List L){
      List list = new List();
	  List catList = new List();
	  list = this.copy();
	  catList = L.copy();
	  list.back.next = catList.front;
	  catList.front.prev = list.back;
	  list.back = catList.back;
	  list.length += L.length;
	  return list;
   }
   
   
   
   
   
}
