// Connor Monson 1461818 cmonson@ucsc.edu
// pa5 11/11/17
// FindComponents.c
// basically same/very similar to FindPath.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 400 //just cuz i like yg400 lol 

int main(int argc, char* argv[]) { //*** keeps printing a 0 between stuff ***//

/*Read the input file.
• Assemble a graph object G using newGraph() and addArc().
• Print the adjacency list representation of G to the output file.
• Run DFS on G and GT , processing the vertices in the second call by decreasing finish times from
the first call.
• Determine the strong components of G.
• Print the strong components of G to the output file in topologically sorted order.*/
	
	//a bunch of shit goes in here
	//input and output 
	char line[MAX_LEN];
	int order = 0;//order of graph - number of vertices
	int v1 = 0;// "v1 v2" - vertex1 and vertex2 from input file
	int v2 = 0;
	int number = 0; //number of Strongly Connected Components
	int indexSCC = 1; //the SCC index 

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
	List S = newList();
	//I think the rest should jsut be two big while loops --->>>
	//Add edges to graph
	while( fgets(line, MAX_LEN, in) != NULL){//Continue reading inputfile for vertex pairs
		sscanf(line, "%d %d", &v1, &v2);//string to int
		if(v1==0 && v2==0){
			break;//If dummy line '0 0' found, then stop
		}
		addArc(G, v1, v2);//Add vertices into graph
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);//Print adjacency List
	fprintf(out, "\n");

// DFS and strongly connected component
	for(int i =1; i<=getOrder(G); i++){
		append(S,i); //put the shit into the list
	}
	DFS(G, S); //DFS on regular G
	Graph tran = transpose(G); //transpose graph
	DFS(tran, S); //DFS on trans of G

//strongly connected components or SCC for short? 
	for(moveBack(S); index(S)!=-1; movePrev(S)){ 
		if(getParent(tran, get(S)) == NIL){ 
			number++; 
		}
	}

	fprintf(out, "G contains %d strongly connected components:\n", number);

	List SCC[number];
	for(int i =1; i<=number; i++){
		SCC[i]= newList();
	}

//Print the strong components of G to the output file in topologically sorted order.
	for(moveBack(S); index(S)!=-1; movePrev(S)){
		prepend(SCC[indexSCC], get(S)); //every vertex gets prepended to list array called SCC
		if(getParent(tran, get(S)) == NIL){ 
			fprintf(out, "Component %d: ", indexSCC); //printing shit how it is in the example
			printList(out, SCC[indexSCC]);
			fprintf(out, "\n");
			indexSCC++; 
		}
	}

		//*** BFS I had for reference	

			// while(fgets(line, MAX_LEN, in) != NULL){//Continue reading while not empty
			// 	sscanf(line, "%d %d", &v1, &v2);//Converting string format of vertex into int format
			// 	if(v1==0 && v2==0){
			// 		break;//If dummy line '0 0' found, then stop
			// 	}
			// 	BFS(G, v1);//Running BFS
			// 	fprintf(out, "\nThe distance from %d to %d is ", v1, v2);
			// 	if(getDist(G, v2) == INF){
			// 		fprintf(out, "infinity\n");//If no path between source and terminus vertex
			// 	}else{ 
			// 		fprintf(out, "%d\n", getDist(G, v2));//Printing distance between vertices
			// 	}

			// 	List L = newList();//List that holds shortest path between vertices
			// 	getPath(L, G, v2);//Running shortest path operation, shortest path stored in List L
			// 	if(front(L) == NIL){
			// 		fprintf(out, "No %d-%d path exists\n", v1, v2);//If no shortest path exists
			// 	}else {//Shortest path does exist
			// 		fprintf(out, "A shortest %d-%d path is: ", v1, v2);
			// 		printList(out, L);//Print List, which represents shortest path
			// 		fprintf(out, "\n");
			// 	}
			// 	freeList(&L);//Free memory for no memory leaks
			// }

		//*** end of BFS

	//free 2 graphs, 1 list, and everything in Strongly Connected Components
	freeGraph(&G);//Free memory for no memory leaks 
	freeGraph(&tran);
	freeList(&S);
	//now free everything in SCC
	for(int i =1; i<=number; i++){
		freeList(&SCC[i]);
	}
	fclose(in); //rememberto close both in out files
	fclose(out);

	return(0);

}