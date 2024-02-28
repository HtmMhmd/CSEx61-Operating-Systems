#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_LINE 80 /* The maximum length command */

void on_child_exit() {
    // Reap child zombie
    while (waitpid(-1, NULL, WNOHANG) > 0);

    // Write to log file
    FILE *log_file = fopen("log.txt", "a");
    fprintf(log_file, "Child terminated\n");
    fclose(log_file);
}

void setup_environment() {
    // Change to current working directory
    chdir(getenv("PWD"));
}

void shell() {
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    char input[MAX_LINE];
    int background;

    while (should_run) {
        printf("osh>");
        fflush(stdout);

        fgets(input, MAX_LINE, stdin);
        input[strcspn(input, "\n")] = 0;  // remove trailing newline

        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        background = i > 0 && strcmp(args[i-1], "&") == 0;
        if (background) {
            args[i-1] = NULL;  // remove & from args
        }

        if (i > 0 && strcmp(args[0], "exit") == 0) {
            should_run = 0;
            continue;
        }

        // Handle built-in commands
        if (i > 0 && strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "Expected argument to \"cd\"\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("osh");
                }
            }
            continue;
        }

        if (i > 0 && strcmp(args[0], "echo") == 0) {
            for (int j = 1; j < i; j++) {
                printf("%s ", args[j]);
            }
            printf("\n");
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork failed.\n");
            return;
        } else if (pid == 0) {
            if (execvp(args[0], args) < 0) {
                fprintf(stderr, "Exec failed.\n");
                exit(1);
            }
        } else {
            if (!background) {
                waitpid(pid, NULL, 0);
            }
        }
    }
}

int main(void) {
    // Register child signal
    signal(SIGCHLD, on_child_exit);

    // Setup environment
    setup_environment();

    // Start shell
    shell();

    return 0;
}