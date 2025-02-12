#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static int major;


static ssize_t read_func (struct file *f, char __user *u, size_t l, loff_t *o){

	printk("Read function is called.\n");
	return 0;
}
static int open_driver(struct inode *device_file, struct file *instance){
	printk("hello-cdev driver was opened!\n");
	return 0;
}


static int close_driver(struct inode *device_file, struct file *instance){
	printk("hello-cdev driver was closed!\n");
	return 0;
}


//File operations object
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = read_func,
	.open = open_driver,
	.release = close_driver
};

//Codec function when module is loaded into the kernel
//Static limits the visibility and linkage of the functions. Can be only called within this module
// __init and __exit macros only improve the readabililty of the functions
static int __init m_init(void)
{	
	//this creates a new device file with given label and the first unused device number (0). 
	//A specific device number can be given in place of 0. 
	//The last argument is a pointer to the file operations object
	major = register_chrdev(0, "hello-cdev", &fops);

	if(major<0){
		printk("Error registering hello_cdev\n");
		return major;
	}
		
	printk("Major device number for hello_cdev: %d\n", major);
	return 0;
}

//Function when module exits the kernel
static void __exit m_exit(void)
{
	unregister_chrdev(major, "hello-cdev");
}

//Telling which func to use when module loads and exits
module_init(m_init);
module_exit(m_exit);

//Specifying the license of the kernel module. GPL - General purpose license
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anuj Tripathi");
MODULE_DESCRIPTION("Registering a character device");
