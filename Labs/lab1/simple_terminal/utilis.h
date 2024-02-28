#include "defines.h"

#define GET_INPUT_COMMAND()       fgets(cmd, MAX_CMD_LENGTH, stdin)
#define EXIT_COMMAND()            (strcmp(cmd, "exit") == 0) 