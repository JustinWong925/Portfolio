//Program 2: Lexicographic Insertion Sort
//Justin Wong jujwong@ucsc.edu
//CS101 Tantalo Fall 14

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 160


List inSort(char** array, int length){
   List list = newList();
   if(length > 0) append(list, 0);
   for(int j = 1; j < length; ++j){
      char *temp = array[j];
	  int index = j - 1;
	  moveTo(list, index);
	  while(index > -1 && strcmp(temp, array[getElement(list)]) < 1){
	     index--;
		 movePrev(list);
	  }
	  if(getIndex(list) == -1){
	     prepend(list, j);
	  }else{
	     insertAfter(list, j);
	  }
   }
   return list;
}

void freeall(char** lines, int linecount, List list){
  for (int i = 0; i < linecount; i++){
    free(lines[i]);
  }
  free(lines);
  freeList(&list);
}

char** read(FILE* input, int lines){
   char** array = malloc(sizeof(char**) * lines);
   char line[MAX_LEN];
   for(int i = 0; i < lines; ++i){
      fgets(line, MAX_LEN, input);
	  array[i] = strdup(line);
   }
   return array;
}

int main(int argc, char* argv[]){
   int count = 0;
   char line[MAX_LEN];
   
   if(argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
	  return 1;
   }
   
   FILE* input = fopen(argv[1], "r");
   FILE* output = fopen(argv[2], "w");
   if(input == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
	  return 1;
   }else if(output == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
	  return 1;   
   }
   
   
   while(fgets(line, MAX_LEN, input) != NULL){
      count++;
   }
   
   fclose(input);
   input = fopen(argv[1], "r");
   char** lines = read(input, count);
   List list = inSort(lines, count);
   for(moveTo(list, 0); getIndex(list) >= 0; moveNext(list)){
      fprintf(output, "%s", lines[getElement(list)]);
   }
   fclose(input);
   fclose(output);
   freeall(lines, count, list);
   return(0);
}










