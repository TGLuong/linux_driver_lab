#include <linux/module.h>
#include <linux/timekeeping.h>



static int md_init(void) {
    struct timespec64 tv;
    ktime_get_ts64(&tv);
    printk("wall time: %lld\n", tv.tv_sec);
    return 0;
}

static void md_exit(void) {
    printk("exit module\n");
}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
