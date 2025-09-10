#include "types.h"
#include "user.h"

int main(int argc, char** argv) {
	int pid = getpid();
	printf(1, "Part one test. Current PID %d, current count %d\n", pid, firstpart());
	printf(1, "New count %d\n", firstpart());
	exit();
}
