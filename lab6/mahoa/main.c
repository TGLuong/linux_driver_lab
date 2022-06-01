#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/ctype.h>

#define MEM_SIZE 1024

int k1;
module_param(k1, int, S_IRUGO);

char *k2 = "";
module_param(k2, charp, S_IRUGO);

int k3[100];
int length;
module_param_array(k3, int, &length, S_IRUGO);

char cmd[MEM_SIZE], value[MEM_SIZE];
uint8_t * kernel_buffer;
dev_t dev_num;
static struct class * device_class;
static struct cdev * char_device;

static int open_fun(struct inode * inode, struct file * file) {
    return 0;
}

static int release_fun(struct inode * inode, struct file * file) {
    return 0;
}

static ssize_t read_fun(struct file * file, char * user_buf, size_t len, loff_t * off) {
    char buffer[MEM_SIZE];
    int i;

    if (strcmp(cmd, "ma-hoa-dich-chuyen") == 0) {
        strcpy(buffer, value);
        for (i = 0; i < strlen(buffer); i++) {
            if (isalpha(buffer[i])) {
                buffer[i] += k1;
                while (!isalpha(buffer[i])) buffer[i] -= 26;
            }
        }
    }

    if (strcmp(cmd, "ma-hoa-thay-the") == 0) {
        memset(buffer, 0, sizeof(buffer));
        for (i = 0; i < strlen(value); i++) {
            buffer[i] = plant_text[k3[i]];
        }
    }

    if (strcmp(cmd, "ma-hoa-hoan-vi") == 0) {

    }

    if (strcmp(cmd, "giai-ma-dich-chuyen") == 0) {
        strcpy(buffer, value);
        for (i = 0; i < strlen(buffer); i++) {
            if (isalpha(buffer[i])) {
                buffer[i] -= k1;
                while (!isalpha(buffer[i])) buffer[i] += 26;
            }
        }
    }

    copy_to_user(user_buf, buffer, 800);
    printk("handle read\n");
    return len;
}

static ssize_t write_fun(struct file * file, const char * user_buff, size_t len, loff_t * off) {
    copy_from_user(kernel_buffer, user_buff, len);

    memset(cmd, 0, sizeof(cmd));
    memset(value, 0, sizeof(value));

    sscanf(kernel_buffer, "cmd:%s\nvalue:%s", cmd, value);
    printk("cmd: %s, value: %s\n", cmd, value);

    printk("handle write\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = read_fun,
    .write = write_fun,
    .open = open_fun,
    .release = release_fun
};


static int md_init(void) {
    alloc_chrdev_region(&dev_num, 0, 1, "thietbi");
    device_class = class_create(THIS_MODULE, "lop");
    device_create(device_class, NULL, dev_num, NULL, "lab6_ma_hoa");

    kernel_buffer = kmalloc(MEM_SIZE, GFP_KERNEL);

    char_device = cdev_alloc();
    cdev_init(char_device, &fops);
    cdev_add(char_device, dev_num, 1);
    return 0;
}

static void md_exit(void) {
    cdev_del(char_device);
    kfree(kernel_buffer);
    device_destroy(device_class, dev_num);
    class_destroy(device_class);
    unregister_chrdev_region(dev_num, 1);
    printk("exit module\n");
}


module_init(md_init);
module_exit(md_exit);


MODULE_LICENSE("GPL");