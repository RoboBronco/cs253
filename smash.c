#include <stdio.h>    //Standard I/O functions and definitions
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>  //String manipulation functions
#include <signal.h>
#include "smash.h"
#include "history.h"
#define MAXLINE 4096


void catch_ctrlC(int sig)
{
	if(sig == SIGINT){
		printf("\n$ ");
	}
}

int main(int argc, char **argv) {
	int cmdPos = 0;
	int seqNum = 1;
	int count = 0;
	int cmdCount = 0;

	setvbuf(stdout,NULL,_IONBF,0);
	char bfr[MAXLINE] = "";
	signal(SIGINT, catch_ctrlC); //Catch the interrupt

	fputs("$ ",stderr); //Output the first prompt
	
	struct Cmd *history = init_history();

	//Loop reading commands until EOF or error
	while ((fgets(bfr, MAXLINE, stdin) != NULL) && !(feof(stdin))){
		
		if(strlen(bfr)>=MAXLINE){
			fprintf(stderr, "Line exceeded 4096 characters\n");
		} 

		bfr[strlen(bfr) - 1] = '\0'; //Replace newline with NUL
		int status = executeCommand(bfr, cmdPos, seqNum, history, cmdCount);	
		if(status != 6){
			cmdCount = cmdCount + 1;
			if(cmdPos < 9){
				cmdPos = cmdPos + 1;
			}else{
				cmdPos = 0;
			}

			if(count < 9){
			}else{
				seqNum = seqNum + 1;
			}
			count = count +1;
		}
		fputs("$ ",stderr);
	}

	clear_history(history);
	return 0;

}