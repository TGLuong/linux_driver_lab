#include <linux/module.h>

char *bin = "";
module_param(bin, charp, S_IRUGO);

char *converter[] = {"0", "1", "2", "3", "4", "5", "6", "7"};

static int md_init(void) {
    int length = strlen(bin) - 1, i, buffer;
    char oct[1000];
    printk("bin: %s\n", bin);

    memset(oct, 0, sizeof(oct));
    
    while (length >= 0) {
        buffer = 0;
        if (length >= 0 && bin[length] == '1') {
            buffer ^= 1;
        }
        length--;
        if (length >= 0 && bin[length] == '1') {
            buffer ^= 2;
        }
        length--;
        if (length >= 0 && bin[length] == '1') {
            buffer ^= 4;
        }
        length--;
        strcat(oct, converter[buffer]);
    }
    length = strlen(oct);
    for (i = 0; i < length / 2; i++) {
        char b = oct[i];
        oct[i] = oct[length - 1 - i];
        oct[length - 1 - i] = b;
    }
    printk("oct: %s\n", oct);
    return 0;
}

static void md_exit(void) {

}


module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
