// #define _GNU_SOURCE
#include <sched.h>
#include <linux/sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	int prev_sched;
	const struct sched_param param = { .sched_priority = 0 };

	if (argc < 2) {
		printf("need a pid.\n");
		return 0;
	}
		
	pid = strtol(argv[1], NULL, 10);

	prev_sched = sched_getscheduler(pid);

	if (sched_setscheduler(pid, SCHED_FREEZER, &param) == -1) {
		printf("sched_setscheduler() failed.\n");
		printf("ERROR: %d\n", (errno));
		return 0;
	}

	printf("[%d] sched policy changed: %d --> %d\n", pid, prev_sched, 7);
	return 0;
}