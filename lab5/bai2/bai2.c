#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/timekeeping.h>
#include <linux/jiffies.h>

#define MEM_SIZE 1024

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

    
    if (strcmp(kernel_buffer, "micro") == 0) {
        struct timeval tv;
        jiffies_to_timeval(jiffies, &tv);
        sprintf(buffer, "%ld.%ld\n", tv.tv_sec, tv.tv_usec);    
        printk("%s\n", buffer);
    }

    if (strcmp(kernel_buffer, "nano") == 0) {
        struct timespec ts;
        jiffies_to_timespec(jiffies, &ts);
        sprintf(buffer, "%ld.%ld\n", ts.tv_sec, ts.tv_nsec);
        printk("%s\n", buffer);
    }

    if (strcmp(kernel_buffer, "relative") == 0) {
        struct timespec64 ts;
        ktime_get_ts64(&ts);
        sprintf(buffer, "%lld.%ld\n", ts.tv_sec, ts.tv_nsec);
        printk("%s\n", buffer);
    }

    copy_to_user(user_buf, buffer, MEM_SIZE);
    return 0;
}

static ssize_t write_fun(struct file * file, const char * user_buf, size_t len, loff_t * off) {
    memset(kernel_buffer, 0, MEM_SIZE);
    copy_from_user(kernel_buffer, user_buf, len);
    return 0;
}




static int md_init(void) {
    alloc_chrdev_region(&dev_num, 0, 1, "thietbi");
    device_class = class_create(THIS_MODULE, "lop");
    device_create(device_class, NULL, dev_num, NULL, "lab5_2_mai_lam");

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
