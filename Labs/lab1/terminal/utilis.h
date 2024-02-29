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

typedef enum{
    STOP_RUNNING,
    CONTINUE_RUNNING
}run_t;

typedef enum{
    NOT_BUILTIN_COMMAND,
    BUILTIN_COMMAND
}builtin_command_t;

/* flag to determine when to exit program */
run_t              should_run ;  
/* flag to determine if the command is builtin or not */
builtin_command_t command_type ;

/*
FUNCTIONS DEFINATIONS
*/
void write_log(char characters[]);
void on_child_exit();
void setup_environment();
bool exit_shell(void);
void read_input_command(void);
void tokinize_command(void);
builtin_command_t builtin_commands(void);
void split_quoted_string(void);
void set_enviroment_variable_value(char *ip);
void get_enviroment_variable_value(char *ip, int index);
void echo_command(void);
void export_command(void);
void goto_root_path(void);
void cd_command(void);
void handle_enviroment_variable(void);
void shell();


#endif