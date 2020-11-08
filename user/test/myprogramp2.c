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
    struct sched_param param;
    cpu_set_t *mask;
    pid_t pid;
    int i;

    mask = CPU_ALLOC(1);
    CPU_ZERO(mask);
    CPU_SET(2, mask); 

    for (i = 0; i < 11; i++) {
        pid = fork();
        if (pid < 0) {
            die("fork() failed!");
        } else if (pid > 0) {
            continue;
        } else {
            if (sched_setaffinity(0, sizeof(*mask), mask) == -1)
                die("sched_setaffinity() failed");
            if (i < 5)
                nice(10);
            else if (i < 10)
                nice(14);
            else {
                param.sched_priority = 99;
                sched_setscheduler(0, SCHED_FIFO, &param);
            }
            break;
        }

    }
    if (pid > 0)
        sleep(100);
    while (1);

    return 0;
}
