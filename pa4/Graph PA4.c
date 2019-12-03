// Connor Monson 1461818 cmonson@ucsc.edu
// pa4 11/11/17
// Graph.c

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2


typedef struct GraphObj{
 //graph fields
	List* nbor;
	int* color;
	int* parent;
	int* distance;
	int order;
	int size;
	int recentVertex; //labels the most recent vertex as source for BFS  *???*

} GraphObj;


/*** Constructors-Destructors ***/
Graph newGraph(int n){
	//check statement
	//code creating a new graph 
	Graph G = malloc(sizeof(GraphObj)); //heap memory
	G->nbor = malloc(sizeof(List)* (n+1));
	G->color = malloc(sizeof(int)* (n+1));
	G->parent = malloc(sizeof(int)* (n+1));
	G->distance = malloc(sizeof(int)* (n+1));
	G->order = n;
	G->size = 0;
	G->recentVertex = NIL; //*???*
	//for loop to initialize
	for(int i=0; i<(n+1); i++){
		G->nbor[i] = newList();
		G->color[i] = WHITE; //start as all white
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	return G;
}
void freeGraph(Graph* pG){
	//check statement
	//free all heap memory for no leaks and set graph to null
	free((*pG)->nbor);
	free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->distance);
	free(*pG);
	*pG = NULL; 
}

/*** Access functions ***/
int getOrder(Graph G){
	return G->order;
}

int getSize(Graph G){
	return G->size;
}

int getSource(Graph G){
	return G->recentVertex;
}

int getParent(Graph G, int u){
	//check statement(s)
	return G->parent[u];

}

int getDist(Graph G, int u){
	//check statement(s)
	return G->distance[u];

}

void getPath(List L, Graph G, int u){
	//check statement(s)
	//3 checks 
	//utilize recursion, printPath, section 22.2 of vs.3 of txt 
	if (u == getSource(G)){
		append(L,u);
	}
	if (getParent(G,u) == NIL){ //*** if "something"
		append(L,NIL);
	} else{ //recursion 
		getPath(L, G, getParent(G,u));
		append(L,u);
	}
}

/*** Manipulation procedures ***/ //the hard ones 
//deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G){
	//check statement

	for(int i=i; i<=getOrder(G); i++){
		clear(G->nbor[i]);
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	G->size = 0;

}

void addEdge(Graph G, int u, int v){
	//check statement

	//utilizing addArc to write less of the same code
	// addArc(G, u, v);
	// addArc(G, v, u);
	// G->size++;

	//#1
	List V = G->nbor[v];
	if(length(V) == 0){
		append(V,u);
	}
	if(length(V)>0){
		//a bunch of code
		moveBack(V);
		while ( index(V)!=-1 && u<get(V) ) movePrev(V);
		if(index(V) !=-1 && u == get(V)) return;
		if(index(V) == -1) prepend(V, u);
		else insertAfter(V, u);
	}

	//#2
	List U = G->nbor[u];
	if(length(U) == 0){
		append(U,v);
	}
	if(length(U)>0){
		//a bunch of code
		moveBack(U);
		while ( index(U)!=-1 && v<get(U) ) movePrev(U);
		if(index(U) !=-1 && v == get(U)) return;
		if(index(U) == -1) prepend(U, v);
		else insertAfter(U, v);
	}
	G->size++;

	// List V = G->nbor[v];
	// List U = G->nbor[u];
	// if(length(V) == 0){
	// 	append(V, u);
	// }
	// if(length(V)>0){
	// 	//a bunch of code
	// 	//moveBack();
	// 	for(moveBack(V); index(V)!=-1 && u<get(V); movePrev(V)){
	// 		if(index(V)!=-1 && u<get(V)){
	// 			break;
	// 		}
	// 		if(index(V) == -1){
	// 			prepend(V,u);
	// 		}else{
	// 			insertAfter(V,u);
	// 		}

	// 	}
	// }
	// if(length(U) == 0){
	// 	append(U,v);
	// }
	// if(length(U)>0){
	// 	//a bunch of code
	// }

}

void addArc(Graph G, int u, int v){
	//check statement
	List U = G->nbor[u];
	if(length(U) == 0){
		append(U,v);
	}else if(length(U)>0){
		//a bunch of code
		moveBack(U);
		while ( index(U)!=-1 && v<get(U) ) movePrev(U);
		if(index(U) !=-1 && v == get(U)) return;
		if(index(U) == -1) prepend(U, v);
		else insertAfter(U, v);
	}

	G->size++;
}

void BFS(Graph G, int s){
	//check statement
	//using section 22.1, 22.2, and graph theory handout
	for(int i=1; i<=getOrder(G); i++){
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}

	G->recentVertex = s;
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;

	List C = newList();
	append(C, s);
	while(length(C)>0){
		int u = front(C);
		deleteFront(C);
		List adj = G->nbor[u];
		for(moveFront(adj); index(adj)!=-1; moveNext(adj)){
			int v = get(adj);
			if(G->color[v] == WHITE){
				G->color[v] = GRAY;
				G->distance[v] = (getDist(G, u)+1);
				G->parent[v] = u;
				append(C, v);
			}
		}
		G->color[u] = BLACK;
	}

	freeList(&C);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	//CHeck statement

	//loop that goes through and prints
	for(int i=1; i<=getOrder(G); i++){
		//print stuff
		fprintf(out, "%d: ", i);        					 // ** ??? *** ///
		printList(out,G->nbor[i]); // adjacent
		fprintf(out, "\n"); //new line

	}
}