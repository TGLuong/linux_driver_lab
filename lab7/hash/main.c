#include <linux/module.h>
#include <linux/scatterlist.h>
#include <linux/crypto.h>
#include <crypto/hash.h>

#define MEM_SIZE 1024

char type[MEM_SIZE], value[MEM_SIZE];
uint8_t * kernel_buffer;
dev_t dev_num;
struct class * device_class;
struct cdev * char_device;

static int open_fun(struct inode * inode, struct file * file) {
    return 0;
}

static int release_fun(struct inode * inode, struct file * file) {
    return 0;
}

static ssize_t read_fun(struct file * file, char * user_buf, size_t len, loff_t * off) {
    struct shash_desc *sdesc;
    struct crypto_shash *shash;
    char out[40];

    sdesc = kmalloc(sizeof(*sdesc), GFP_KERNEL);
    memset(out, 0, sizeof(out));

    if (strcmp(type, "MD5") == 0) {

    }

    if (strcmp(type, "sha1") == 0) {
        shash = crypto_alloc_shash("sha1", 0, 0);
        sdesc->tfm = shash;
        crypto_shash_digest(sdesc, value, strlen(value), out);

        printk("out: %s\n", out);

        crypto_free_shash(sdesc->tfm);
        kfree(sdesc);
    }

    if (strcmp(type, "sha224") == 0) {
        
    }
    
    copy_to
    return len;
}


static ssize_t write_fun(struct file * file, const char * user_buff, size_t len, loff_t * off) {
    copy_from_user(kernel_buffer, user_buff, len);

    memset(type, 0, sizeof(type));
    memset(value, 0, sizeof(value));

    sscanf(kernel_buffer, "type:%s\nvalue:%s", type, value);
    printk("cmd: %s, value: %s\n", type, value);

    printk("handle write\n");
    return 0;
}

static int md_init(void) {
    alloc_chrdev_region(&dev_num, 0, 1, "thietbi");
    device_class = class_create(THIS_MODULE, "lop");
    device_create(device_class, NULL, dev_num, NULL, "lab7_ma_hoa");

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