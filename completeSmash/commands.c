#include <stdio.h>    //Standard I/O functions and definitions
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>  //String manipulation functions
#include <unistd.h>
#include<sys/wait.h> 
#include <fcntl.h> 
#include "smash.h"
#include "history.h"

int executeCommand(char *str, int cmdPos, int seqNum, struct Cmd *history, int cmdCount){

	char save[4096] = "";
	strncpy(save, str, 4096);
	char *args[10];
	int place = 0;
	int exitStatus = 0;
	int hisCheck = 0;
	int state = 0;
	char *fileNameOut;
	int readIn = 0, sendOut = 0, hold = 0, status;

	args[0] = NULL;		

	if(strstr(str, "|")){
		int ret = executePipeCommand(str, cmdPos, seqNum, history, cmdCount);
		add_history(save, ret, cmdPos, history);
		return ret;
	}

	char *word = strtok(str, " ");
	while(word != NULL){
		args[place] = word;
		if(strstr(word, ">") != NULL){
			sendOut = 1;
			hold = place;
		}
		if(strstr(word, "<") != NULL){
			readIn = 1;
			hold = place;
		}
		word = strtok(NULL, " ");
		place = place+1;
	}
	
	if(sendOut == 1){
		int kid = fork();
		if(kid<0){
			perror("Fork kid failed");
		}
		
		if(kid == 0){
			if(strlen(args[hold]) == 1){
				fileNameOut = args[hold+1];
			}else{
				fileNameOut = args[hold];
				fileNameOut++;
			}

			//makefile
			int fd = open(fileNameOut, O_CREAT|O_WRONLY, 0644);
			dup2(fd, 1);
			close(fd);

			args[hold] = NULL;
		}else{
			sendOut = 0;
			int newEx = wait(&status);
			return newEx;
		}
		
	}

	if(args[0] != NULL){
		args[place] = NULL;

		if(strcmp(args[0], "exit") == 0){
			exitStatus = 0;	
			clear_history(history);	
			exit(0);
		}else if(strcmp(args[0], "cd") == 0){
			if(args[1] == NULL){
				exitStatus = 0;
			}else{
				state = chdir(args[1]);
				if(state == 0){
					printf("%s\n", args[1]);
					exitStatus = 0;
				}else{
					perror("Error");
					exitStatus = 1;
				}
			}
		}else if(strcmp(args[0], "history") == 0){
			exitStatus = 0;
			hisCheck = 1;
		}else{
			exitStatus = executeExternalCommand(args[0], args, readIn, hold);
		}
		add_history(save, exitStatus, cmdPos, history);
		if(hisCheck == 1){
			print_history(seqNum, cmdCount, history);
		}
	}else{
		exitStatus = 6;
	}

	if(sendOut == 1){
		exit(0);
	}
	return exitStatus;
}

int executeExternalCommand(char *des, char *args[], int fileIn, int hold){
	int result;
	int forkMe;
	int stat;
	char *fileName = NULL;

	forkMe = fork();
	if(forkMe < 0){
		perror("Error: ");
	}

	if(forkMe == 0 && fileIn == 1){
		if(strlen(args[hold]) == 1){
			fileName = args[hold+1];
		}else{
			fileName = args[hold];
			fileName++;
		}

		printf("%s\n", fileName);
		//makefile
		int fd = open(fileName, O_RDONLY);
		dup2(fd, 0);
		close(fd);

		args[hold] = NULL;

		result = execvp(des, args);
		if(result == -1){
			perror("Error: ");
		}	
		exit(-1);
	}else if(forkMe == 0){
		result = execvp(des, args);
		if(result == -1){
			perror("Error: ");
		}
		exit(-1);
	}else{
		wait(&stat);
		result = WEXITSTATUS(stat);
	}
	
	return result;
	
}

int executePipeCommand(char *str, int cmdPos, int seqNum, struct Cmd *history, int cmdCount){
	char *args[10];
	char *word = strtok(str, "|");
	int place = 0;
	int fd[2];
	int res = pipe(fd);
	int statA, statB;
	int ret;

	if(res == -1){
		perror("Error: ");
	}

	while(word != NULL){
		args[place] = word;
		word = strtok(NULL, "|");
		place = place+1;
	}
	args[place] = NULL;

	int kid1 = fork();
	if(kid1<0){
		perror("Fork kid1 failed");
	}

	if(kid1 == 0){
		dup2(fd[1],1);
		close(fd[0]);
		close(fd[1]);

		ret = executeCommand(args[0], cmdPos, seqNum, history, cmdCount);
		exit(ret);
	}

	int kid2 = fork();
	if(kid2<0){
		perror("Fork kid2 failed");
	}	

	if(kid2 == 0){
		dup2(fd[0],0);
		close(fd[0]);
		close(fd[1]);

		ret = executeCommand(args[1], cmdPos, seqNum, history, cmdCount);
		exit(ret);
	}

	close(fd[0]);
	close(fd[1]);

	wait(&statA);
	wait(&statB);

	if(statA != 0){
		return statA;
	}else if(statB != 0){
		return statB;
	}else{
		return 0;
	}
}
