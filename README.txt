This file should contain:

-	Your name & UNI (or those of all group members for group assignments)
-	Homework assignment number
-	Description for each part

The description should indicate whether your solution for the part is working
or not. You may also want to include anything else you would like to
communicate to the grader, such as extra functionality you implemented or how
you tried to fix your non-working code.

part1:
    task1:
        In this task, we wrote a c program called myprogram.c (in user/test/),
        in this program, we created a process and forked 10 child processes, bond
        the 10 processes to cpu2, then we set the first 5 child processes' nice 
        value to 10 and last 5 processes' nice value to 14. 
        
        top - 09:16:17 up 13 min,  3 users,  load average: 0.82, 0.22, 0.12
        Tasks: 179 total,  11 running, 168 sleeping,   0 stopped,   0 zombie
        %Cpu0  :   0.3/0.0     0[                                                   ]
        %Cpu1  :   0.0/0.0     0[                                                   ]
        %Cpu2  : 100.0/0.0   100[|||||||||||||||||||||||||||||||||||||||||||||||||||]
        %Cpu3  :   0.0/0.0     0[                                                   ]
        MiB Mem :   7973.6 total,   5296.2 free,    919.1 used,   1758.3 buff/cache
        MiB Swap:   8190.0 total,   8190.0 free,      0.0 used.   6744.3 avail Mem 

        PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                                                                      
        1472 bateman   30  10    2276     80      0 R  14.3   0.0   0:01.27 myprogram                                                                    
        1476 bateman   30  10    2276     80      0 R  14.3   0.0   0:01.27 myprogram                                                                    
        1473 bateman   30  10    2276     80      0 R  14.0   0.0   0:01.26 myprogram                                                                    
        1474 bateman   30  10    2276     80      0 R  14.0   0.0   0:01.26 myprogram                                                                    
        1475 bateman   30  10    2276     80      0 R  14.0   0.0   0:01.26 myprogram                                                                    
        1477 bateman   34  14    2276     80      0 R   6.0   0.0   0:00.52 myprogram                                                                    
        1480 bateman   34  14    2276     80      0 R   6.0   0.0   0:00.52 myprogram                                                                    
        1478 bateman   34  14    2276     80      0 R   5.7   0.0   0:00.51 myprogram                                                                    
        1479 bateman   34  14    2276     80      0 R   5.7   0.0   0:00.51 myprogram                                                                    
        1481 bateman   34  14    2276     80      0 R   5.7   0.0   0:00.51 myprogram                                                                    
            1 root      20   0  169468  10080   7804 S   0.0   0.1   0:00.87 systemd                                                                      
            2 root      20   0       0      0      0 S   0.0   0.0   0:00.00 kthreadd
    
    task2:
        In this task, we modified the task1's program into myprogramp2.c: we add another
        child process, i.e. 11st child process, the first 10 child processes remained 
        the same. In the last child process, we changed the scheduler policy to 
        SCHED_FIFO and set the sched_priority to max: 99. Finally, we ran the myprogramp2 with
        sudo: sudo ./myprogramp2.

        top - 09:27:36 up 24 min,  3 users,  load average: 10.71, 9.76, 5.70
        Tasks: 180 total,  14 running, 166 sleeping,   0 stopped,   0 zombie
        %Cpu0  :   0.0/0.0     0[                                                        ]
        %Cpu1  :   0.3/0.0     0[                                                        ]
        %Cpu2  : 100.0/0.0   100[||||||||||||||||||||||||||||||||||||||||||||||||||||||||]
        %Cpu3  :   0.0/0.0     0[                                                        ]
        MiB Mem :   7973.6 total,   5283.2 free,    930.3 used,   1760.0 buff/cache
        MiB Swap:   8190.0 total,   8190.0 free,      0.0 used.   6732.7 avail Mem 

        PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                                                                      
        1577 root      rt   0    2276     76      0 R  99.7   0.0   0:10.33 ./myprogramp2                                                                
            1 root      20   0  169468  10080   7804 S   0.0   0.1   0:00.87 /sbin/init                                                                   
            2 root      20   0       0      0      0 S   0.0   0.0   0:00.00 [kthreadd]                                                                   
            3 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 [rcu_gp]     


        and the part result of the ps auxf command:

        bateman    942  0.0  0.0   9012  5864 pts/2    Ss   09:03   0:00  |       \_ -bash
        root      1565  0.0  0.0  10244  3900 pts/2    S+   09:27   0:00  |           \_ sudo ./myprogramp2
        root      1566  0.0  0.0   2276   740 pts/2    S+   09:27   0:00  |               \_ ./myprogramp2
        root      1567  0.0  0.0   2276    76 pts/2    RN+  09:27   0:00  |                   \_ ./myprogramp2
        root      1568  0.0  0.0   2276    76 pts/2    RN+  09:27   0:00  |                   \_ ./myprogramp2
        root      1569  0.0  0.0   2276    76 pts/2    RN+  09:27   0:00  |                   \_ ./myprogramp2
        root      1570  0.0  0.0   2276    76 pts/2    RN+  09:27   0:00  |                   \_ ./myprogramp2
        root      1571  0.0  0.0   2276    76 pts/2    RN+  09:27   0:00  |                   \_ ./myprogramp2
        root      1572  0.0  0.0   2276    76 pts/2    RN+  09:27   0:00  |                   \_ ./myprogramp2
        root      1573  0.0  0.0   2276    76 pts/2    RN+  09:27   0:00  |                   \_ ./myprogramp2
        root      1574  0.0  0.0   2276    76 pts/2    RN+  09:27   0:00  |                   \_ ./myprogramp2
        root      1575  0.0  0.0   2276    76 pts/2    RN+  09:27   0:00  |                   \_ ./myprogramp2
        root      1576  0.0  0.0   2276    76 pts/2    RN+  09:27   0:00  |                   \_ ./myprogramp2
        root      1577 99.6  0.0   2276    76 pts/2    R+   09:27   1:18  |                   \_ ./myprogramp2