#include <linux/ctype.h>
#include <linux/module.h>

int dec = 0;
module_param(dec, int, S_IRUGO | S_IWUSR);

static int md_init(void) {
    int i, length = 0;
    char buffer[100], bin[100];
    memset(buffer, 0, sizeof(buffer));
    memset(bin, 0, sizeof(bin));

    printk("%d\n", dec);
    while (dec != 0) {
        if (dec % 2 == 0) {
            bin[length] = '0';
        } else {
            bin[length] = '1';
        }
        length++;
        dec = dec / 2;
    }
    for (i = 0; i < length ; i++) {
        buffer[i] = bin[length - 1 - i];
    }
    printk("bin: %s\n", buffer);
    return 0;
}

static void md_exit(void) {

}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
