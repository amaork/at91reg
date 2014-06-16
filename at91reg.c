#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <asm/io.h>
#include <linux/cdev.h>
#include <linux/mm.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <asm/processor.h>
#include <asm/uaccess.h>								/* Copy from user */
#include <asm/page.h>

struct at91reg_dev{
	struct miscdevice 	dev;
};

static struct at91reg_dev at91reg;

#define DEVICE_NAME				"at91reg"
#define DEVICE_MINOR			12
#define REG_BASE_PHY_ADDR		0xfffff000

MODULE_AUTHOR("amaork@gmail.com");
MODULE_VERSION("AT91REG_V1.2");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("ARM SCR User Interface");

static int at91reg_open(struct inode *inode, struct file *file){
	return 0;
}

static int at91reg_release(struct inode *inode, struct file *file){
	return 0;	
}

static int at91reg_mmap(struct file *file, struct vm_area_struct *vma)
{
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	if(remap_pfn_range(vma, vma->vm_start, REG_BASE_PHY_ADDR>>PAGE_SHIFT, PAGE_SIZE, vma->vm_page_prot))
		return -EAGAIN;

	return 0;
}

static	struct file_operations at91reg_fops	=	{
	.owner		=	THIS_MODULE,
	.open		=	at91reg_open,
	.release	=	at91reg_release,
	.mmap		=	at91reg_mmap,
};

static int __init reg_init(void){

	int ret;
	memset(&at91reg, 0, sizeof(at91reg));
	
	/* Fill misc device structure */
	at91reg.dev.name	=	DEVICE_NAME;
	at91reg.dev.minor	=	DEVICE_MINOR;
	at91reg.dev.fops	=	&at91reg_fops;	

	/* Register lcd as a misc device */
	if ((ret = misc_register(&at91reg.dev))){
		printk(KERN_ERR "Failed to register %s as a misc device!\n", DEVICE_NAME);
		return ret;
	}			
	else{
		printk(KERN_INFO "Success install %s module, minor is %d !\n", DEVICE_NAME, DEVICE_MINOR);
		return 0;
	}
}

static void __exit reg_exit(void){

	misc_deregister(&at91reg.dev);	
	printk(KERN_INFO "Success uninstall %s module!\n", DEVICE_NAME);
}

module_init(reg_init);
module_exit(reg_exit);

