#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xb3753869, "module_layout" },
	{ 0xde4c1a24, "param_ops_charp" },
	{ 0x5ab5b891, "param_ops_int" },
	{ 0xa3bf6975, "param_array_ops" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xb356c301, "class_destroy" },
	{ 0xc38c6801, "device_destroy" },
	{ 0x37a0cba, "kfree" },
	{ 0x78f44845, "cdev_del" },
	{ 0x7afe113a, "cdev_add" },
	{ 0xa3036ef8, "cdev_init" },
	{ 0xe1bf6a21, "cdev_alloc" },
	{ 0xf5cb25c8, "kmem_cache_alloc_trace" },
	{ 0x35216b26, "kmalloc_caches" },
	{ 0xc79de84d, "device_create" },
	{ 0x8d62ea07, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x11089ac7, "_ctype" },
	{ 0xa916b694, "strnlen" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0xc5850110, "printk" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "58C7C97BF3AF84CD9A96F2C");
