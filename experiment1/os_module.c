#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kiara Stark");
MODULE_DESCRIPTION("A simple Linux kernel module.");
MODULE_VERSION("1.0");

static char *whom = "Kiara Stark";
module_param(whom, charp, S_IRUGO);

static int num = 1;
module_param(num, int, S_IRUGO);

static int kiara_module_int(void){
    int i;
    for(i=0;i<num;i++){
        printk(KERN_ALERT "Hello!My name is%s\n",whom);
    }
    return 0;
}

static void kiara_module_exit(void){
    printk(KERN_ALERT "Goodbye!\n");
}

module_init(kiara_module_int);
module_exit(kiara_module_exit);