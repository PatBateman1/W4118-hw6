#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void die(char *msg)
{
	printf("err: %s\n", msg);
	exit(0);
}

int main(int argc, char const *argv[])
{
	cpu_set_t *mask;
	pid_t pid;
	int i;

	mask = CPU_ALLOC(1);
	CPU_ZERO(mask);

	for (i = 0; i < 20; i++) {
		pid = fork();
		if (pid < 0) {
			die("fork() failed!");
		} else if (pid > 0) {
			continue;
		} else {
			if (i < 5) {
				CPU_ZERO(mask);
				CPU_SET(0, mask);
				if (sched_setaffinity(0, sizeof(*mask), mask) == -1)
					die("sched_setaffinity() failed");
			} else if (i < 10) {
				CPU_ZERO(mask);
				CPU_SET(1, mask);
				if (sched_setaffinity(0, sizeof(*mask), mask) == -1)
					die("sched_setaffinity() failed");
			} else if (i < 15) {
				CPU_ZERO(mask);
				CPU_SET(2, mask);
				if (sched_setaffinity(0, sizeof(*mask), mask) == -1)
					die("sched_setaffinity() failed");
			} else {
				CPU_ZERO(mask);
				CPU_SET(3, mask);
				if (sched_setaffinity(0, sizeof(*mask), mask) == -1)
					die("sched_setaffinity() failed");
			}
			break;
		}

	}
	while (1);

	return 0;
}
