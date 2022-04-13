#include <linux/module.h>
#include <linux/moduleparam.h>

#define MODULE_DES "bai1"

// lua chon chay chuong trinh
int choice = 0;
module_param(choice, int, S_IRUGO | S_IWUSR);

// tim uoc chung lon nhat cua 2 so a, b
int a = 0;
module_param(a, int, S_IRUGO | S_IWUSR);

int b = 0;
module_param(b, int, S_IRUGO | S_IWUSR);

// read arr and length of arr when install module
int arr[1000];
int arr_length = 0;
module_param_array(arr, int , &arr_length, S_IRUGO | S_IWUSR);


int sum(void) {
    int s = 0, i;
    for (i = 0; i < arr_length; i++) {
        s += arr[i];
    }
    return s;
}

int ucln(void) {
    int x = a, y = b;
    while (x != y) {
        if (x > y) {
            x = x - y;
        } else {
            y = y - x;
        }
    }
    return x;
}

static int md_init(void) {
    printk("init module\n");
    printk("choice : %d\n", choice);
    switch (choice) {
        case 1:
            printk("sum off array: %d\n", sum());
            break;
        case 2:
            printk("uoc chung lon nhat: %d\n", ucln());        
            break;
        default:
            break;
    }
    return 0;
}

static void md_exit(void) {
    printk("exit module\n");
}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(MODULE_DES);
