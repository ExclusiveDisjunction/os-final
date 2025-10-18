#include "types.h"
#include "user.h"

int main() {
    int pid1 = fork();
    if (pid1 == 0) {
        exec("print_test test1", 0);
    }

    // int pid2 = fork();
    // if (pid2 == 0) {
        // exec("print_test test2", 0);
    // }

    wait();
}
