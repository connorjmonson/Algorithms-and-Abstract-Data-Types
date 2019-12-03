// Connor Monson 1461818 cmonson@ucsc.edu
// pa5 11/11/17
// Graph.c

//forgot to do check statements on 
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
	int* discover;
	int* finish;
	int order;
	int size;

} GraphObj;


/*** Constructors-Destructors ***/
Graph newGraph(int n){
	//check statement
	
	//code creating a new graph 
	Graph G = malloc(sizeof(GraphObj)); //heap memory
	G->nbor = malloc(sizeof(List)* (n+1));
	G->color = malloc(sizeof(int)* (n+1));
	G->parent = malloc(sizeof(int)* (n+1));
	G->discover = malloc(sizeof(int)* (n+1));
	G->finish = malloc(sizeof(int)* (n+1));
	G->order = n;
	G->size = 0;
	
	//for loop to initialize
	for(int i=0; i<(n+1); i++){
		G->nbor[i] = newList();
		G->color[i] = WHITE; //start as all white
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	return G;
}
void freeGraph(Graph* pG){
	//check statement

	if((pG != NULL) && (*pG!=NULL)){
		//forgot this in my pa4 :( shit
		for(int i =1; i<=(*pG)->order; i++){
			freeList(&(*pG)->nbor[i]);
		}
		//free all heap memory for no leaks and set graph to null
		free((*pG)->nbor);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->discover);
		free((*pG)->finish);
		free(*pG);
		*pG = NULL; 
	}
}

/*** Access functions ***/
int getOrder(Graph G){
	
	return G->order;
}

int getSize(Graph G){
	
	return G->size;
}

int getParent(Graph G, int u){
	//check statement(s)
	
	return G->parent[u];

}

int getDiscover(Graph G, int u){
	//check statement(s)
	
	return G->discover[u];

}

int getFinish(Graph G, int u){
	//check statement(s)
	if(G == NULL){
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		exit(1);
	}
	return G->finish[u];
}

/*** Manipulation procedures ***/ //the hard ones 

void addEdge(Graph G, int u, int v){
	//check statement
	// if(G == NULL){
	// 	exit(1);
	// }
	// if(u<1 || u>getOrder(G)){
	// 	exit(1);
	// }
	// if(v<1 || v>getOrder(G)){
	// 	exit(1);
	// }
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
	// if(G == NULL){
	// 	exit(1);
	// }
	// if(u<1 || u>getOrder(G)){
	// 	exit(1);
	// }
	// if(v<1 || v>getOrder(G)){
	// 	exit(1);
	// }

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

static int time; //trying approach number 2 
//static List stack;

void DFS(Graph G, List S){ //******* gotta change this shit!!!!
	//check statement
	
	// if(!(length(S) == getOrder(G))){ // length(S)==n where n = getOrder(G)
	// 	exit(1);
	// }
	//using section 22.3 of textbook, and the most recent HW and graph theory handout
	//checks are not necessary but whatever 
			// DFS.G/
		// 1 2 3 4 5 6 7
		// for each vertex u 2 G:V u:color D WHITE u:􏰊 D NIL
		// timeD0
		// for each vertex u 2 G:V
		// if u:color == WHITE DFS-VISIT.G; u/
	List temp = copyList(S);
	clear(S);
	for(int i = 1; i<G->order; i++){
		G->color[i] = WHITE;
		G->parent[i] = NIL;
	}
	time = 0;
	for(moveFront(temp); index(temp)!=-1; moveNext(temp)){
		if(G->color[get(temp)] == WHITE){
			DFS_visit(G, get(temp), S);
		}
	}
	freeList(&temp);
}

void DFS_visit(Graph G, int u, List S){
	//using section 22.3 of textbook, and the most recent HW 
		// 		DFS-VISIT.G;u/
		// 1 2 3 4 5 6 7 8 9
		// 10
		// // white vertex u has just been discovered
		// time D time C 1
		// u:d D time
		// u:color D GRAY
		// foreach􏰈2G:AdjŒu􏰇 //exploreedge.u;􏰈/
		// if 􏰈:color == WHITE 􏰈:􏰊 D u
		// DFS-VISIT.G;􏰈/ u:color D BLACK
		// timeDtimeC1 u:fDtime
		// // blacken u; it is finished

	G->color[u] = GRAY;
	time = time+1; //not sure the problem
	G->discover[u] = time;
	for(moveFront(G->nbor[u]); index(G->nbor[u])!=-1; moveNext(G->nbor[u])){
		if(G->color[get(G->nbor[u])] == WHITE){
			G->parent[get(G->nbor[u])] = u;
			DFS_visit(G, get(G->nbor[u]), S);
		}
	}
	G->color[u] = BLACK;
	time = time+1;
	G->finish[u] = time;
	//now prepend onto new stack list 
	prepend(S, u); //FIX prepend

} 

/*** Other operations ***/
Graph transpose(Graph G){
	//stuff
	
	Graph tran = newGraph(getOrder(G)); //transpose G
	tran->order = getOrder(G);
	tran->size = getSize(G);

	for(int i=1; i<=getOrder(G); i++){
		if(length(G->nbor[i])>0){ //if list of adj is not 0 
			for(moveFront(G->nbor[i]); index(G->nbor[i])!=-1; moveNext(G->nbor[i])){
				addArc(tran, get(G->nbor[i]), i); //add arc to new transpose
			}
		}
	}
	return tran; 

}

Graph copyGraph(Graph G){
	//stuff
	// same shit as transpose! changed variable to C just for 'copy' and helps me understand whats going on 
	
	Graph C = newGraph(getOrder(G)); //transpose G
	C->order = getOrder(G);
	C->size = getSize(G);

	for(int i=1; i<=getOrder(G); i++){
		if(length(G->nbor[i])>0){ //if list of adj is not 0 
			for(moveFront(G->nbor[i]); index(G->nbor[i])!=-1; moveNext(G->nbor[i])){
				addArc(C, i, get(G->nbor[i])); //add arc to new transpose
			}
		}
	}
	return C; 
}

void printGraph(FILE* out, Graph G){
	// //CHeck statement
	// if(G == NULL){
	// 	exit(1);
	// }
	//loop that goes through and prints
	for(int i=1; i<=getOrder(G); i++){
		//print stuff
		fprintf(out, "%d: ", i);        					 // ** ??? *** ///
		printList(out,G->nbor[i]); // adjacent
		fprintf(out, "\n"); //new line

	}
}