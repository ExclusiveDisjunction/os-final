#include "types.h"
#include "user.h"

int main() {
    int pid1 = fork();
    if (pid1 == 0) {
        char *argv[] = { "hog", 0 };
        int ret = exec("hog", argv);
        printf(1, "hog returned code=%d", ret);   
        exit();
    }

    int pid2 = fork();
    if (pid2 == 0) {
        char *argv[] = { "sleeper", 0 };
        int ret = exec("sleeper", argv);
        printf(1, "sleeper returned code=%d", ret);  
        exit();
    }

    wait();
}
