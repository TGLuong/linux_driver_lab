#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>


#define DRIVER_AUTHOR "luong"
#define DRIVER_DESC "simple"
#define MEM_SIZE 1024

dev_t dev_num = 0;
static struct class * device_class;
static struct cdev * example_cdev;
uint8_t *kernel_buffer;
unsigned open_cnt = 0;

static int example_open(struct inode * inode, struct file * file);
static int example_release(struct inode * inode, struct file * file);
static ssize_t example_read(struct file * file, char __user * user_buf, size_t len, loff_t * off);
static ssize_t example_write(struct file * file, const char * user_buf, size_t len, loff_t * off);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = example_read,
    .write = example_write,
    .open = example_open,
    .release = example_release,
};

static int example_open(struct inode * inode, struct file * file) {
    open_cnt++;
    printk("Handle opened event %u times\n", open_cnt);
    return 0;
}

static int example_release(struct inode * inode, struct file * file) {
    printk("Handle closed event %u times\n", open_cnt);
    return 0;
}

static ssize_t example_read(struct file * file, char __user * user_buf, size_t len, loff_t * off) {
    copy_to_user(user_buf, kernel_buffer, len);
    printk("Handle write event %u times\n", open_cnt);
    return 0;
}

static ssize_t example_write(struct file * file, const char __user * user_buf, size_t len, loff_t * off) {
    copy_from_user(kernel_buffer, user_buf, len);
    printk("Handle write event %u times\n", open_cnt);
    return len;
}

static int __init char_driver_init(void) {
    alloc_chrdev_region(&dev_num, 0, 1, "tendev");
    device_class = class_create(THIS_MODULE, "tenlop");
    device_create(device_class, NULL, dev_num, NULL, "tendevfile");
    kernel_buffer = kmalloc(MEM_SIZE, GFP_KERNEL);

    example_cdev = cdev_alloc();
    cdev_init(example_cdev, &fops);
    cdev_add(example_cdev, dev_num, 1);
    return 0;
}



void __exit char_driver_exit(void)
{
	cdev_del(example_cdev);
	kfree(kernel_buffer);
	device_destroy(device_class,dev_num);
	class_destroy(device_class);
	unregister_chrdev_region(dev_num, 1);
	printk("Remove character driver successfully.\n");
}


module_init(char_driver_init);
module_exit(char_driver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("3.0");
