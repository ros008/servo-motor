#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/uaccess.h>

#define DEV_NAME "motor_dev"
#define MAJOR_NUM 240

#define PIN_NUM 18

static char msg[10];

MODULE_LICENSE ("GPL");

int motor_open(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "Open motor dev\n");
	

	return 0;
}

ssize_t motor_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
	printk(KERN_ALERT "Read motor dev\n");
	
	
	return 0;
}

ssize_t motor_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset){
	int i;

	printk(KERN_ALERT "Write motor dev\n");
	
	if(copy_from_user(msg, buffer, length) < 0){
		printk(KERN_ERR "Write error\n");
	}
	// printk(KERN_ALERT "msg:%s\n", msg); // behind msg trash..?? error
	
	if(!strncmp(msg, "OPEN", 4)){
		for(i = 0 ; i < 22; i++) {
			gpio_set_value(PIN_NUM, 1); // set output pin_num as high
			udelay(2000);
			gpio_set_value(PIN_NUM, 0); // set output pin_num as low
			udelay(2000);
		}
		
		printk(KERN_ALERT "Door opened");
		
	}
	else if(!strncmp(msg, "CLOSE", 5)){
		for(i = 0 ; i < 45; i++) {
		      	gpio_set_value(PIN_NUM, 1);
			udelay(1000);
			gpio_set_value(PIN_NUM, 0);
			udelay(1000);
		}
	  
		printk(KERN_ALERT "Door closed");
	}
	else{
		printk(KERN_ALERT "Error!");
	}

	
	return length;
}

int motor_close(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "Close motor dev\n");


	return 0;
}

struct file_operations fop={
	.owner = THIS_MODULE,
	.open = motor_open,
	.read = motor_read,
	.write = motor_write,
	.release = motor_close,
};

int __init motor_init(void) {
	printk(KERN_ALERT "Init motor dev\n");
	register_chrdev(MAJOR_NUM, DEV_NAME, &fop);
	return 0;
}

void __exit motor_exit(void) {
	printk(KERN_ALERT "Exit motor dev\n");
	unregister_chrdev(MAJOR_NUM, DEV_NAME);
}

module_init(motor_init);
module_exit(motor_exit);

