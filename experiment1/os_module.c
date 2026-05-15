#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kiara Stark");
MODULE_DESCRIPTION("A simple Linux kernel module.");
MODULE_VERSION("1.0");

static int kiara_module_int(void){
    printk(KERN_ALERT "Hello!\n");
    return 0;
}

static void kiara_module_exit(void){
    printk(KERN_ALERT "Goodbye!\n");
}

module_init(kiara_module_int);
module_exit(kiara_module_exit);