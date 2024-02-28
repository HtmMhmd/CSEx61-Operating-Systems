#ifndef UTILIS_H
#define UTILIS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_LINE 80 /* The maximum length command */
int INPUT_COMMAND_LENGTH;
char *args[MAX_LINE/2 + 1]; /* command line arguments */
int background;
char input[MAX_LINE];
/*
FUNCTIONS DECLERATION
*/
void write_log(char characters[]);
void on_child_exit();
void setup_environment();
bool exit_shell(void);
void read_input_command(void);
void tokinize_command(void);
bool builtin_commands(void);
void set_enviroment_variable_value(char *ip);
void get_enviroment_variable_value(char *ip, int index);
void shell();


#endif