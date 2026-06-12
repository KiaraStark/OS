#include <linux/errno.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/module.h>
#include <linux/types.h>

#include "op_common.h"

extern my_op_func_t my_op_ptr;

static int num1;
module_param(num1, int, 0644);
MODULE_PARM_DESC(num1, "First integer operand");

static int num2 = 1;
module_param(num2, int, 0644);
MODULE_PARM_DESC(num2, "Second integer operand");

static char *op = "+";
module_param(op, charp, 0644);
MODULE_PARM_DESC(op, "Operator: +, -, *, /");

static int __init op_client_init(void)
{
	int result = 0;
	u64 elapsed_ns;
	u64 end_ns;
	u64 start_ns;
	long ret;

	if (!my_op_ptr) {
		pr_err("op_client: my_op_ptr is NULL, load op_provider first\n");
		return -ENODEV;
	}

	start_ns = ktime_get_ns();
	ret = my_op_ptr(&result, num1, num2, op);
	end_ns = ktime_get_ns();
	elapsed_ns = end_ns - start_ns;

	if (ret) {
		pr_err("op_client: operation failed, ret=%ld, elapsed=%llu ns\n",
		       ret, elapsed_ns);
		return ret;
	}

	pr_info("op_client: %d %c %d = %d, elapsed=%llu ns\n",
		num1, op[0], num2, result, elapsed_ns);
	return 0;
}

static void __exit op_client_exit(void)
{
	pr_info("op_client: unloaded\n");
}

module_init(op_client_init);
module_exit(op_client_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kiara Stark");
MODULE_DESCRIPTION("Integer arithmetic client using exported function pointer");
MODULE_VERSION("1.0");
MODULE_SOFTDEP("pre: op_provider");
