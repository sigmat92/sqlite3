#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

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
	{ 0x54b1fac6, "__ubsan_handle_load_invalid_value" },
	{ 0x4dfa8d4b, "mutex_lock" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0x67a33343, "devm_kmalloc" },
	{ 0xcefb0c9f, "__mutex_init" },
	{ 0x7b1277ca, "device_property_read_u32_array" },
	{ 0xb7554b15, "device_property_present" },
	{ 0x3b4cf56c, "_dev_info" },
	{ 0xe8f4b7e3, "devm_gpiod_get_array" },
	{ 0x15ed0381, "devm_input_allocate_device" },
	{ 0xb0c0546c, "input_set_abs_params" },
	{ 0x3a1b27aa, "_dev_err" },
	{ 0x74e47b44, "device_property_match_string" },
	{ 0xd5c13bf7, "input_set_capability" },
	{ 0x1b1db38c, "gpiod_to_irq" },
	{ 0x427de137, "devm_request_threaded_irq" },
	{ 0xf36ec2f1, "input_register_device" },
	{ 0xcac4a295, "device_wakeup_disable" },
	{ 0xe1a38ba1, "device_set_wakeup_capable" },
	{ 0x48c6b958, "device_wakeup_enable" },
	{ 0x89d21ee2, "dev_err_probe" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xa648e561, "__ubsan_handle_shift_out_of_bounds" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xfc802b99, "__platform_driver_register" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xce2840e7, "irq_set_irq_wake" },
	{ 0x4c068e46, "gpiod_get_value_cansleep" },
	{ 0x81ef79db, "platform_driver_unregister" },
	{ 0xdf4c28a8, "input_event" },
	{ 0xc6227e48, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "1FD3A79ED28B01AAAF71218");
