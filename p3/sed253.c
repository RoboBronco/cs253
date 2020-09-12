//-----------------------------------------------------------------------------
//
// NAME
//  sed253 -- Simplified editor
//
// SYNOPSIS
//  sed253
//  sed253 -s pattern string
//  sed253 -d line1 line2
//
// DESCRIPTION
//  Simplified editor.  Copies lines read from stdin to stdout.  Options:
//
//  -s Substitute every occurrence of pattern with string
//  -d Delete line1 through line2 inclusive
//
// ERRORS
//  Prints usage message and exits abnormally for invalid commands.  Prints an
//  error message and exits abnormally for other issues.
//
// LIMITATIONS
//  Lines of text are limited to a maximum of 1023 chars.
//
// AUTHORS
//  Epoch...................................................................jrc
//
//-----------------------------------------------------------------------------

//Bring in the definitions for our helper functions
#include "copy.h"
#include "substitute.h"
#include "delete.h"
#include <stdio.h>    //Standard I/O functions and definitions
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>  //String manipulation functions

//-----------------------------------------------------------------------------
//  usage -- Prints a usage message and exits with status=2
//-----------------------------------------------------------------------------
void usage() {
    
    //Print the usage message to stderr
    fprintf(stderr, "usage: sed253 [-s pattern string] [-d line1 line2]\n");
    
    //Force an exit.  This is equivalent to return 1 in main()
    exit(1);                //Exit status is 1
    
}

//-----------------------------------------------------------------------------
// main -- the main function
//-----------------------------------------------------------------------------
int main(int argc, char **argv) {

  char *pattern;
  char *swap;
  char *line1;
  char *line2;
  
  int exitStatus = 0; //normal exit status
  
  //check for options//
  if(argc==4){						//If there are 4 arguments
    if(strcmp(argv[1], "-s")==0){			//If the 2nd argument is -s
      pattern = argv[2];
      swap = argv[3];
      
      if((strlen(pattern)==0) || (strlen(swap)==0)){	//Check for invalid pattern or swap
	usage();
      }
     
      doSubstitute(pattern, swap);			//Substitute swap for pattern
     
    }else if(strcmp(argv[1], "-d")==0){			//If the 2nd argument is -d
      line1 = argv[2];
      line2 = argv[3];
      
      if((line1==0) || (line2==0)){			//Check for invalid lines
	usage();
      }
      
      doDelete(line1, line2);				//Delete desired line range	
      
    }else{						//If there are 4 arguments, used incorrectly
      usage();						//Exit abnormally
    }
  }else if(argc==1){					//If there is only 1 argument
    doCopy();						//Run copy function
  }else{						//There are 2,3, or >4 arguments
    usage();						//Exit abnormally
  }

  return exitStatus;
}

