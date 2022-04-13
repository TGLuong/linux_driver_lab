#include <linux/ctype.h>
#include <linux/module.h>

char *string = "";
module_param(string, charp, S_IRUGO | S_IWUSR);

char *s1 = "";
module_param(s1, charp, S_IRUGO | S_IWUSR);

char *s2 = "";
module_param(s2, charp, S_IRUGO | S_IWUSR);

int endc = 0;
module_param(endc, int, S_IRUGO);


int length(char *s) {
    int n = 0, i;
    if (endc == 0) return strlen(s);
    for (i = 0; i < strlen(s); i++) {
        if (s[i] == endc) {
            n = i;
            break;
        }
    }
    return n;
}

static int md_init(void) {
    int i;
    char buffer[100];
    
    memset(buffer, 0, sizeof(buffer));


    printk("%s\n", string);
    printk("length: %d\n", length(string));

    strcpy(buffer, string);
    for (i = 0; i < strlen(buffer) / 2; i++) {
        char b = buffer[i];
        buffer[i] = buffer[strlen(buffer) - 1 - i];
        buffer[strlen(buffer) - 1 - i] = b;
    }
    printk("dao nguoc: %s\n", buffer);

    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, string, length(string));
    for (i = 0; i < strlen(buffer) / 2; i++) {
        char b = buffer[i];
        buffer[i] = buffer[strlen(buffer) - 1 - i];
        buffer[strlen(buffer) - 1 - i] = b;
    }   
    printk("dao nguoc voi ky tu ket thuc: %s\n", buffer);

    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, string);

    i = 0;
    while (i < strlen(buffer)) {
        while (i < strlen(buffer) && buffer[i] == ' ') i++;
        if (islower(buffer[i])) {
            buffer[i] -= 32;
        }
        i++;
        while (i < strlen(buffer) && buffer[i] != ' ') {
            if (isupper(buffer[i])) buffer[i] += 32;
            i++;
        }
    }

    printk("chuan hoa: %s\n", buffer);

    strcat(s1, s2);
    printk("noi chuoi: %s\n", s1);

    return 0;
}

static void md_exit(void) {

}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
