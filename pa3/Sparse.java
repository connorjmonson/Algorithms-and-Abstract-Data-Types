// Connor Monson 1461818 cmonson@ucsc.edu
// pa3 10/22/17
// Sparse.java 

import java.io.*;
import java.util.Scanner;

public class Sparse {

 public static void main(String[] args) throws IOException{
        //mostly all taken from FileIO
        // Throws error if wrong number args
        if(args.length != 2) {
            System.err.println("Usage: FileIO infile outfile");
            System.exit(1);
        }
       //initialize and set everything 
        Scanner in = new Scanner(new File(args[0]));
        PrintWriter out = new PrintWriter(new FileWriter(args[1]));
        int n = in.nextInt(); // matrix size
        int a = in.nextInt(); // # of non-0 entries in matrix A
        int b = in.nextInt(); // # of non-0 entries in matrix B
        Matrix A = new Matrix(n); //calls to matrix.java to make new matrix A and B 
        Matrix B = new Matrix(n); 
        
        for (int con = 0; con<a; con++){
          int i = in.nextInt(); //column
          int j = in.nextInt(); //row
          double x = in.nextDouble(); //value
          A.changeEntry(i, j, x); //changes ith row, jth column of this Matrix to x
        }
        
        for (int con = 0; con<b; con++){
          int i = in.nextInt(); //column
          int j = in.nextInt(); //row
          double x = in.nextDouble(); //value
          B.changeEntry(i, j, x); //changes ith row, jth column of this Matrix to x
        }
        
        in.close(); //close scanner; in Lex I might have wanted to close it earlier but it still worked
        
        //all the stuff printed in the example for output file 
        out.println("A has "+ a + " non-zero entries:\n" + A);
        out.println("B has "+ b + " non-zero entries:\n" + B);
        out.println("(1.5)*A = \n" + A.scalarMult(1.5)); 
        out.println("A+B = \n" + A.add(B));
        out.println("A+A = \n" + A.add(A));
        out.println("B-A = \n" + B.sub(A));
        out.println("A-A = \n" + A.sub(A));
        out.println("Transpose(A) = \n" + A.transpose());
        out.println("A*B = \n" + A.mult(B));
        out.println("B*B = \n" + B.mult(B));
        
        out.close(); //close printWriter; in Lex I closed in and out at the very end which seemed to work 
        //but I do not want to risk any accidental in. calls 
        
 }
}