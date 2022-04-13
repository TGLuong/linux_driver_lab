#include <linux/ctype.h>
#include <linux/module.h>

int dec = 0;
module_param(dec, int, S_IRUGO | S_IWUSR);

static int md_init(void) {
    printk("dec: %d\n", dec);
    printk("dex: %x\n", dec);
    return 0;
}

static void md_exit(void) {

}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
