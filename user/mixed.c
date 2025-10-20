# include "types.h"
# include "stat.h"
# include "user.h"

int main(int argc, char *argv[]){
	int cycles = 40;
	if(argc>1){
		cycles = atoi(argv[1]);
	}
	int i,j,x=0;
	for(i = 0; i < cycles; i++){
		for(j = 0; j < 12; j++){
			x += j;
			if( (i % 4) == 0){
				sleep(3);
			}
		}
	}
	printf(1, "mixed done, pid=%d\n", getpid());
	exit();
}
