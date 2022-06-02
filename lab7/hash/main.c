#include <linux/module.h>
#include <linux/scatterlist.h>
#include <linux/crypto.h>
#include <crypto/hash.h>



static int md_inti(void) {
    struct shash_desc *sdesc;
    struct crypto_shash *shash;
    char out[40];

    sdesc = kmalloc(sizeof(*sdesc), GFP_KERNEL);
    memset(out, 0, sizeof(out));

    sdesc->tfm = crypto_alloc_shash("sha1", 0, 0);

    crypto_shash_digest(sdesc, "luong", 5, out);

    printk("out: %s\n", out);

    crypto_free_shash(sdesc->tfm);
    kfree(sdesc);

    return 0;
}

static void md_exit(void) {
    
}

module_init(md_inti);
module_exit(md_exit);

MODULE_LICENSE("GPL");