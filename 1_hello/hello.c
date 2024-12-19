#include <linux/module.h>
#include <linux/init.h>

//Codec function when module is loaded into the kernel
int m_init(void)
{	
	printk("hello Kernel!\n"); // always add newline char when printing anything to kernel
	return 0;
}

//Function when module exits the kernel
void m_exit(void)
{
	printk("Exit kernel\n");
}

//Telling which func to use when module loads and exits
module_init(m_init);
module_exit(m_exit);

//Specifying the license of the kernel module. GPL - General purpose license
MODULE_LICENSE("GPL");
