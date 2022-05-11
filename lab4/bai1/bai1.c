#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/cdev.h>

#define MEM_SIZE 1024

uint8_t * kernel_buffer;
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
    copy_to_user(user_buf, kernel_buffer, MEM_SIZE);
    printk("handle read\n");
    return len;
}

static ssize_t write_fun(struct file * file, const char * user_buff, size_t len, loff_t * off) {
    copy_from_user(kernel_buffer, user_buff, len);
    printk("handle write\n");
    return 0;
}



static int md_init(void) {
    alloc_chrdev_region(&dev_num, 0, 1, "thietbi");
    device_class = class_create(THIS_MODULE, "lop");
    device_create(device_class, NULL, dev_num, NULL, "lab4_1_tran_gia_luong");

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
