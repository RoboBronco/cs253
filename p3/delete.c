#include "delete.h"
#include <stdio.h>    //Standard I/O functions and definitions
#include <string.h>   //String manipulation functions
#include <stdlib.h>   //Standard library (includes exit function)


int doDelete(char *line1, char *line2){

  char str[1024];
  int count = 0;
  int l1;
  int l2;

  sscanf(line1, "%d", &l1);
  sscanf(line2, "%d", &l2);
    
  while(fgets(str, sizeof(str), stdin) != NULL){
    if(strlen(str)>=1023){
      fprintf(stderr, "Line exceeded 1023 characters\n");
      exit(1);
    }
    
    count = count+1;

    if( (count<l1) || (count>l2) ){
      printf("%s", str);
    }
    
  }

  printf("\n");
  return 0;
}
