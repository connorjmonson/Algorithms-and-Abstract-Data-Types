// Connor Monson 1461818 cmonson@ucsc.edu
// pa2 10/2/17
// Lex.c 

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "List.h"

#define MAX_LEN 400 //just cuz i like yg400 lol 


//literally the same thing as Lex.java just translated into c
//args are different  

int main(int argc, char* argv[]) {

	char line[MAX_LEN];
	int numLines = 0; //number of lines in inputFile

	// Checking for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// Open input file; count numlines
	FILE* in = fopen(argv[1], "r"); // read
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	while( fgets(line, MAX_LEN, in) != NULL)  {
		numLines++;
	}
	fclose(in); //close

	List list = newList();
	char* stringArray[numLines]; //String array as pointer of length 'count' 

	// Open input file again; read individual lines into a String array
	FILE* in2 = fopen(argv[1], "r"); //in again
	if( in2==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	int i = 0; // use to loop through
	while( fgets(line, MAX_LEN, in2) != NULL){
		int j = strlen(line);
		stringArray[i] = malloc( sizeof(char)*j );
		strcpy(stringArray[i], line);
		i++;
	}
	fclose(in2); //close

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
        //not actually insertionSort but a variation that uses strcmp() and ADT functions I made in list.c
	append(list, 0); 

	for (int j = 1; j < numLines; j++){ //translated to c 
		char* temp = stringArray[j]; 
		int i = j - 1;
		moveBack(list); 
		while ( (i >= 0) && strcmp(temp, stringArray[get(list)]) <= 0 ){ 
			movePrev(list);
			i--;
		}

		if(index(list) >= 0){
			insertAfter(list, j);
		}

		else{
			prepend(list, j);
		}
	}

	
       //printing results to the output
	FILE* out = fopen(argv[2], "w"); //open, write
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	moveFront(list);
	while(index(list)>=0){
		fprintf(out, "%s", stringArray[get(list)]);
		moveNext(list);
	}
	fclose(out);

	//Free heap memory   
	//no leaks for me my man 
	for(i=0; i<numLines; i++){ 
		free(stringArray[i]); //free my leaks when I want too! no one will leak early 
	}
	freeList(&list);

	return(0);
}