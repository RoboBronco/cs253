#ifndef HISTORY_H
#define HISTORY_H

//Define the layout of a single entry in the history array
struct Cmd {
	char cmd[4096];
	int exitStatus;
};
//A saved copy of the user’s command string
//The exit status from this command

//Define the maximum number of entries in the history array
#define MAXHISTORY 10
//Smash will save the history of the last 10 commands

//Function prototypes for the command history feature
struct Cmd* init_history(void); //Builds data structures for recording cmd history
void add_history(char *cmd, int exitStatus, int cmdNum, struct Cmd *history); //Adds an entry to the history
void clear_history(struct Cmd *history); //Frees all malloc’d memory in the history
void print_history(int firstSequenceNumber, int cmdCount, struct Cmd *history); //Prints the history to stdout

#endif /*HISTORY_H*/
