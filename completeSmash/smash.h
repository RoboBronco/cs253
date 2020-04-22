#ifndef SMASH_H
#define SMASH_H
//-----------------------------------------------------------------------------
//
// NAME
//  substitute.h -- Define prototypes and symbols for using substitute.c
//
//-----------------------------------------------------------------------------
#include "history.h"

// Define function prototypes
int executeCommand(char *str, int cmdPos, int seqNum, struct Cmd* history, int cmdCount);
int executeExternalCommand(char *des, char *args[], int fileIn, int hold);
int executePipeCommand(char *str, int cmdPos, int seqNum, struct Cmd *history, int cmdCount);

#endif /*SMASH_H*/
