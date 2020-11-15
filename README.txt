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