#include <stdio.h>    //Standard I/O functions and definitions
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>  //String manipulation functions
#include <unistd.h>
#include "history.h"

struct Cmd* init_history(){
	
	struct Cmd *history =  malloc(10*sizeof(struct Cmd));
	return history;
	
}

void add_history(char *str, int exitStatus, int cmdPos, struct Cmd *history){ //Adds an entry to the history

		strncpy(history[cmdPos].cmd, str, sizeof(history[cmdPos].cmd));
		history[cmdPos].exitStatus = exitStatus;

}

void clear_history(struct Cmd *history){ //Frees all malloc’d memory in the history

 	free(history);

}

void print_history(int firstSequenceNumber, int cmdCount, struct Cmd *history){ //Prints the history to stdout

	int n = 0;
	int pos = firstSequenceNumber;
	int p = 0;

	if(cmdCount < 10){
		while(n <= cmdCount){
			p = (pos-1)%10;
			printf("%d [%d] %s\n", pos, history[p].exitStatus, history[p].cmd);
			pos = pos+1;
			n = n+1;	
		}
	}else{
		while(n < 10){
			p = (pos-1)%10;
			printf("%d [%d] %s\n", pos, history[p].exitStatus, history[p].cmd);
			pos = pos+1;
			n = n+1;	
		}
	}
}
