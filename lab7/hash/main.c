#include <linux/module.h>
#include <linux/scatterlist.h>
#include <linux/crypto.h>
#include <crypto/hash.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/ctype.h>

#define MEM_SIZE 1024

u8 type[MEM_SIZE], value[MEM_SIZE];
uint8_t * kernel_buffer;
dev_t dev_num;
struct class * device_class;
struct cdev * char_device;


struct sdesc {
    struct shash_desc shash;
    char ctx[];
};

static struct sdesc 
*init_sdesc(struct crypto_shash *alg) {
    struct sdesc *sdesc;
    int size;

    size = sizeof(struct shash_desc) + crypto_shash_descsize(alg);
    sdesc = kmalloc(size, GFP_KERNEL);
    if (!sdesc)
        return ERR_PTR(-ENOMEM);
    sdesc->shash.tfm = alg;
    return sdesc;
}

static int 
calc_hash
(
    struct crypto_shash *alg,
    const unsigned char *data, unsigned int datalen,
    unsigned char *digest
)
{
    struct sdesc *sdesc;
    int ret;

    sdesc = init_sdesc(alg);
    if (IS_ERR(sdesc)) {
        pr_info("can't alloc sdesc\n");
        return PTR_ERR(sdesc);
    }

    ret = crypto_shash_digest(&sdesc->shash, data, datalen, digest);
    kfree(sdesc);
    return ret;
}

static int 
sha1_hash
(
    const unsigned char *data, 
    unsigned int        datalen,
    unsigned char       *digest
)
{
    struct crypto_shash *alg;
    char *hash_alg_name = "sha1";
    int ret;

    alg = crypto_alloc_shash(hash_alg_name, 0, 0);
    if (IS_ERR(alg)) {
            pr_info("can't alloc alg %s\n", hash_alg_name);
            return PTR_ERR(alg);
    }
    ret = calc_hash(alg, data, datalen, digest);
    crypto_free_shash(alg);
    return ret;
}

static int 
sha224_hash
(
    const unsigned char *data, 
    unsigned int datalen,
    unsigned char *digest
)
{
    struct crypto_shash *alg;
    char *hash_alg_name = "sha224";
    int ret;

    alg = crypto_alloc_shash(hash_alg_name, 0, 0);
    if (IS_ERR(alg)) {
            pr_info("can't alloc alg %s\n", hash_alg_name);
            return PTR_ERR(alg);
    }
    ret = calc_hash(alg, data, datalen, digest);
    crypto_free_shash(alg);
    return ret;
}

static int 
md5_hash
(
    const unsigned char *data, 
    unsigned int datalen,
    unsigned char *digest
)
{
    struct crypto_shash *alg;
    char *hash_alg_name = "md5";
    int ret;

    alg = crypto_alloc_shash(hash_alg_name, 0, 0);
    if (IS_ERR(alg)) {
            pr_info("can't alloc alg %s\n", hash_alg_name);
            return PTR_ERR(alg);
    }
    ret = calc_hash(alg, data, datalen, digest);
    crypto_free_shash(alg);
    return ret;
}


static int open_fun(struct inode * inode, struct file * file) {
    return 0;
}

static int release_fun(struct inode * inode, struct file * file) {
    return 0;
}

static ssize_t 
read_fun
(
    struct file *file, 
    char        *user_buf, 
    size_t      len, 
    loff_t      *off
) 
{
    char out[30];
    int i, return_length;

    if (strcmp("md5", type) == 0) {
        md5_hash(value, strlen(value), out);
        return_length = 16;
    }

    if (strcmp("sha1", type) == 0) {
        sha1_hash(value, strlen(value), out);
        return_length = 20;
    }

    if (strcmp("sha224", type) == 0) {
        sha224_hash(value, strlen(value), out);
        return_length = 28;
    }

    copy_to_user(user_buf, out, return_length);    
    return return_length;
}


static ssize_t 
write_fun
(
    struct file *file, 
    const char  *user_buff, 
    size_t      len, 
    loff_t      *off
) 
{
    copy_from_user(kernel_buffer, user_buff, len);

    memset(type, 0, sizeof(type));
    memset(value, 0, sizeof(value));

    sscanf(kernel_buffer, "type:%s\nvalue:%s", type, value);
    printk("type: %s, value: %s\n", type, value);

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
