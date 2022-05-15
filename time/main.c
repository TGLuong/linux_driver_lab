#include <linux/module.h>
#include <linux/timekeeping.h>
#include <linux/jiffies.h>


static int md_init(void) {
    struct timespec64 tv;
    struct timespec tvj;
    u64 time;
    unsigned long start_time;
    

    start_time = jiffies;
    jiffies_to_timespec(start_time, &tvj);


    ktime_get_ts64(&tv);
    time = ktime_get_ns();


    printk("wall time nsec: %ld\n", tv.tv_nsec);
    printk("wall time sec: %lld\n", tv.tv_sec);
    printk("wall time nano: %lld\n", time);
    printk("systemup time: %ld", tvj.tv_sec);
    return 0;
}

static void md_exit(void) {
    printk("exit module\n");
}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
