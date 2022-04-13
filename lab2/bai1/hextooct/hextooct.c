#include <linux/ctype.h>
#include <linux/module.h>

char *hex = "";
module_param(hex, charp, S_IRUGO);

char *bincvt[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
                  "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

char *octcvt[] = {"0", "1", "2", "3", "4", "5", "6", "7"};


static int md_init(void) {
    int i, j, to_num;
    char bin_buffer[100];
    char oct_buffer[100];

    memset(bin_buffer, 0, sizeof(bin_buffer));
    memset(oct_buffer, 0, sizeof(oct_buffer));

    printk("hex: %s\n", hex);
    for (i = 0; i < strlen(hex); i++) {
         if (isdigit(hex[i])) {
             strcat(bin_buffer, bincvt[hex[i] - 48]);
         }
         else if (islower(hex[i])) {
             strcat(bin_buffer, bincvt[hex[i] - 87]);
         }
         else if (isupper(hex[i])) {
             strcat(bin_buffer, bincvt[hex[i] - 55]);
         }
    }

    i = strlen(bin_buffer) - 1;
    while (i >= 0) {
        to_num = 0;
        if (i >= 0 && bin_buffer[i] == '1') {
            to_num ^= 1;
        }
        i--;
        if (i >= 0 && bin_buffer[i] == '1') {
            to_num ^= 2;
        }
        i--;
        if (i >= 0 && bin_buffer[i] == '1') {
            to_num ^= 4;
        }
        i--;
        strcat(oct_buffer, octcvt[to_num]);
    }
    j = strlen(oct_buffer);
    for (i = 0; i < j / 2; i++) {
        char b = oct_buffer[i];
        oct_buffer[i] = oct_buffer[j - 1 - i];
        oct_buffer[j - 1 - i] = b;
    }
    printk("bin: %s\n", oct_buffer);
    return 0;
}

static void md_exit(void) {

}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
