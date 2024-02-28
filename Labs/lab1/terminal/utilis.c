#include "utilis.h"

void write_log(char characters[]){
    /*
    write input text into log.txt file
    */
    FILE *log_file = fopen("log.txt", "a");
    if (log_file == NULL) {
        printf("Error opening file.\n");
        return ;
    }
    fprintf(log_file, "%s\n", characters);
    fclose(log_file);
}

void on_child_exit(){
    /*
    wait for the termination of any child processes in a non-blocking manner.
    */
    while (waitpid(-1, NULL, WNOHANG) > 0);
    // Write to log file
    write_log("Child terminated");
}

void setup_environment() {
    /* 
    Change to current working directory
    */
    chdir(getenv("PWD"));
}

bool exit_shell(void){
    /* 
    exit if input command is exit
    */
    return (strcmp(args[0], "exit") == 0);
}

void read_input_command(void){
    /*
    get the input command
    */
    fgets(input, MAX_LINE, stdin);
    input[strcspn(input, "\n")] = 0;  // remove trailing newline
}

void tokinize_command(void){
    /*
    split input command into argumants (tokens separated by spaces) and stores in args.
    return : INPUT_COMMAND_LENGTH
    */
    char *token = strtok(input, " ");
    INPUT_COMMAND_LENGTH = 0;
    while (token != NULL) {
        args[INPUT_COMMAND_LENGTH ++] = token;
        token = strtok(NULL, " ");
    }
    args[INPUT_COMMAND_LENGTH] = NULL;
    for (int j = 1; j < INPUT_COMMAND_LENGTH; j++) {
            if (args[j][0] == '$') {
                get_enviroment_variable_value(args[j], j);
        }
    }
}
void set_enviroment_variable_value(char *ip) {
    char *name = strtok(ip, "=");
    char *value = strtok(NULL, "=");
    if (setenv(name, value, 1) != 0) {
        perror("Failed to set environment variable");
    }
}


void get_enviroment_variable_value(char *ip, int index) {
    // Skip the first character ($) in the variable name
    char *value = getenv(ip + 1);
    if (value == NULL) {
        printf("Variable %s is not set", ip + 1);
    } 
    else {
        //printf("%s", value);
        args[index]= value;
    }
}

bool builtin_commands(void){
    bool ret = 1;
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            chdir("/root");
        }
        else {
            if (chdir(args[1]) != 0) {
                perror("osh");
            }
            ret = 0;
        }
    }
    else if (strcmp(args[0], "echo") == 0) {
        for (int j = 1; j < INPUT_COMMAND_LENGTH; j++) {
            printf("%s ", args[j]);}
        printf("\n");
    }
    else if (strcmp(args[0], "export") == 0) {
        if (args[1] != 0) {
                perror("osh");
                set_enviroment_variable_value(args[1]);
            }
    }
    else {
        ret = 0;
    }
    return ret;
}

void shell() {
    int should_run = 1;  /* flag to determine when to exit program */

    while (should_run) {
        printf("osh>");
        // get the input command

        read_input_command();
        tokinize_command();

        background = INPUT_COMMAND_LENGTH > 0 && strcmp(args[INPUT_COMMAND_LENGTH-1], "&") == 0;
        if (background) {
            args[INPUT_COMMAND_LENGTH-1] = NULL;  // remove & from args
        }

        // checking exit command
        if (exit_shell()){
            should_run = 0;
            continue;
        }

        // Handle built-in commands
        if (INPUT_COMMAND_LENGTH > 0 && builtin_commands()){
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            write_log("Fork failed.");
            return;
        
        } 
        else if (pid == 0) {
            if (execvp(args[0], args) < 0) {
                write_log("Exec failed.");
                exit(1);
            }
        }
        else {
            //waitpid(pid, NULL, 0);
            if (!background) {
                waitpid(pid, NULL, 0);
            }
        }
    }
}