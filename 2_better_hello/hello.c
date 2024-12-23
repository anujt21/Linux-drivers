#include <linux/module.h>
#include <linux/init.h>

// test comment
//Codec function when module is loaded into the kernel
//Static limits the visibility and linkage of the functions. Can be only called within this module
// __init and __exit macros only improve the readabililty of the functions
static int __init m_init(void)
{	
	printk("hello Kernel!\n"); // always add newline char when printing anything to kernel
	return 0;
}

//Function when module exits the kernel
static void __exit m_exit(void)
{
	printk("Exit kernel\n");
}

//Telling which func to use when module loads and exits
module_init(m_init);
module_exit(m_exit);

//Specifying the license of the kernel module. GPL - General purpose license
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anuj Tripathi");
MODULE_DESCRIPTION("Hello world linux kernel module");
