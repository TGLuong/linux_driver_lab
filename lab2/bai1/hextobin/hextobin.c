#include <linux/ctype.h>
#include <linux/module.h>

char *hex = "";
module_param(hex, charp, S_IRUGO);

char *converter[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
                     "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

static int md_init(void) {
    int i;
    char buffer[1000];
    memset(buffer, 0, sizeof(memset));

    printk("hex: %s\n", hex);
    for (i = 0; i < strlen(hex); i++) {
        if (isdigit(hex[i])) {
            strcat(buffer, converter[hex[i] - 48]);
        } 
        else if (islower(hex[i])) {
            strcat(buffer, converter[hex[i] - 87]);
        }
        else if (isupper(hex[i])) {
            strcat(buffer, converter[hex[i] - 55]);
        }
    }
    printk("bin: %s\n", buffer);
    return 0;
}

static void md_exit(void) {

}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
