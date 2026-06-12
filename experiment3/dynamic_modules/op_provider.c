#include <linux/errno.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include "op_common.h"

static long do_integer_op(int *result, int num1, int num2, char *op)
{
	int res = 0;
	char op_char;
	int i;

	if (!result || !op)
		return -EFAULT;

	op_char = *op;
	if (op_char == '/' && num2 == 0)
		return -EINVAL;

	for (i = 0; i < MY_OP_ITERATIONS; ++i) {
		switch (op_char) {
		case '+':
			res = num1 + num2;
			break;
		case '-':
			res = num1 - num2;
			break;
		case '*':
			res = num1 * num2;
			break;
		case '/':
			res = num1 / num2;
			break;
		default:
			return -EINVAL;
		}
	}

	*result = res;
	return 0;
}

my_op_func_t my_op_ptr;
EXPORT_SYMBOL(my_op_ptr);

static int __init op_provider_init(void)
{
	my_op_ptr = do_integer_op;
	pr_info("op_provider: exported my_op_ptr\n");
	return 0;
}

static void __exit op_provider_exit(void)
{
	my_op_ptr = NULL;
	pr_info("op_provider: unloaded\n");
}

module_init(op_provider_init);
module_exit(op_provider_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kiara Stark");
MODULE_DESCRIPTION("Integer arithmetic provider exporting a function pointer");
MODULE_VERSION("1.0");
