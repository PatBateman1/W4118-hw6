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
    cpu_set_t mask;
    pid_t pid;
    int i;

    CPU_ZERO(&mask);
    CPU_SET(0, &mask); 

    for (i = 0; i < 10; i++) {
        pid = fork();
        if (pid < 0) {
            die("fork() failed!");
        } else if (pid > 0) {
            continue;
        } else {
            if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
                die("sched_setaffinity() failed");
            if (i < 5)
                nice(10);
            else
                nice(14);
            
            break;
        }

    }
    while (1);

    return 0;
}
