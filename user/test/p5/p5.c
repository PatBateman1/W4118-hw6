#include <linux/init.h>
#include <linux/module.h>
#include <asm/param.h>
#include <linux/jiffies.h>
#include <linux/printk.h>

int simple_init(void)
{
	unsigned long time_stamp;

	/* for q1 */
	printk("HZ is %d\n", HZ);

	/* for q4 */
	time_stamp = jiffies;
	printk("jiffies is: %ld\n", time_stamp);
	return 0;
}

void simple_exit(void)
{
	printk("exit.\n");
}

module_init(simple_init);
module_exit(simple_exit);
