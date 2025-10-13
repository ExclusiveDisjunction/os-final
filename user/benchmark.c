# include "types.h"
# include "stat.h"
# include "user.h"
# include "pstat.h"

# define NCHILD 5

static void spawn(char *prog, char *arg){
	char *argv[3]={prog, arg, 0};
	if(fork() == 0){
		exec(prog, argv);
		printf(1, "exec %s failed\n", prog);
		exit();
	}
}
int main(int argc, char *argv[]){
	struct pstat ps;
	int i;
	int start = uptime();
	spawn("cpubound", "600000");
	spawn("cpubound", "600000");
	spawn("iobound", "40");
	spawn("iobound", "40");
	spawn("mixed", "30");
	
	for(i = 0; i < NCHILD; i++){
		wait();
	}
	
	int end = uptime();
	int makespan = end - start;
	
	if(getpinfo(&ps) < 0){
		printf(1, "getinfo failed\n");
		exit();
	}
	
	int total_resp = 0;
	int resp_cnt = 0;
	int total_turn = 0;
	int turn_cnt = 0;
	int busy_ticks = 0;
	
	printf(1, "\nFINAL STATS (pid name ticks wait start first end)\n");
	
	for(i = 0; i < NPROC; i++){
		if(ps.inuse[i] && ps.pid[i] > 2){
			
			int turnaround;
			if(ps.end_tick[i] > 0){
				turnaround = ps.end_tick[i] - ps.start_tick[i];
			}
			else{
				turnaround = end - ps.start_tick[i];
			}
			
			int response;
			if(ps.first_run[i] >= 0){
				response = ps.first_run[i] - ps.start_tick[i];
			}
			else{
				response = end - ps.start_tick[i];
			}
			
			printf(1, "%d %-12s %d %d %d %d %d\n", ps.pid[i], ps.ticks[i], ps.wait_ticks[i],
					ps.start_tick[i], ps.first_run[i], ps.end_tick[i]);
			
			if(ps.end_tick[i] > 0){
				total_turn += turnaround;
				turn_cnt++;
			}
			
			if(ps.first_run[i] >= 0){
				total_resp += response;
				resp_cnt++;
			}
			
			busy_ticks += ps.ticks[i];
		}
	}
	
	int avg_response;
	if(resp_cnt){
		avg_response = total_resp/resp_cnt;
	}
	else{
		avg_response = -1;
	}
	
	int avg_turn;
	if(turn_cnt){
		avg_turn = total_turn/turn_cnt;
	}
	else{
		avg_turn = -1;
	}
	
	int util_permille;
	if(makespan){
		util_permille = (busy_ticks*1000)/makespan;
	}
	else{
		util_permille = 0;
	}
	
	printf(1, "\nMAKESPAN (ticks): %d\n", makespan);
	printf(1, "AVG RESPONSE (ticks): %d\n", avg_response);
	printf(1, "AVG TURNAROUND (ticks): %d\n", avg_turn);
	printf(1, "CPU UTILIZATION: %d.%d%%\n", util_permille/10, util_permille%10);
	exit();
}