//Program 5: Graph
//Justin Wong jujwong@ucsc.edu
//CS101 Tantalo Fall 14

#include <stdlib.h>
#include "Graph.h"

static void inSort(List L, int u);

#define WHITE 10000001
#define BLACK 19999991
#define GRAY -6666669

struct GraphObj {
   List *array;
   int *colors;
   int *parents;
   int *discover;
   int *finish;
   int order;  //# of vertices
   int size;  //# of edges
};


//Returns a graph pointing to a new GraphObj 
//with n vertices and no edges
Graph newGraph(int n){
   Graph new = malloc(sizeof(struct GraphObj));
   new->array = calloc(n + 1, sizeof(List));
   new->colors = calloc(n + 1, sizeof(int));
   new->parents = calloc(n + 1, sizeof(int));
   new->discover = calloc(n + 1, sizeof(int));
   new->finish = calloc(n + 1, sizeof(int));
   new->order = n;
   new->size = 0;
   for(int i = 0; i < n+1; ++i){
      new->array[i] = newList();
	  new->colors[i] = WHITE;
	  new->parents[i] = NIL;
	  new->discover[i] = UNDEF;
	  new->finish[i] = UNDEF;
   }
   return new;
}

//Frees memory allocated for graph
void freeGraph(Graph* pG){
   Graph freed = *pG;
   for(int i = 0; i < (freed->order) + 1; ++i){
      freeList(&(freed->array[i]));
   }
   free(freed->array);
   free(freed->colors);
   free(freed->parents);
   free(freed->discover);
   free(freed->finish);
   free(*pG);
   *pG = NULL;
}


/*** Access Functions ***/
//returns # of vertices
int getOrder(Graph G){
   if(G == NULL){
      printf("getOrder: null Graph\n");
	  return UNDEF;
   }
   return G->order;
}
//return # of edges
int getSize(Graph G){
   return G->size;
}
// Returns parents of vertex u
// Pre : 1 <= U <= getOrder(G)
int getParent(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("getParent: incorrect parameter");
      return 0;
   }
   return G->parents[u];
}

// Returns discovery time from DFS source to vertex u
// Pre : 1 <= U <= getOrder(G)
int getDiscover(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("getDiscover: incorrect parameter");
      return 0;
   }
   return G->discover[u];
}
//returns finish time
//Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("getFinish: invalid vertex \n");
      return 0;
   }
   return G->finish[u];
}

/*** Manipulation Procedures ***/

//Pre: 1 <= u <= n and 1<= v <= n
void addEdge(Graph G, int u, int v){
   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("addEdge: Pre failed");
	  printf("%d %d\n", u, v);
	  return;
   }
   List U = G->array[u];
   List V = G->array[v];
   inSort(U, v);
   inSort(V, u);
}

static void inSort(List L, int u){
   if(length(L) == 0){
      append(L, u);
      return;
   }
   for(moveTo(L,0); getIndex(L) >= 0; moveNext(L)){
      int big = getElement(L);
      if(u < big){
	     insertBefore(L, u);
	     break;
	  }
   }
   if(getIndex(L) == -1){
      append(L, u);
   }
}

//PRE: both int arguments must be between 1 to getOrder(G)
void addArc(Graph G, int u, int v){
   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
    printf("addArc: preconditions not met");
	printf("%d %d\n", u, v);
    return;
  }
  List U = G->array[u];
  inSort(U, v);
}

//DFS Algorithm
//Pre: getLength(s) == getOrder(G)
void DFS(Graph G, List s){
   if(length(s) != getOrder(G)){
      printf("DFS: list and graph not same size\n");
	  return;   
   }
   int time = 0;
   int size = length(s);
   void Visit(int vertex){
      time++;
	  G->discover[vertex] = time;
	  G->colors[vertex] = GRAY;
      List adj = G->array[vertex];
	  for(moveTo(adj, 0); getIndex(adj) >= 0; moveNext(adj)){
	     int vert = getElement(adj);
	     if(G->colors[vert] == WHITE){
		    G->parents[vert] = vertex;
			Visit(vert);
		 }
	  }
	  G->colors[vertex] = BLACK;
	  time++;
	  G->finish[vertex] = time;
	  prepend(s, vertex);
   }
   for(moveTo(s, 0); getIndex(s) >= 0; moveNext(s)){
      int vertex = getElement(s);
	  G->colors[vertex] = WHITE;
      G->parents[vertex] = NIL;
   }
   for(moveTo(s, 0); getIndex(s) >= 0; moveNext(s)){
      int vertex = getElement(s);
	  if(G->colors[vertex] == WHITE) Visit(vertex);
   }
   for(;size > 0; size--){
      deleteBack(s);
   }
}


/*** Other Operations ***/

void printGraph(FILE* out, Graph G){
   if(out == NULL || G == NULL){
      printf("Parameters are null");
      return;
   }
   for(int i = 1; i < getOrder(G) + 1; ++i){
      fprintf(out, "%d: ", i);
	  printList(out, G->array[i]);
      fprintf(out, "\n");
   }
}

//returns the transpose of G
//adj lists are reversed
Graph transpose(Graph G){
 int n = G->order;
  Graph new = malloc(sizeof(struct GraphObj)); 
  new->array = calloc (n + 1, sizeof(List)); 
  new->colors = calloc(n + 1, sizeof(int)); 
  new->parents = calloc(n + 1, sizeof(int)); 
  new->discover = calloc(n + 1, sizeof(int));
  new->finish = calloc(n+1, sizeof(int));
  new->order = G->order;
  new->size = G->size;
  for (int i = 0; i < n + 1; i++){
    new->array[i] = newList();
    new->colors[i] = WHITE;
    new->parents[i] = NIL;
    new->discover[i] = UNDEF;
    new->finish[i] = UNDEF;
  }
  for(int i = 0; i < n + 1; i++){
    List g = G->array[i];
    for(moveTo(g, 0); getIndex(g) >= 0; moveNext(g)){
      append(new->array[getElement(g)], i);
    }
  }
  return new;
}

// copies Graph G
Graph copyGraph(Graph G){
  int n = G->order;
  Graph new = malloc(sizeof(struct GraphObj)); 
  new->array = calloc (n + 1, sizeof(List)); 
  new->colors = calloc(n + 1, sizeof(int)); 
  new->parents = calloc(n + 1, sizeof(int)); 
  new->discover = calloc(n + 1, sizeof(int));
  new->finish = calloc(n+1, sizeof(int));
  new->order = G->order;
  new->size = G->size;
  for (int i = 0; i < n + 1; i++){
    new->array[i] = newList();
    List g = G->array[i];
    // copies over the entries
    for(moveTo(g, 0); getIndex(g) >= 0; moveNext(g)){
      append(new->array[i], getElement(g));
    }
    new->colors[i] = WHITE;
    new->parents[i] = NIL;
    new->discover[i] = UNDEF;
    new->finish[i] = UNDEF;
  }
  return new;
}

