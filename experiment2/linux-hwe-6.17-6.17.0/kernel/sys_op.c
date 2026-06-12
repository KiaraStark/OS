#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>

#define MY_OP_ITERATIONS 100000

SYSCALL_DEFINE4(my_op, int __user *, result, int, num1, int, num2, char __user *, op)
{
    int res = 0;
    char op_char;
    int i;

    if (!result || !op)
        return -EFAULT;

    if (get_user(op_char, op))
        return -EFAULT;

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

    if (copy_to_user(result, &res, sizeof(res)))
        return -EFAULT;

    return 0;
}
