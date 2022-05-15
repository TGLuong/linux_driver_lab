#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/cdev.h>

#define MEM_SIZE 1000
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')


char cmd[MEM_SIZE], value[MEM_SIZE];
char * kernel_buffer;
dev_t dev_num;
static struct class * device_class;
static struct cdev * char_device;


static ssize_t read_fun(struct file * file, char * user_buf, size_t len, loff_t * off);
static ssize_t write_fun(struct file * file, const char * user_buf, size_t len, loff_t * off);
static int open_fun(struct inode * inode, struct file * file);
static int release_fun(struct inode * inode, struct file * file);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = read_fun,
    .write = write_fun,
    .open = open_fun,
    .release = release_fun
};

static int open_fun(struct inode * inode, struct file * file) {
    printk("handle open charator device\n");
    return 0;
}

static int release_fun(struct inode * inode, struct file * file) {
    printk("handle release charator deivce\n");
    return 0;
}

static ssize_t read_fun(struct file * file, char * user_buf, size_t len, loff_t * off) {
    char buffer[MEM_SIZE];
    long l;

    kstrtol(value, 0, &l);

    if (strcmp(cmd, "hex") == 0) {
        sprintf(buffer, "%lx\n", l);
        printk("%s\n", buffer);
    }

    if (strcmp(cmd, "bin") == 0) {
        sprintf(buffer, BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(l));        
        printk("%s\n", buffer);
    }

    if (strcmp(cmd, "oct") == 0) {
        sprintf(buffer, "%lo\n", l);
        printk("%s\n", buffer);
    }

    copy_to_user(user_buf, buffer, MEM_SIZE);
    return 0;
}

static ssize_t write_fun(struct file * file, const char * user_buf, size_t len, loff_t * off) {
    copy_from_user(kernel_buffer, user_buf, len);

    memset(cmd, 0, sizeof(cmd));
    memset(value, 0, sizeof(value));

    sscanf(kernel_buffer, "cmd:%s\nvalue:%s", cmd, value);
    printk("cmd: %s, value: %s\n", cmd, value);

    return 0;
}




static int md_init(void) {
    alloc_chrdev_region(&dev_num, 0, 1, "thietbi");
    device_class = class_create(THIS_MODULE, "lop");
    device_create(device_class, NULL, dev_num, NULL, "lab5_1_tran_gia_luong");

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

MODULE_LICENSE("GPL");
module_init(md_init);
module_exit(md_exit);
