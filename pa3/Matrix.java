// Connor Monson 1461818 cmonson@ucsc.edu
// pa3 10/22/17
// Matrix.java 

//***REMINDER: delete comments to clean up when everything works***//

public class Matrix {
  
  //***Private Classes for "entry" (classic 12b type set uppre)***//
  private class Entry {
    //two Entry Fields
    int column; //column info
    double value; //value info
    
    
    //Constructor
    Entry(int column, double value) {
      this.column = column;
      this.value = value; 
    }
    
    //equals(): override the corresponding methods in the Object superclass
    public boolean equals (Object x){ // no return statement? wtf
      boolean flag  = true;
      if(x instanceof Entry) { // is x an instant of Entry
        Entry E = (Entry)x;
//        if(this.column==E.column && this.value==E.value){
//          return flag;
//        }
        return (this.column==E.column && this.value==E.value);
      }else{ // x not instance of Entry
        return false;
      }
    }
    
    //toString(): override the corresponding methods in the Object superclass
    public String toString() {
      //return String.valueOf(data);
      return ("(" + column + "," + " " + value + ")"); //this is a string --> (column, value)
    }
  }//end of private class Entry

//It is required that these Lists be maintained in column sorted order. Your Matrix ADT will export the following operations.
  //Matrix Fields
  private int size; //size of matrix (n x n)
  private int NNZ; // as specified, is abreviation for number of non-zero entries
  private List[] r; //array of List rows; r= row, so r will have column int and value double
  
// Constructor
// Makes a new n x n zero Matrix. 
// pre: n>=1
  Matrix(int n){
    NNZ = 0;
    //size= n; 
    size = n+1; //not n because in the example it starts at 1 not 0  ***//might change this 
    r = new List[size]; //List array r is of size specified 
    for(int i=0; i<size; i++){
      r[i]= new List(); //each list now has a List 
    }
  }
    
// Access functions
// Returns n, the number of rows and columns of this Matrix 
  int getSize(){
    return this.size-1;
  }
    
// Returns the number of non-zero entries in this Matrix  
  int getNNZ(){
    return this.NNZ;
  }
    
// overrides Object's equals() method  
  public boolean equals(Object x){                    // *having trouble working*
      if(x instanceof Matrix) { // is x an instant of Entry
        Matrix M = (Matrix)x;  
        if(this.size!=M.size || this.getNNZ()!=M.getNNZ()){
          return false;
        }
        for(int i=0; i<this.size; i++){
          if( !(this.r[i].equals(M.r[i]))){
            return false;
          }
        }
        return true;
      }else{ // x not instance of Entry
        return false;
      }
  }
  
// Manipulation procedures
// sets this Matrix to the zero state 
  void makeZero(){
    for(int i=0; i<this.size; i++){
      this.r[i].clear(); //clearing the rows 
    }
    this.NNZ=0;
    //this.size=0; //dont need 
  }
  
// matrix copy() follows similarly to other copy()  
// returns a new Matrix having the same entries as this Matrix
  Matrix copy(){
    Matrix copy = new Matrix(this.size); // -1 because I did size = n+1
    for(int i=0; i<this.size; i++){
      if(r[i].length() != 0){
        for(r[i].moveFront(); r[i].index()>=0; r[i].moveNext()){
          //some code dealing with entry
          Entry temp = (Entry)r[i].get(); //storing as temporary Entry value of the Matrix in specified row
          copy.changeEntry(i, temp.column, temp.value); //adding temp Entry to copy Matrix
        }
      }
    }
    return copy; // returning a new Matrix 
  }

// changes ith row, jth column of this Matrix to x
// pre: 1<=i<=getSize(), 1<=j<=getSize()
  void changeEntry(int i, int j, double x){ //WHY ARE YOU NOT WORKING :(  
//Mij=0, x!=0 --> insert  or Mij!=0, x!=0 --> overwrite data
//putting non-zero entries to ith row
    if(x!=0){//if value inserted is not 0
      if(r[i].length()>0){
        for(r[i].moveFront(); r[i].index()>=0; r[i].moveNext()){
          Entry temp = (Entry)r[i].get();
          if(temp.column == j) { //if column = j column
            r[i].delete();
            NNZ--;
            break;
          }
        }
        boolean flag = false; //the boolean was the key!
        for(r[i].moveFront(); r[i].index()>=0; r[i].moveNext()){
          Entry temp = (Entry)r[i].get();
          if (j < temp.column){ 
            r[i].insertBefore(new Entry(j,x)); //new entry before
            NNZ++;
            flag = true;
            break;
          }
        }
        if(!flag){ //no j column was flagged less than any column value already
          r[i].append(new Entry(j,x)); 
          NNZ++;
        }
        
      }else{ //just append
        r[i].append(new Entry(j,x));
        NNZ++;
      }
    } 
//Mij=0, x=0 --> nothing  or Mij!=0, x=0 --> delete
    if(x==0){//If value is 0
      if(r[i].length()>0){
        for(r[i].moveFront(); r[i].index()>=0; r[i].moveNext()){
          Entry temp = (Entry)r[i].get();
          if(temp.column == j && (int)temp.value != 0) { // flagged
            r[i].delete();
            NNZ--;
            break;
          }
        }
      }
    }
// ---------------- //first weak attempt without boolean worked for some cases
//    if(r[i].length()!=0){ //row length not 0
//      for(r[i].moveFront(); r[i].index()>=0; r[i].moveNext()){ //loop through entries in the row
//        //some code dealing with entry
//        Entry temp = (Entry)r[i].get(); //storing as temporary Entry value of the Matrix at row i
//        if(temp.column == j){ //if the column number already exists 
//          if(x == 0){ //and if the new changed value x: is zero 
//            r[i].delete(); //delete entry
//            NNZ--; //subtract 1 from nonzero entries
//            break; //get out of loop 
//          }else{ // x is not 0
//            temp.value = x; //changing value
//            break; //get out of loop
//          } 
//        }else if(temp.column > j){ //if j is less than an already existing column in the row 
//          if(x!=0){ //then if x is not 0
//            r[i].insertBefore(new Entry(j,x)); //NOT WORKING
//            NNZ++; 
//            break; //get out of loop
//          }
//        }
//        
//      }
//    }
//    if(r[i].length()==0 && x!=0){ //nothing in the row, and the x value isn not 0 
//      r[i].append(new Entry(j,x)); //NOT WORKING
//      NNZ++;      
//    }
  }
  
// returns a new Matrix that is the scalar product of this Matrix with x  
  Matrix scalarMult(double x){
    Matrix M = new Matrix(this.size-1); //again getSize()-1 because size = n+1 
    for(int i=0; i<this.size; i++){
      //System.out.println("this.size: "+this.size);
      if(r[i].length() == 0){ 
      }else{ 
        for(this.r[i].moveFront(); this.r[i].index()>=0; this.r[i].moveNext()){ //loop through entries in the row
          //System.out.println("this.index()"+this.r[i].index());
          //some code dealing with entry
          Entry temp = (Entry)r[i].get(); //storing as temporary Entry value of the Matrix in specified row
          M.changeEntry(i, temp.column, x*(temp.value)); //adding temp Entry to copy Matrix
        }
      }
    }  //maybe could use some sort of like copy variation? idk 
    return M; 
  }
  
// returns a new Matrix that is the sum of this Matrix with M
// pre: getSize()==M.size
  Matrix add(Matrix M){
    Matrix add = new Matrix(this.size-1);
    //base case: if they the same matrix just multiply by 2 (aka adding) 
    if(this.equals(M)){ return this.scalarMult(2);}
    
    for(int i=1; i<this.size; i++){
      //this matrix has row and M matrix has row 
      if(this.r[i].length()>0 && M.r[i].length()>0){ //most complicated
        this.r[i].moveFront();
        M.r[i].moveFront();
        while(this.r[i].index()>=0 && M.r[i].index()>=0){ 
          Entry tempForThis = (Entry)r[i].get();
          Entry tempForM = (Entry)M.r[i].get();
          if(tempForThis.column == tempForM.column){ //same column
            add.changeEntry(i, tempForThis.column, (tempForThis.value + tempForM.value)); //add together
            this.r[i].moveNext();
            M.r[i].moveNext();
          }
          if(tempForThis.column < tempForM.column){ //if column for M is bigger --> add tempForThis
            add.changeEntry(i, tempForThis.column, tempForThis.value); 
            this.r[i].moveNext(); //moving this on to the next while M remains same
            //M.r[i].moveNext();
          }
          if(tempForThis.column > tempForM.column){ //if column for this is bigger --> add tempForM
            add.changeEntry(i, tempForM.column, tempForM.value);
            //this.r[i].moveNext();
            M.r[i].moveNext(); //moving M on to the next while this remains same 
          }   
        } //done with while
        if(this.r[i].index()>=0 && M.r[i].index()<0){ //adding the rest of remaining this values, with M values 0
          while(this.r[i].index()>=0){
            Entry tempForThis = (Entry)r[i].get();
            add.changeEntry(i, tempForThis.column, tempForThis.value);
            this.r[i].moveNext();
          }
        }
        if(this.r[i].index()<0 && M.r[i].index()>=0){ //adding the rest of remaining M values, with this values 0 
          while(M.r[i].index()>=0){
                Entry tempForM = (Entry)M.r[i].get();
                add.changeEntry(i, tempForM.column, tempForM.value);
                M.r[i].moveNext();
          }
        }
      }
      // this matrix has row but M matrix does not 
      if(this.r[i].length()>0 && M.r[i].length()==0){
        for(this.r[i].moveFront(); this.r[i].index()>=0; this.r[i].moveNext()){
          Entry tempForThis = (Entry)r[i].get();
          add.changeEntry(i, tempForThis.column, tempForThis.value);
        }
      }
      // M matrix has row but this matrix does not
      if(this.r[i].length()==0 && M.r[i].length()>0){
        for(M.r[i].moveFront(); M.r[i].index()>=0; M.r[i].moveNext()){
          Entry tempForM = (Entry)M.r[i].get();
          add.changeEntry(i, tempForM.column, tempForM.value);
        }
      }
    }

    return add;
  }
  
// returns a new Matrix that is the difference of this Matrix with M
// pre: getSize()==M.size
  Matrix sub(Matrix M){
    //Matrix sub = new Matrix(this.size-1);
    //ta told me to just do scalar multiply by -1 and then call add 
    Matrix sub = M.scalarMult(-1); //turns everything opposite
    Matrix result = this.add(sub); //adding the this and opposite of m is the same as subtracting
    return result;
    
    //base case: if they the same matrix just multiply by 2 (aka adding) 
//    if(this.equals(M)){ return this.scalarMult(-2);}
//    
//    for(int i=1; i<this.size; i++){
//      //this matrix has row and M matrix has row 
//      if(this.r[i].length()>0 && M.r[i].length()>0){ 
//        
//      }
//      // this matrix has row but M matrix does not 
//      if(this.r[i].length()>0 && M.r[i].length()==0){
//        for(this.r[i].moveFront(); this.r[i].index()>=0; this.r[i].moveNext()){
//          
//        }
//      }
//      // M matrix has row but this matrix does not
//      if(this.r[i].length()==0 && M.r[i].length()>0){
//        for(M.r[i].moveFront(); M.r[i].index()>=0; M.r[i].moveNext()){
//        
//        }
//      }
//    }
  }
  
// returns a new Matrix that is the transpose of this Matrix  
  Matrix transpose(){
   Matrix transpose = new Matrix(this.size);
   for (int i=0; i<this.size; i++){
     if(r[i].length() == 0){
     }else{
       for(r[i].moveFront(); r[i].index()>=0; r[i].moveNext()){ //loop through entries in the row
         //some code dealing with entry 
         Entry temp = (Entry)r[i].get();
         int column = temp.column;
         transpose.changeEntry(column, i, temp.value); //switching column and row!
       }
     }
   }
   return transpose;
  }

// returns a new Matrix that is the product of this Matrix with M
// pre: getSize()==M.size
  Matrix mult(Matrix M){
    Matrix mult = new Matrix(this.size); // seriously contemplating changing size = n instead of size=n+1 //this matrix
    Matrix transposeM = M.transpose(); //transpose of matrix M; transpose will make it easier to 
    for (int i=1; i<this.size; i++){ //double loop n^2 //ith row //maybe start i=1 
      for(int j=1; j<transposeM.size; j++){ //jth column //maybe start j=1
        //use dot product 
        mult.changeEntry(i, j, dot(this.r[i], transposeM.r[j])); //***change entry doesnt work yet, but i think this will work
      }
    }
    return mult;
  }
  
// Other functions
// overrides Object's toString() method
  public String toString(){
    String s = "";
    for(int i=1; i<size; i++){ //getting confused with the size=n+1 ... size-1 or size? shit 
      if(r[i].length()>0){ //if non-empty row
        s= s + i + ":" + r[i].toString() + "\n"; // add row to s to print
        //s= s + String.valueOf(i) + ":" + r[i] + "\n";
      }
    }
    return s; 
  }
  
  
//dot product private function
  private static double dot(List P, List Q){
    double dot = 0; //will be returned double
    if(P.length()==0){
    }else{
      for(P.moveFront(); P.index()>=0; P.moveNext()){
        Entry tempForP = (Entry)P.get();
        if(Q.length()==0){
        }else{
          for(Q.moveFront(); Q.index()>=0; Q.moveNext()){
            Entry tempForQ = (Entry)Q.get();
            if(tempForP.column == tempForQ.column){ 
              dot += (tempForP.value * tempForQ.value); 
              //same as dot= dot + (tempP.value*tempQ.value)
            }
          } 
        }
      }
    }
    return dot; 
  }

}