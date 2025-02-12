#include <linux/module.h>
#include <linux/init.h>

// test comment
//Codec function when module is loaded into the kernel
//Static limits the visibility and linkage of the functions. Can be only called within this module
// __init and __exit macros only improve the readabililty of the functions
static int __init m_init(void)
{	
	printk(KERN_INFO "log level - This is an info\n");
	printk(KERN_WARNING "log level - This is a warning\n");
	printk(KERN_ALERT "log level - This is an alert\n");
	printk(KERN_DEBUG "log level - This is a debug\n");
	return 0;
}

//Function when module exits the kernel
static void __exit m_exit(void)
{
	pr_emerg("Module is unloaded\n");
}

//Telling which func to use when module loads and exits
module_init(m_init);
module_exit(m_exit);

//Specifying the license of the kernel module. GPL - General purpose license
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anuj Tripathi");
MODULE_DESCRIPTION("Hello world linux kernel module");
