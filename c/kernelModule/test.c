#include <linux/init.h>  
#include <linux/kernel.h>  
#include <linux/module.h>  

static int ins_mod(void)  
{  
    printk("module installed\n");  
    return 0;  
}  

static int rm_mod(void)  
{  
    printk("module removed\n");  
    return 0;  
}  
module_init(ins_mod);  
module_exit(rm_mod);  
MODULE_LICENSE("GPL");  
MODULE_AUTHOR("elfy");  


