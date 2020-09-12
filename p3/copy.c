#include "copy.h"
#include <stdio.h>    //Standard I/O functions and definitions
#include <string.h>   //String manipulation functions
#include <stdlib.h>   //Standard library (includes exit function)

int doCopy(){
  char str[1023];
  
  while((fgets(str, sizeof(str), stdin))){
    if(strlen(str)>=1023){
      fprintf(stderr, "Line exceeded 1023 characters\n");
      exit(1);
    }    

    printf("%s", str);
  }
  
  return 0;
  
}
