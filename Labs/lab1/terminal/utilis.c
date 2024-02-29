#include "utilis.h"

void write_log(char characters[])
{
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

void on_child_exit()
{
    /*
    wait for the termination of any child processes in a non-blocking manner.
    */
    while (waitpid(-1, NULL, WNOHANG) > 0);
    // Write to log file
    write_log("Child terminated");
}

void setup_environment()
{
    /* 
    Change to current working directory
    */
    chdir(getenv("PWD"));
}

bool exit_shell(void)
{
    /* 
    exit if input command is exit
    */
    return (strcmp(args[0], "exit") == 0);
}

void read_input_command(void)
{
    /*
    get the input command
    */
    //int *input_modifier[] = input;
    fgets((input), MAX_LINE, stdin);
    (input)[strcspn((input), "\n")] = 0;  // remove trailing newline
}   

void split_quoted_string(void)
{   
    /* 
    replaces the quoted part of the input with the unquoted part
    */    
    char output[MAX_LINE];
    int j = 0;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != '\"') {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';  // Null-terminate the string
    strcpy(input, output);
}

void handle_enviroment_variable(void)
{   
    /*
    checks if enviroment variable call argument ($VAR) and replaces it with its value
    */
    for (int arg_number = 1; arg_number < INPUT_COMMAND_LENGTH; arg_number++) 
    {
        if (args[arg_number][0] == '$') 
        {
            get_enviroment_variable_value(args[arg_number], arg_number);
        }
    }
}

void set_enviroment_variable_value(char *ip)
{   
    char *name  = strtok(ip, "=");
    char *value = strtok(NULL, "=");
    if (setenv(name, value, 1) != 0) 
    {
        perror("Failed to set environment variable");
    }
}

void get_enviroment_variable_value(char *ip, int index) 
{
    // Skip the first character ($) in the variable name
    char *value = getenv(ip + 1);
    if (value == NULL) 
    {
        printf("Variable %s is not set", ip + 1);
    }
    else 
    {
        args[index]= value;
    }
}


void tokinize_command(void)
{
    /*
    split input command into argumants (tokens separated by spaces) and stores in args.
    return : INPUT_COMMAND_LENGTH
    */
    //printf("%s\n", input);
    split_quoted_string();
    //printf("%s\n", input);
    char *token = strtok(input, " ");
    INPUT_COMMAND_LENGTH = 0;
    while (token != NULL)
    {
        args[INPUT_COMMAND_LENGTH ++] = token;
        token = strtok(NULL, " ");
    }
    args[INPUT_COMMAND_LENGTH] = NULL;

    handle_enviroment_variable();
}

void echo_command(void)
{
    /*
    handling (echo) command
    */
    for (int arg_number = 1; arg_number < INPUT_COMMAND_LENGTH; arg_number++) 
    {
        printf("%s ", args[arg_number]);
    }
    printf("\n");
    command_type = BUILTIN_COMMAND;
}

void export_command(void)
{   
    /*
    handling (export) command
    */
    if(args[2] != 0)
    {
        command_type = NOT_BUILTIN_COMMAND;
    }
    else if ((args[1] != 0))
    {
        set_enviroment_variable_value(args[1]);
        command_type = BUILTIN_COMMAND;
    }
     
}

void cd_command(void)
{
    /*
    handling (cd) , (cd ~) commands which change directory to root path
    */
    if ((args[1] == NULL) || (strcmp(args[1], "~") == 0))
    {
        chdir("/root");
        command_type = BUILTIN_COMMAND;
    }
    else if (chdir(args[1]) != 0) 
    {
        command_type = NOT_BUILTIN_COMMAND;
    }  
}
builtin_command_t builtin_commands(void)
{

    if (strcmp(args[0], "cd") == 0) {

        cd_command();
    }
    else if (strcmp(args[0], "echo") == 0) 
    {
        echo_command();
    }
    else if (strcmp(args[0], "export") == 0) 
    {
        export_command();
    }
    else {
        command_type = NOT_BUILTIN_COMMAND;
    }
    return command_type;
}

void shell() {
    should_run = CONTINUE_RUNNING;
    while (should_run == CONTINUE_RUNNING) {
        printf("shell>");
        // get the input command

        read_input_command();
        tokinize_command();

        background = INPUT_COMMAND_LENGTH > 0 && strcmp(args[INPUT_COMMAND_LENGTH-1], "&") == 0;
        if (background) {
            args[INPUT_COMMAND_LENGTH-1] = NULL;  // remove & from args
        }

        // checking exit command
        if (exit_shell())
        {
            should_run = STOP_RUNNING;
            continue;
        }

        // Handle built-in commands
        if ((INPUT_COMMAND_LENGTH > 0) && (builtin_commands() == BUILTIN_COMMAND))
        {
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) 
        {
            write_log("Fork failed.");
            return;
        
        } 
        else if (pid == 0) 
        {
            if (execvp(args[0], args) < 0) 
            {   
                perror("Check the command");
                write_log("Exec failed.");
                exit(1);
            }
        }
        else {
            if (!background) 
            {
                waitpid(pid, NULL, 0);
            }
        }
    }
}