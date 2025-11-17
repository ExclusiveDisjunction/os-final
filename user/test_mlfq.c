#include "types.h"
#include "user.h"

int main() {
    int pid1 = fork();
    if (pid1 == 0) {
        char *argv[] = { "test_print", "test1", 0 };
        int ret = exec("test_print", argv);
        printf(1, "test_print1 returned code=%d", ret);   
    }

    int pid2 = fork();
    if (pid2 == 0) {
        char *argv[] = { "test_print", "test2", 0 };
        int ret = exec("test_print", argv);
        printf(1, "test_print2 returned code=%d", ret);   
    }

    wait();
}
