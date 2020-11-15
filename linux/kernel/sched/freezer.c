#include "sched.h"
#include <linux/list.h>
#include <trace/events/sched.h>
#include <linux/sched/freezer.h>
#include <linux/slab.h>
#include <linux/cpumask.h>

void init_freezer_rq(struct freezer_rq *fz_rq)
{
	INIT_LIST_HEAD(&fz_rq->run_list);
	fz_rq->nr_running = 0;
}

void __init init_sched_fz_class(void)
{

}

static void enqueue_task_fz(struct rq *rq, struct task_struct *p, int flags)
{
	struct sched_freezer_entity *fz_se = &p->fz;

	list_add_tail(&fz_se->run_list, &rq->fz.run_list);
	rq->fz.nr_running++;
}

static void dequeue_task_fz(struct rq *rq, struct task_struct *p, int flags)
{
	if (!rq->fz.nr_running)
		return;

	list_del(&p->fz.run_list);
	rq->fz.nr_running--;
}

static void yield_task_fz(struct rq *rq)
{	
	rq->curr->fz.time_slice = 0;
}

static void check_preempt_curr_fz(struct rq *rq, struct task_struct *p, int wake_flags)
{
	if (p->prio < rq->curr->prio) {
		resched_curr(rq);
		return;
	}
}

static struct task_struct *pick_next_task_fz(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
	struct freezer_rq *fz_rq = &rq->fz;
	struct sched_freezer_entity *next_entity;
	struct task_struct *next;

	if (!fz_rq->nr_running)
		return NULL;
	
	put_prev_task(rq, prev);
	next_entity = list_entry(fz_rq->run_list.next, struct sched_freezer_entity, run_list);
	next = list_entry(next_entity, struct task_struct, fz);

	return next;
}

static void put_prev_task_fz(struct rq *rq, struct task_struct *prev)
{
	struct freezer_rq *fz_rq = &rq->fz;

	if(!prev->fz.on_rq)
		return;

	if (fz_rq->run_list.next == &prev->fz.run_list)
		return;
	
	list_del(&prev->fz.run_list);
	list_add_tail(&prev->fz.run_list, &fz_rq->run_list);
}

#ifdef CONFIG_SMP
static int select_task_rq_fz(struct task_struct *p, int prev_cpu, int sd_flag, int wake_flags)
{
	int target_cpu, cpu;
	unsigned int num_tasks;
	struct rq *rq;
	struct cpumask cpus = (struct cpumask) p->cpus_allowed;

	target_cpu = 0;
	num_tasks = 4294967295;
	if (p->nr_cpus_allowed == 1)
		return target_cpu;
	
	for_each_cpu(cpu, &cpus) {
		rq = cpu_rq(cpu);
		if (rq->fz.nr_running < num_tasks) {
			num_tasks = rq->fz.nr_running;
			target_cpu = cpu;
		}
	}

	return target_cpu;
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
#endif

static void set_curr_task_fz(struct rq *rq)
{
	rq->curr->fz.time_slice = FREEZER_TIMESLICE;
}

static void update_curr_fz(struct rq *rq);

static void task_tick_fz(struct rq *rq, struct task_struct *curr, int queued)
{
	curr->fz.time_slice--;
	update_curr_fz(rq);

	if (curr->fz.time_slice)
		return;
	
	curr->fz.time_slice = FREEZER_TIMESLICE;

	if (rq->fz.nr_running == 1)
		return;
	
	list_del(&curr->fz.run_list);
	list_add_tail(&curr->fz.run_list, &rq->fz.run_list);

	resched_curr(rq);
}

static void task_fork_fz(struct task_struct *p)
{

}


static void prio_changed_fz(struct rq *rq, struct task_struct *p, int oldprio)
{

}

static void switched_from_fz(struct rq *rq, struct task_struct *p)
{
	list_del(&p->fz.run_list);
	resched_curr(rq);
}

static void switched_to_fz(struct rq *rq, struct task_struct *p)
{
	if (p->on_rq && rq->curr != p) {
		list_add_tail(&p->fz.run_list, &rq->fz.run_list);
		resched_curr(rq);
	}
}

static unsigned int get_rr_interval_fz(struct rq *rq, struct task_struct *task)
{
	return 0;
}

static void update_curr_fz(struct rq *rq)
{
	struct task_struct *curr = rq->curr;
	u64 delta_exec;
	u64 now;

	if (curr->sched_class != &freezer_sched_class)
		return;

	now = rq_clock_task(rq);
	delta_exec = now - curr->se.exec_start;
	if (unlikely((s64)delta_exec <= 0))
		return;

	schedstat_set(curr->se.statistics.exec_max,
		      max(curr->se.statistics.exec_max, delta_exec));

	curr->se.sum_exec_runtime += delta_exec;
	account_group_exec_runtime(curr, delta_exec);

	curr->se.exec_start = now;
	cgroup_account_cputime(curr, delta_exec);
}


/*
 * freezer sched class
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

	.rq_online			= rq_online_fz,
	.rq_offline			= rq_offline_fz,

	.task_dead			= task_dead_fz,
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
