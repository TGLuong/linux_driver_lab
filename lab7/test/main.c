#include <linux/module.h>
#include <linux/scatterlist.h>
#include <crypto/hash.h>
#include <linux/stat.h>



struct sdesc {
    struct shash_desc shash;
    char ctx[];
};

struct sdesc *init_sdesc(struct crypto_shash *alg)
{
    struct sdesc *sdesc;
    int size;

    size = sizeof(struct shash_desc) + crypto_shash_descsize(alg);
    sdesc = kmalloc(size, GFP_KERNEL);
    if (!sdesc)
        return ERR_PTR(-ENOMEM);
    sdesc->shash.tfm = alg;
    return sdesc;
}

int calc_hash(struct crypto_shash *alg,
             const unsigned char *data, unsigned int datalen,
             unsigned char *digest)
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

int test_hash(const unsigned char *data, unsigned int datalen,
             unsigned char *digest)
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

static int md_init(void) {
    int i;
    char data[20] = "gialuong";
    char out[20];

    test_hash(data, strlen(data), out);

    printk("sha1: \n");
    for (i = 0; i < 20; i++) {
        printk("%02hhx\n", out[i]);
    } 
    printk("end sha1\n");

    return 0;
}

static void md_exit(void) {

}

module_init(md_init);
module_exit(md_exit);

MODULE_LICENSE("GPL");