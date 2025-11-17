# include "types.h"
# include "stat.h"
# include "user.h"

int main(int argc, char *argv[]){

	int iters=800000; 
	if(argc>1){
		iters=atoi(argv[1]);
	}
	int i, x = 0; 
	for(i = 0; i < iters; i++){
		x += i;
		if((i & 1023) == 0){
			x >>= 1;
		}
	}
	printf(1, "cpubound done, pid=%d\n", getpid());
	exit();
}