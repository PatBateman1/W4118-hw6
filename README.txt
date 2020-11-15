This file should contain:

-	Your name & UNI (or those of all group members for group assignments)
-	Homework assignment number
-	Description for each part

The description should indicate whether your solution for the part is working
or not. You may also want to include anything else you would like to
communicate to the grader, such as extra functionality you implemented or how
you tried to fix your non-working code.

Zixiao Zhu (zz2700)
Zhaoxuan Jiang (zj2267)

part6:
	Our solution works, the ps command doesn't show SCH 7 which is freezer scheduler.

part7:
	Our solution works.

	./set-freezer 954
	[954] sched policy changed: 0 --> 7
	./set-freezer 1030
	[1030] sched policy changed: 0 --> 7
	./set-freezer 1064
	[1064] sched policy changed: 0 --> 7

	ps results of the three vim process before we use set-freezer:
	0 TS    2  0.0  0   886 bateman               |   \_ bash
	0 TS    0  0.0  0   954 bateman               |   |   \_ vim Makefile
	0 TS    0  0.0  0   976 bateman               |   \_ bash
	0 TS    0  0.0  0  1030 bateman               |   |   \_ vim Makefile
	0 TS    0  0.0  0  1038 bateman               |   \_ bash
	0 TS    3  0.0  0  1064 bateman               |       \_ vim Makefile

	ps results of the three vim process after we use set-freezer:
	0 TS    2  0.0  0   886 bateman               |   \_ bash
	7 #7    0 60.7 60   954 bateman               |   |   \_ vim Makefile
	0 TS    0  0.0  0   976 bateman               |   \_ bash
	7 #7    1  0.0  0  1030 bateman               |   |   \_ vim Makefile
	0 TS    0  0.0  0  1038 bateman               |   \_ bash
	7 #7    1  0.0  0  1064 bateman               |       \_ vim Makefile

part8:
	our solution works. we changed all SCHED_NORMAL to SCHED_FREEZER in core.c and init_task.c.
	we wrote a test program called myprogram.c in user/test/set-freezer. this program created
	20 child processes cross 4 cpus. This is the ps command output:

	SCH POL PSR %CPU  C   PID USER     CMD
	7 #7    0  0.5  0   726 root      \_ sshd: bateman [priv]
	7 #7    0 88.5 88   744 bateman   |   \_ sshd: bateman@pts/0
	7 #7    0  0.6  0   745 bateman   |       \_ -bash
	7 #7    0  377 99  1923 bateman   |           \_ top
	7 #7    1  214 99  1654 root      \_ sshd: bateman [priv]
	7 #7    0  304 99  1660 bateman   |   \_ sshd: bateman@notty
	7 #7    1  0.0  0  1661 bateman   |       \_ -bash
	7 #7    1  214 99  1664 bateman   |           \_ bash
	7 #7    0  0.0  0  1704 bateman   |               \_ sh /home/bateman/.vscode-server/bin/fcac248b077b55bae4ba5bab613fd6e9156c2f0c/server.
	7 #7    0 2651 99  1712 bateman   |               |   \_ /home/bateman/.vscode-server/bin/fcac248b077b55bae4ba5bab613fd6e9156c2f0c/node /
	7 #7    0 4111 99  1750 bateman   |               |       \_ /home/bateman/.vscode-server/bin/fcac248b077b55bae4ba5bab613fd6e9156c2f0c/no
	7 #7    0 4324 99  1786 bateman   |               |       |   \_ /home/bateman/.vscode-server/extensions/ms-vscode.cpptools-1.1.1/bin/cpp
	7 #7    0 1155 99  1852 bateman   |               |       |       \_ /home/bateman/.vscode-server/extensions/ms-vscode.cpptools-1.1.1/bin
	7 #7    3 1871 99  1908 bateman   |               |       |       \_ /home/bateman/.vscode-server/extensions/ms-vscode.cpptools-1.1.1/bin
	7 #7    0 5802 99  2006 bateman   |               |       |       \_ /home/bateman/.vscode-server/extensions/ms-vscode.cpptools-1.1.1/bin
	7 #7    1 2193 99  2564 bateman   |               |       |       \_ /home/bateman/.vscode-server/extensions/ms-vscode.cpptools-1.1.1/bin
	7 #7    0 1980 99  1761 bateman   |               |       \_ /home/bateman/.vscode-server/bin/fcac248b077b55bae4ba5bab613fd6e9156c2f0c/no
	7 #7    0  0.0  0  2732 bateman   |               \_ sleep 180
	7 #7    1  310 99  1926 root      \_ sshd: bateman [priv]
	7 #7    2  343 99  1932 bateman   |   \_ sshd: bateman@pts/1
	7 #7    0  398 99  1933 bateman   |       \_ -bash
	7 #7    0 11154 99 2784 bateman   |           \_ ./myprogram
	7 #7    0 11152 99 2785 bateman   |               \_ ./myprogram
	7 #7    0 11152 99 2786 bateman   |               \_ ./myprogram
	7 #7    0 11153 99 2787 bateman   |               \_ ./myprogram
	7 #7    0 11153 99 2788 bateman   |               \_ ./myprogram
	7 #7    0 11154 99 2789 bateman   |               \_ ./myprogram
	7 #7    1 11154 99 2790 bateman   |               \_ ./myprogram
	7 #7    1 11154 99 2791 bateman   |               \_ ./myprogram
	7 #7    1 11153 99 2792 bateman   |               \_ ./myprogram
	7 #7    1 11153 99 2793 bateman   |               \_ ./myprogram
	7 #7    1 11154 99 2794 bateman   |               \_ ./myprogram
	7 #7    2 11154 99 2795 bateman   |               \_ ./myprogram
	7 #7    2 11153 99 2796 bateman   |               \_ ./myprogram
	7 #7    2 11154 99 2797 bateman   |               \_ ./myprogram
	7 #7    2 11154 99 2798 bateman   |               \_ ./myprogram
	7 #7    2 11153 99 2799 bateman   |               \_ ./myprogram
	7 #7    3 11153 99 2800 bateman   |               \_ ./myprogram
	7 #7    3 11154 99 2801 bateman   |               \_ ./myprogram
	7 #7    3 11153 99 2802 bateman   |               \_ ./myprogram
	7 #7    3 11154 99 2803 bateman   |               \_ ./myprogram
	7 #7    3 11154 99 2804 bateman   |               \_ ./myprogram