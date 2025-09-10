#include "types.h"
#include "user.h"

int main(int argc, char** argv) {
	printf(1, "Part one test. Current PID %d, current count %d\n", getpid(), firstpart());
	printf(1, "New count %d\n", firstpart());
	exit();
}
