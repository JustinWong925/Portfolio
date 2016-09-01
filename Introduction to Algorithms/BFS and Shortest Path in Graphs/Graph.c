//Program 4: Graph
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
   int *distances;
   int order;  //# of vertices
   int size;  //# of edges
   int source;
};


//Returns a graph pointing to a new GraphObj 
//with n vertices and no edges
Graph newGraph(int n){
   Graph new = malloc(sizeof(struct GraphObj));
   new->array = calloc(n + 1, sizeof(List));
   new->colors = calloc(n + 1, sizeof(int));
   new->parents = calloc(n + 1, sizeof(int));
   new->distances = calloc(n + 1, sizeof(int));
   new->source = NIL;
   new->order = n;
   new->size = 0;
   for(int i = 0; i < n+1; ++i){
      new->array[i] = newList();
	  new->colors[i] = WHITE;
	  new->parents[i] = NIL;
	  new->distances[i] = INF;
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
   free(freed->distances);
   free(*pG);
   *pG = NULL;
}


/*** Access Functions ***/
int getOrder(Graph G){
   return G->order;
}

int getSize(Graph G){
   return G->size;
}

int getSource(Graph G){
   return G->source;
}

// Returns parents of vertex u or NIL
// Pre : 1 <= U <= getOrder(G)
int getParent(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("getParent: incorrect parameter");
      return 0;
   }
   return G->parents[u];
}

// Returns distance from BFS source to vertex u
// Pre : 1 <= U <= getOrder(G)
int getDist(Graph G, int u){
   if(getSource(G) == NIL){
      return INF;
   }
   if(u < 1 || u > getOrder(G)){
      printf("getDist: incorrect parameter");
      return 0;
   }
   return G->distances[u];
}

// appends the vertices of shortest path in G from source to U
// or appends to L NIL if no path exists.
// Pre : getSource(G) != NIL
// Pre : 1 <= U <= getOrder()
void getPath(List L, Graph G, int u){
   if(getSource(G) == NIL){
      printf("Source is NIL.");
   }
   if(u < 1 || u > getOrder(G)){
      printf("getPath: incorrect parameter");
      return;
   }
   int s = G->source;
   if( u == s){
      prepend(L, s);
      return;
   } else if (G->parents[u] == NIL){
      append(L, NIL);
   } else {
      prepend(L, u);
      getPath(L, G, G->parents[u]);
   }
}

/*** Manipulation Procedures ***/

void makeNull(Graph G){
   for(int i = 0; i < G->order + 1; ++i){
   clear(G->array[i]);
   }
}

//PRE: both int arguments must be between 1 to getOrder(G)
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
  }
  List U = G->array[u];
  inSort(U, v);
}


//BFS algorithm from pseudo code
//intitalize everything to white/empty
//create a List object as Q
//checks the vertex attributes in relation to source vertex
//changes color if discovered
//and will free the queue
void BFS(Graph G, int s){
  for (int u = 0; u < G->order + 1; u++){
    if(u != s){
      G->colors[u] = WHITE;
      G->distances[u] = INF;
      G->parents[u] = NIL;
    }
  }
  G->source = s;
  G->colors[s] = GRAY;
  G->distances[s] = 0;
  G->parents[s] = NIL;
  List Q = newList();
  prepend(Q, s);
  while(length(Q) > 0){
    int u = back(Q);
    deleteBack(Q);
    List adj = G->array[u];
    for(moveTo(adj, 0);getIndex(adj) >= 0 ; moveNext(adj)){
      int vertex = getElement(adj);
      if(G->colors[vertex] == WHITE){
	G->colors[vertex] = GRAY;
	G->distances[vertex] = G->distances[u] + 1;
	G->parents[vertex] = u;
	prepend(Q, vertex);
      }
    }
    G->colors[u] = BLACK;
  }
  freeList(&Q);
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







