#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
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
__used __section("__versions") = {
	{ 0x3cd61e2b, "__platform_driver_register" },
	{ 0xce2840e7, "irq_set_irq_wake" },
	{ 0x3d0f9821, "input_event" },
	{ 0x6ab27649, "gpiod_get_value_cansleep" },
	{ 0x4dfa8d4b, "mutex_lock" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0xe455ba3b, "platform_driver_unregister" },
	{ 0x90e6520d, "devm_kmalloc" },
	{ 0xcefb0c9f, "__mutex_init" },
	{ 0x2fe3c750, "device_property_read_u32_array" },
	{ 0xe5d82004, "device_property_present" },
	{ 0x3257e1c3, "device_property_match_string" },
	{ 0x7b497abb, "_dev_err" },
	{ 0xe4d1d6c6, "_dev_info" },
	{ 0x6e6d18f, "devm_gpiod_get_array" },
	{ 0xa5f5679d, "devm_input_allocate_device" },
	{ 0x29145ff2, "input_set_capability" },
	{ 0x3ea1b6e4, "__stack_chk_fail" },
	{ 0xe8f30077, "dev_err_probe" },
	{ 0x81c43591, "input_set_abs_params" },
	{ 0xd54c5ee8, "gpiod_to_irq" },
	{ 0xfa6ab601, "devm_request_threaded_irq" },
	{ 0x362d204f, "input_register_device" },
	{ 0xcdaae80, "device_wakeup_disable" },
	{ 0xa9b8dd3a, "device_set_wakeup_capable" },
	{ 0x775a9e7e, "device_wakeup_enable" },
	{ 0x754e4864, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Crotary-encoder");
MODULE_ALIAS("of:N*T*Crotary-encoderC*");
