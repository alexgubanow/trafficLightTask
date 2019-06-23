#include "lghtIO.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
//#include "lghtIO_ioctl.h"

#define FIRST_MINOR 0
#define MINOR_CNT 1

static dev_t dev;
static struct cdev c_dev;
static struct class* cl;
static lghtColor lColor = Ylw;
static int idx = -1;

static int lghtIO_open(struct inode* i, struct file* f) { return 0; }
static int lghtIO_close(struct inode* i, struct file* f) { return 0; }
static lghtColor getColor(int targetIdx);
static void setColor(lghtColor targetColor, int targetIdx);


#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
static int lghtIO_ioctl(struct inode* i, struct file* f, unsigned int cmd, unsigned long arg)
#else
static long lghtIO_ioctl(struct file* f, unsigned int cmd, unsigned long arg)
#endif
{
	lghtIO_arg_t q;

	switch (cmd)
	{
	case getLghtByIdx:
		printk(KERN_INFO "Request for Light\n");
		if (copy_from_user(&q, (lghtIO_arg_t*)arg, sizeof(lghtIO_arg_t)))
		{
			printk(KERN_ERR "Error while getting data from user about Light\n");
			return -EACCES;
		}
		q.clrT = getColor(q.idx);
		if (copy_to_user((lghtIO_arg_t*)arg, &q, sizeof(lghtIO_arg_t)))
		{
			printk(KERN_ERR "Error while transmitting data to user about Light\n");
			return -EACCES;
		}
		break;
	case resetLghtByIdx:
		printk(KERN_INFO "Request for resert Light\n");
		if (copy_from_user(&q, (lghtIO_arg_t*)arg, sizeof(lghtIO_arg_t)))
		{
			printk(KERN_ERR "Error while getting data from user about Light\n");
			return -EACCES;
		}
		setColor(Ylw, q.idx);
		break;
	case setLghtByIdx:
		printk(KERN_INFO "Request for set Light\n");
		if (copy_from_user(&q, (lghtIO_arg_t*)arg, sizeof(lghtIO_arg_t)))
		{
			printk(KERN_ERR "Error while getting data from user about Light\n");
			return -EACCES;
		}
		setColor(q.clrT, q.idx);
		break;
	case removeLghtByIdx:
		printk(KERN_INFO "Request for remove Light\n");
		if (copy_from_user(&q, (lghtIO_arg_t*)arg, sizeof(lghtIO_arg_t)))
		{
			printk(KERN_ERR "Error while getting data from user about Light\n");
			return -EACCES;
		}
		//need to insert here removing call
		break;
	default:
		printk(KERN_ERR "Received wrong control sequence\n");
		return -EINVAL;
	}

	return 0;
}

lghtColor getColor(int targetIdx)
{
	return lColor;
}

void setColor(lghtColor targetColor, int targetIdx)
{
	idx = targetIdx;
	lColor = targetColor;
	switch (targetColor)
	{
	case Grn:
		printk(KERN_INFO "Light idx#%d is become to Green\n", targetIdx);
		break;
	case Ylw:
		printk(KERN_INFO "Light idx#%d is become to Yellow\n", targetIdx);
		break;
	case Red:
		printk(KERN_INFO "Light idx#%d is become to Red\n", targetIdx);
		break;
	default:
		printk(KERN_ERR "Received wrong color for Light idx#%d\n", targetIdx);
		break;
	}
}

static struct file_operations lghtIO_fops =
{

	.owner = THIS_MODULE,
	.open = lghtIO_open,
	.release = lghtIO_close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
	.ioctl = lghtIO_ioctl
#else
	.unlocked_ioctl = lghtIO_ioctl
#endif
};
static int __init lghtIO_ioctl_init(void)
{
	int ret;
	struct device* dev_ret;


	if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "lghtIO_ioctl")) < 0)
	{
		printk(KERN_DEBUG "Fail while alloc region for lghtIO\n");
		return ret;
	}
	printk(KERN_DEBUG "Allocated region for lghtIO\n");

	cdev_init(&c_dev, &lghtIO_fops);

	if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0)
	{
		printk(KERN_DEBUG "Fail while adding lghtIO\n");
		return ret;
	}
	printk(KERN_DEBUG "Added lghtIO to device pool\n");

	if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
	{
		printk(KERN_DEBUG "Fail while create class for lghtIO\n");
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(cl);
	}
	printk(KERN_DEBUG "Created class for lghtIO\n");
	if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "lghtIO")))
	{
		class_destroy(cl);
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(dev_ret);
	}
	printk(KERN_INFO "Loaded lghtIO, enjoy\n");

	return 0;
}

static void __exit lghtIO_ioctl_exit(void)
{
	device_destroy(cl, dev);
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
	printk(KERN_INFO "Unloaded lghtIO, bye bye\n");
}

module_init(lghtIO_ioctl_init);
module_exit(lghtIO_ioctl_exit);

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Oleksandr Hubanov <alex@0x0h.com>");
MODULE_DESCRIPTION("Traffic Light Driver");
