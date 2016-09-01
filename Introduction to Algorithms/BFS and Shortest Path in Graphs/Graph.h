//Program 4: Graph
//Justin Wong jujwong@ucsc.edu
//CS101 Tantalo Fall 14

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include "List.h"
#define UNDEF -255
#define NIL 0

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
//returns a Graph pointing at new GraphObj
Graph newGraph(int n);
//frees memory associated with Graph *pG
void freeGraph(Graph* pG);

/*** Access functions ***/
//returns # of vertices in Graph G
int getOrder(Graph G);
//returns size
int getSize(Graph G);
//returns parent of vertex u
//Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);
//Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u);
//Pre: 1 <= u <= getOrder(G)
void getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);

#endif
