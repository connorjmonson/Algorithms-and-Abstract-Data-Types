// Connor Monson 1461818 cmonson@ucsc.edu
// pa1 10/2/17
// Lex.java 
import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;

/*** mostly all code taken from FileIO under examples and insertionSort ***/
class Lex {
    public static void main (String[] args) throws IOException {
      
      //mostly all taken from FileIO
        // Throws error if wrong number args
        if(args.length != 2) {
            System.err.println("Usage: FileIO infile outfile");
            System.exit(1);
        }
       //initialize and set everything 
        Scanner in = new Scanner(new File(args[0]));
        PrintWriter out = new PrintWriter(new FileWriter(args[1]));
        int lineNum = 0;
        List list = new List();
        ArrayList<String> con = new ArrayList<String>(); //new list of strings

        //determining how many lines are in the file 
        while(in.hasNextLine()) {
            lineNum++;
            con.add(in.nextLine());
        }

// void InsertionSort(int* A, int n){ //using this as a guide for my insertionSort variation 
//   int i, j, temp; 
//   for(j=1; j<n; j++){ 
//     temp = A[j]; 
//     i = j-1; 
//     while( i>=0 && temp<A[i] ){ 
//       A[i+1] = A[i]; 
//       i--; 
//     } 
//     A[i+1] = temp; 
//   } 
// } 
        
        // Sorting algorithm similar to insertion sort
        //not actually insertionSort but a variation that uses compareTo and ADT functions I made in list.java
        list.append(0);
        for(int j = 1; j < con.size(); j++) {
            int i = j - 1;
            String temp = con.get(j);
            list.moveBack();
            while(i >= 0 && temp.compareTo(con.get(list.get())) <= 0) {
                list.movePrev();
                i--;
            }
            if(list.index() >= 0){
              list.insertAfter(j);
            }
            else{
              list.prepend(j);
            }
        }

       //printing final results to the output file!
        list.moveFront(); //go to front
        while(list.index() >= 0) { 
            out.println(con.get(list.get()));
            list.moveNext(); //go down list
        }

        in.close(); //close scanner and printWriter
        out.close();
    }
}