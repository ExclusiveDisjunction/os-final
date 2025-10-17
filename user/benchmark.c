# include "types.h"
# include "stat.h"
# include "user.h"
# include "pstat.h"

# define NCHILD 5

static void spawn(char *prog, char *arg){
	char *argv[3]={prog, arg, 0};
	int fork_value = fork();
	if (fork_value < 0) {
		printf(1, "Unable to fork");
		exit();
	}

	else if (fork_value == 0){
		exec(prog, argv);
		printf(1, "exec %s failed\n", prog);
		exit();
	}
}
int main(int argc, char *argv[]){
	int i;
	int start = uptime();
	pinfostart();
	
	spawn("cpubound", "600000");
	spawn("cpubound", "600000");
	spawn("iobound", "40");
	spawn("iobound", "40");
	spawn("mixed", "30");
	
	for(i = 0; i < NCHILD; i++){
		wait();
	}

	struct pstat info;	
	int end = uptime();
	int makespan = end - start;
	
	if(getpinfo(&info) < 0){
		printf(1, "getinfo failed\n");
		exit();
	}

	int total_resp = 0;
	int resp_cnt = 0;
	int total_turn = 0;
	int turn_cnt = 0;
	int busy_ticks = 0;
	
	char name_pretty[16];
	name_pretty[15] = 0;

	printf(1, "\nFINAL STATS\n");
	printf(1, "PID\tName           Ticks\tWait\tStart\tFirst\tEnd\t\n");	
	for(i = 0; i < NPROC && i < info.count; i++){
		if(info.inuse[i] && info.pid[i] > 2){
			int turnaround;
			if(info.end_tick[i] > 0){
				turnaround = info.end_tick[i] - info.start_tick[i];
			}
			else{
				turnaround = end - info.start_tick[i];
			}
			
			int response;
			if(info.first_run[i] >= 0){
				response = info.first_run[i] - info.start_tick[i];
			}
			else{
				response = end - info.start_tick[i];
			}
		
			// Perfectionist stuff... Creating a buffer that stores the name to a specific width..
			memset(name_pretty, ' ', sizeof(char) * 15);
			int c_i;
			char* name = info.name[i];
			for(c_i = 0; name[c_i]; c_i++) 
				name_pretty[c_i] = name[c_i]; 

			printf(1, "%d\t%s\t%d\t%d\t%d\t%d\t%d\n", info.pid[i], name_pretty, info.ticks[i], info.wait_ticks[i], info.start_tick[i], info.first_run[i], info.end_tick[i]);
			
			if(info.end_tick[i] > 0){
				total_turn += turnaround;
				turn_cnt++;
			}
			
			if(info.first_run[i] >= 0){
				total_resp += response;
				resp_cnt++;
			}
			
			busy_ticks += info.ticks[i];
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
