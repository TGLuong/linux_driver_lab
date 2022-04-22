#include <linux/module.h>
#include <linux/ctype.h>

char *plant_text = "";
module_param(plant_text, charp, S_IRUGO);

int k1;
module_param(k1, int, S_IRUGO);

char *k2 = "";
module_param(k2, charp, S_IRUGO);

int k3[100];
int length;
module_param_array(k3, int, &length, S_IRUGO);



void chuyen_vi(void) {
    char buffer[100];
    int i;

    strcpy(buffer, plant_text);
    for (i = 0; i < strlen(buffer); i++) {
        if (isalpha(buffer[i])) {
            buffer[i] += k1;
            while (!isalpha(buffer[i])) buffer[i] -= 26;
        }
    }

    printk("k1: %s\n", buffer);
}

void hoan_vi(void) {
    char buffer[100];
    int i;

    memset(buffer, 0, sizeof(buffer));
    if (length == strlen(plant_text)) {
        for (i = 0; i < strlen(plant_text); i++) {
            buffer[i] = plant_text[k3[i]];
        }
    }

    printk("k3: %s\n", buffer);
}

void thay_the(void) {
    char buffer[100];
    int i;

    strcpy(buffer, plant_text);
    for(i = 0; i < strlen(buffer); i++) {
        if (isalpha(buffer[i])) buffer[i] = k2[buffer[i] - 97];
    }

    printk("k2: %s\n", buffer);
}


static int md_init(void) {
    printk("xau ro: %s\n", plant_text);
    chuyen_vi();
    thay_the();
    hoan_vi();
    return 0;
}

static void md_exit(void) {
    printk("module exit\n");
}



module_init(md_init);
module_exit(md_exit);


MODULE_LICENSE("GPL");