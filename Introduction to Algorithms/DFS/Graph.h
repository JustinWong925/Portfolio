//Program 5: Graph
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
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
//inserts new edge from u to v
//Pre: 1 <= u | v < getOrder(G)
void addEdge(Graph G, int u, int v);
//inserts directed edge from u to v
//Pre: 1 <= u | v < getOrder(G)
void addArc(Graph G, int u, int v);
//runs DFS, stores vertices in decreasing finish times
//Pre: getLength(s) == n
//Pre: S contains premutations of integers {1,2,...n}
// n = getOrder(G)
void DFS(Graph G, List s);

/*** Other operations ***/
//prints adj list
void printGraph(FILE* out, Graph G);
//returns transpose
Graph transpose(Graph G);
//returns a copy of G
Graph copyGraph(Graph G);

#endif
