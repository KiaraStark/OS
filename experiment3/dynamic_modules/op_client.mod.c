#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

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



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd272d446, "__fentry__" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0x673e371d, "my_op_ptr" },
	{ 0x97acb853, "ktime_get" },
	{ 0x5a844b26, "__x86_indirect_thunk_rax" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x4d8419c6, "param_ops_charp" },
	{ 0x4d8419c6, "param_ops_int" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x814e12e5, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0xbd03ed67,
	0x673e371d,
	0x97acb853,
	0x5a844b26,
	0xd272d446,
	0x4d8419c6,
	0x4d8419c6,
	0xe8213e80,
	0xd272d446,
	0x814e12e5,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__fentry__\0"
	"__ref_stack_chk_guard\0"
	"my_op_ptr\0"
	"ktime_get\0"
	"__x86_indirect_thunk_rax\0"
	"__stack_chk_fail\0"
	"param_ops_charp\0"
	"param_ops_int\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "op_provider");


MODULE_INFO(srcversion, "73B44E916BB330C6FEA0534");
