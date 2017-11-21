#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

// to build on debian install package: apt-get install linux-headers-$(uname -r)
// build module: make
//
// load module: insmod hello_module.ko
//
// load module with parameter: insmod hello_module.ko my_arg1=some_test_string
// parameter string will be written to /var/log/kern.log
//
// unload module: rmmod hello_module.ko
// module info: modinfo hello_module.ko

MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("hello world module");

static char *my_arg1 = "world";
module_param(my_arg1, charp, S_IRUGO);
MODULE_PARM_DESC(my_arg1, "string that will be written to kernel log");

static int __init hello_init(void)
{
    printk(KERN_INFO "hello module init %s!\n", my_arg1);
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "hello module exit %s!\n", my_arg1);
}

module_init(hello_init);
module_exit(hello_exit);

