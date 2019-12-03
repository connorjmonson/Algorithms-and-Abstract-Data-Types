// Connor Monson 1461818 cmonson@ucsc.edu
// pa4 11/11/17
// FindPath.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 400 //just cuz i like yg400 lol 

int main(int argc, char* argv[]) { //*** keeps printing a 0 between stuff ***//
	
	//a bunch of shit goes in here
	//input and output 
	char line[MAX_LEN];
	int order = 0;//order of graph - number of vertices
	int v1 = 0;// "v1 v2" - vertex1 and vertex2 from input file
	int v2 = 0;

	// Checking for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// Open input file; count numlines
	// same stuff as Lex.c kind of 
	FILE* in = fopen(argv[1], "r"); // read
	FILE* out = fopen(argv[2], "w"); //open, write

	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	fgets(line, MAX_LEN, in); // Reading first string from infile into 'line'
	sscanf(line, "%d", &order); // Converting string 'line' to int 'order'
	Graph G = newGraph(order); // Creating graph of order 'order'

	//I think the rest should jsut be two big while loops --->>>
	//Add edges to graph
	while( fgets(line, MAX_LEN, in) != NULL){//Continue reading inputfile for vertex pairs
		sscanf(line, "%d %d", &v1, &v2);//string to int
		if(v1==0 && v2==0){
			break;//If dummy line '0 0' found, then stop
		}
		addEdge(G, v1, v2);//Add vertices into graph
	}
	printGraph(out, G);//Print adjacency List

	
	// BFS and Print shortest path 
	while(fgets(line, MAX_LEN, in) != NULL){//Continue reading while not empty
		sscanf(line, "%d %d", &v1, &v2);//Converting string format of vertex into int format
		if(v1==0 && v2==0){
			break;//If dummy line '0 0' found, then stop
		}
		BFS(G, v1);//Running BFS
		fprintf(out, "\nThe distance from %d to %d is ", v1, v2);
		if(getDist(G, v2) == INF){
			fprintf(out, "infinity\n");//If no path between source and terminus vertex
		}else{ 
			fprintf(out, "%d\n", getDist(G, v2));//Printing distance between vertices
		}

		List L = newList();//List that holds shortest path between vertices
		getPath(L, G, v2);//Running shortest path operation, shortest path stored in List L
		if(front(L) == NIL){
			fprintf(out, "No %d-%d path exists\n", v1, v2);//If no shortest path exists
		}else {//Shortest path does exist
			fprintf(out, "A shortest %d-%d path is: ", v1, v2);
			printList(out, L);//Print List, which represents shortest path
			fprintf(out, "\n");
		}
		freeList(&L);//Free memory for no memory leaks
	}

	fclose(in);
	fclose(out);
	freeGraph(&G);//Free memory for no memory leaks 

	return(0);

}