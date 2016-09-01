//Program 5: Find Components
//Justin Wong jujwong@ucsc.edu
//CS101 Tantalo Fall 14

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Graph.h"
#define MAX_LEN 165

int main(int argc, char* argv[]){
   //checks # arguments
   char line[MAX_LEN];
   if(argc != 3){
      printf("Incorrect number of inputs");
	  exit(1);
   }
   //checks if files are valid
   FILE* input = fopen(argv[1], "r");
   FILE* output = fopen(argv[2], "w");
   if(input == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      return 1;
   } else if (output == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
	  return 1;
   }
   // read each line of input file, then count and print tokens
   fgets(line, MAX_LEN, input);
   int numVertex = 0;
   sscanf(line, "%d", &numVertex);
   List S = newList();
   for(int i = 1; i <= numVertex; ++i) append(S, i);
   //creating new graph
   Graph G = newGraph(numVertex);
   while(fgets(line, MAX_LEN, input) != NULL){
      int vert1 = 0;
	  int vert2 = 0;
	  sscanf(line, "%d %d", &vert1, &vert2);
	  if(vert1 == 0 && vert2 == 0) break;
	  addArc(G, vert1, vert2);   
   }

   DFS(G, S);
   fprintf(output, "Adjacency list representation of G:\n");
   printGraph(output, G);
   Graph T = transpose(G);
   DFS(T, S);
   
   int numScc = 0;
   for(moveTo(S, 0); getIndex(S) >= 0; moveNext(S)){
      if(getParent(T, getElement(S)) == NIL) numScc++;
   }
   //putting components into array list
   List Scc[numScc];
   int i = numScc;
   for(moveTo(S, 0); getIndex(S) >= 0; moveNext(S)){
      if(getParent(T, getElement(S)) == NIL){
	     i--;
		 Scc[i] = newList();
	  }
      if(i == numScc) break;
	  append(Scc[i], getElement(S));
   }
   //printing out the strongly connected components
   fprintf(output, "\nG contains %d strongly connected components:", numScc);
   for(int j = 0; j < numScc; ++j){
      fprintf(output, "\n");
	  fprintf(output, "Component %d: ", j + 1);
	  printList(output, Scc[j]);
	  freeList(&(Scc[j]));
   }
   //freeing memory and closing files
   fprintf(output, "\n");
   freeGraph(&G);
   freeGraph(&T);
   freeList(&S);
   fclose(input);
   fclose(output);
   return(0);
  
}
