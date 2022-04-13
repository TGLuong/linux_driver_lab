#include <linux/module.h>


int arr[1000];
int arr_length;
module_param_array(arr, int, &arr_length, S_IRUGO | S_IWUSR);

int ucln(int x, int y) {
    while (x != y) {
        if (x < y) {
            y -= x;
        } else {
            x -= y;
        }
    }
    return x;
}


static int md_init(void) {
    int i;
    printk("bat dau module\n");
    if (arr_length < 2) {
        printk("mang phan lon hon 2 phan tu\n");
        return -1;
    }
    for (i = 1; i < arr_length; i++) {
        arr[i] = ucln(arr[i - 1], arr[i]);
    }
    printk("ucln cua mang la: %d\n", arr[arr_length - 1]);
    return 0;
}

static void md_exit(void) {
    printk("ket thuc module\n");
}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
