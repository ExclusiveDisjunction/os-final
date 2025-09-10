#include "types.h"
#include "user.h"

int main(int argc, char** argv) {
    int pid_count = firstpart();
    int completed_syscalls = secondpart();
    int success_syscalls = thirdpart();

    printf(1, "Total number of pid calls: %d\nTotal number of sys calls: %d\nTotal number of successful syscalls: %d\n", pid_count, completed_syscalls, success_syscalls);
    exit();
}