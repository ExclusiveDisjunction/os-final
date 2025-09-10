#include "types.h"
#include "user.h"

// partone-test.c - Tests the firstpart system call by calling pid, and then outputing the firstpart output.

int main(int argc, char** argv) {
	int pid = getpid();
	printf(1, "Part one test. Current PID %d, current count %d\n", pid, firstpart());
	printf(1, "New count %d\n", firstpart());
	exit();
}
