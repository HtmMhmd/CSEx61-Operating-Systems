#include  "utilis.h"

int main() {

    while (1) {
        printf("YOUR_COMMAND: ");
        /* Reading command from user*/
        /* Storing the command in "cmd" variable*/
        GET_INPUT_COMMAND();
        /* Remove newline character \n in the end */
        /* Replacing new line character with NULL as a list ending*/

        cmd[strcspn(cmd, "\n")] = NULL;
        /* Printing written command*/
        //printf("YOUR COMMAND IS: %s", cmd);

        /* Exit the shell on exit command*/
        if (EXIT_COMMAND()) break;

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
