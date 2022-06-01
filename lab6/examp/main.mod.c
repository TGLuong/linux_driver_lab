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
	{ 0x6b7ba003, "usb_deregister" },
	{ 0xbf671e22, "usb_register_driver" },
	{ 0x56470118, "__warn_printk" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x25d9463f, "usb_register_dev" },
	{ 0xc5850110, "printk" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x4913dc6e, "usb_bulk_msg" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x139de1ed, "usb_deregister_dev" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("usb:v0781p5591d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "1FE693C71AFC4AE2652F37F");
