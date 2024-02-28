#include "utilis.h"

int main(void) {
    // Register child signal
    signal(SIGCHLD, on_child_exit);

    // Setup environment
    setup_environment();

    // Start shell
    shell();

    return 0;
}
