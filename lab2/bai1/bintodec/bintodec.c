#include <linux/module.h>

char *bin = "";
module_param(bin, charp, S_IRUGO | S_IWUSR);

int power(int x, int e) {
    int n = 1;
    if (e == 0) {
        return 1;
    }
    while (e > 0) {
        n *= x;
        e--;
    }
    return n;
}

static int md_init(void) {
    int i, dec = 0, length = strlen(bin);

    printk("bin: %s\n", bin);
    for (i = 0; i < length / 2; i++) {
        char b = bin[i];
        bin[i] = bin[length - 1 - i];
        bin[length - 1 - i] = b;
    }

    for (i = 0; i < length; i++) {
        if (bin[i] == '1') {
            dec += power(2, i);
        }
    }
    printk("dec: %d\n", dec);
    return 0;
}

static void md_exit(void) {

}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
