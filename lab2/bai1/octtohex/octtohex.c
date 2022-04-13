#include <linux/module.h>

char *oct = "";
module_param(oct, charp, S_IRUGO);

char *bincvt[] = {"000", "001", "010", "011", "100", "101", "110", "111"};

char *hexcvt[] = {"0", "1", "2", "3", "4", "5", "6", "7",
                  "8", "9", "a", "b", "c", "d", "e", "f"};


static int md_init(void) {
    int i, j, to_num;
    char bin_buffer[100];
    char hex_buffer[100];

    memset(bin_buffer, 0, sizeof(bin_buffer));
    memset(hex_buffer, 0, sizeof(hex_buffer));

    printk("oct: %s\n", oct);
    for (i = 0; i < strlen(oct); i++) {
        strcat(bin_buffer, bincvt[oct[i] - 48]);
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
        if (i >= 0 && bin_buffer[i] == '1') {
            to_num ^= 8;
        }
        i--;
        strcat(hex_buffer, hexcvt[to_num]);
    }
    j = strlen(hex_buffer);
    for (i = 0; i < j / 2; i++) {
        char b = hex_buffer[i];
        hex_buffer[i] = hex_buffer[j - 1 - i];
        hex_buffer[j - 1 - i] = b;
    }
    printk("bin: %s\n", hex_buffer);
    return 0;
}

static void md_exit(void) {

}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
