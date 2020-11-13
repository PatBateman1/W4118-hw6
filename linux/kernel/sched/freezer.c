#include "sched.h"
#include <linux/list.h>
#include <trace/events/sched.h>

void init_freezer_rq(struct freezer_rq *fz_rq)
{

}

void __init init_sched_fz_class(void)
{
	unsigned int i;

	for_each_possible_cpu(i)
		zalloc_cpumask_var_node(&per_cpu(local_cpu_mask_dl, i),
					GFP_KERNEL, cpu_to_node(i));
}

static void enqueue_task_fz(struct rq *rq, struct task_struct *p, int flags)
{
	
}

static void dequeue_task_fz(struct rq *rq, struct task_struct *p, int flags)
{

}

static void yield_task_fz(struct rq *rq)
{

}

static void check_preempt_curr_fz(struct rq *rq, struct task_struct *p, int wake_flags)
{

}

static struct task_struct *pick_next_task_fz(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
	return NULL;
}

static void put_prev_task_fz(struct rq *rq, struct task_struct *prev)
{

}

static int select_task_rq_fz(struct task_struct *p, int prev_cpu, int sd_flag, int wake_flags)
{
	return 0;
}

static void migrate_task_rq_fz(struct task_struct *p, int new_cpu)
{

}

static void rq_online_fz(struct rq *rq)
{

}

static void rq_offline_fz(struct rq *rq)
{

}

static void task_dead_fz(struct task_struct *p)
{
	
}

static void set_curr_task_fz(struct rq *rq)
{
	
}

static void task_tick_fz(struct rq *rq, struct task_struct *curr, int queued)
{
	
}

static void task_fork_fz(struct task_struct *p)
{

}


static void prio_changed_fz(struct rq *rq, struct task_struct *p, int oldprio)
{

}

static void switched_from_fz(struct rq *rq, struct task_struct *p)
{
	
}

static void switched_to_fz(struct rq *rq, struct task_struct *p)
{

}

static unsigned int get_rr_interval_fz(struct rq *rq, struct task_struct *task)
{
	return 0;
}

static void update_curr_fz(struct rq *rq)
{
	
}


/*
 * Simple, special scheduling class for the per-CPU idle tasks:
 */
const struct sched_class freezer_sched_class = {
	.next				= &fair_sched_class,
	.enqueue_task		= enqueue_task_fz,
	.dequeue_task		= dequeue_task_fz,
	.yield_task			= yield_task_fz,

	.check_preempt_curr	= check_preempt_curr_fz,

	.pick_next_task		= pick_next_task_fz,
	.put_prev_task		= put_prev_task_fz,

#ifdef CONFIG_SMP
	.select_task_rq		= select_task_rq_fz,
	.migrate_task_rq	= migrate_task_rq_fz,

	.rq_online		= rq_online_fz,
	.rq_offline		= rq_offline_fz,

	.task_dead		= task_dead_fz,
	.set_cpus_allowed	= set_cpus_allowed_common,
#endif

	.set_curr_task		= set_curr_task_fz,
	.task_tick			= task_tick_fz,

	.task_fork			= task_fork_fz,

	.prio_changed		= prio_changed_fz,
	.switched_from		= switched_from_fz,
	.switched_to		= switched_to_fz,

	.get_rr_interval	= get_rr_interval_fz,

	.update_curr		= update_curr_fz,
};
