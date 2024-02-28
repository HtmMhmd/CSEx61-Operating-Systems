#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 128
#define MAX_NUM_ARGS 10

char cmd[MAX_CMD_LENGTH];
char *args[MAX_NUM_ARGS];
char *token;
int status;
pid_t pid;