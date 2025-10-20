# include "types.h"
# include "stat.h"
# include "user.h"

int main(int argc, char *argv[]){
	int ops = 60;
	if(argc>1){
		ops = atoi(argv[1]);
	}
	int i;
	for (i = 0; i < ops; i++){
		printf(1, "io %d\n", i);
		sleep(5);
	}
	printf(1, "iobound done, pid=%d\n", getpid());
	exit();
}