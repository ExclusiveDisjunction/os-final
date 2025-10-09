#ifndef _PSTAT_H_
#define _PSTAT_H_
#include "param.h"

struct pstat {
	int inuse[NPROC];
	int pid[NPROC];
	int ticks[NPROC];
	int wait_ticks[NPROC];
	int start_tick[NPROC];
	int first_run[NPROC];
	int end_tick[NPROC];
	char name[NPROC][16];
};

#endif
