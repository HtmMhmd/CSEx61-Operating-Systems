#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 128
#define MAX_NUM_ARGS 10

int main() {
    char cmd[MAX_CMD_LEN];
    char *args[MAX_NUM_ARGS];
    char *token;
    int status;
    pid_t pid;

    while (1) {
        printf("YOUR_COMMAND: ");
        fgets(cmd, MAX_CMD_LEN, stdin);

        // Remove trailing newline character
        cmd[strcspn(cmd, "\n")] = 0;

        // Exit the shell on 'exit' command
        if (strcmp(cmd, "exit") == 0) {
            break;
        }

        // Tokenize the command string into arguments
        int i = 0;
        token = strtok(cmd, " ");
        while (token != NULL) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;  // Last element should be NULL for execvp

        // Fork a child process
        pid = fork();
        if (pid < 0) {  // Error occurred
            fprintf(stderr, "Fork Failed");
            return 1;
        } else if (pid == 0) {  // Child process
            execvp(args[0], args);

            // If execvp returns, it must have failed
            printf("execvp failed for command %s\n", args[0]);
            exit(1);
        } else {  // Parent process
            // Parent will wait for the child to complete
            while (wait(&status) != pid)
                ;
        }
    }

    return 0;
}
