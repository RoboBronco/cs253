#include "substitute.h"
#include <stdio.h>    //Standard I/O functions and definitions
#include <string.h>   //String manipulation functions
#include <stdlib.h>   //Standard library (includes exit function)


int doSubstitute(char *pattern, char *sub){

  char str[1024];
  int patLen = strlen(pattern);
  
  while(fgets(str, sizeof(str), stdin) != NULL){
    if(strlen(str)>=1023){
      fprintf(stderr, "Line exceeded 1023 characters\n");
      exit(1);
    }
   
    while(strstr(str, pattern)){
      char firstHalf[1024] = "";
      
      strncpy(firstHalf, str, (strlen(str) - strlen((strstr(str, pattern)))));
      
      char *secHalfPat = strstr(str, pattern);
      
      char *secHalf = secHalfPat + patLen;
      
      strncat(firstHalf, sub, 1024);
      
      strncat(firstHalf, secHalf, 1024);
      
      strncpy(str, firstHalf, 1024);
    }
  
  printf("%s", str);
  }

  return 0;
}
