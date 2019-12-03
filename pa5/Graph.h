// Connor Monson 1461818 cmonson@ucsc.edu
// pa4 11/11/17
// Graph.h
//----------------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h> //do I need? 
#define NIL 0//Undefined vertex label, all valid vertex labels are positive integers
#define UNDEF 0//Undefined discover/finish time
#include "List.h"

typedef struct GraphObj* Graph;

//------------------------------------------------------------
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

//------------------------------------------------------------
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

//------------------------------------------------------------
/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v);
void addEdge(Graph G, int u, int v);
void DFS(Graph G, List S);
void DFS_visit(Graph G, int u, List S);

//------------------------------------------------------------
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
//------------------------------------------------------------
#endif
