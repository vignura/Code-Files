#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x6c90af03, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xf30a05be, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0x6cd19c73, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x990f6646, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0x826b144d, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x69799446, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xe4b19e11, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xde430b13, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x63f97ae1, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0xd31cc78e, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0xc671e369, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x754d539c, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xb5419b40, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x88db9f48, __VMLINUX_SYMBOL_STR(__check_object_size) },
	{ 0xaf5fca8a, __VMLINUX_SYMBOL_STR(mutex_trylock) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbaab9735, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

