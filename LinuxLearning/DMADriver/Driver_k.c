/*
    Reference : http://derekmolloy.ie/writing-a-linux-kernel-module-part-2-a-character-device/
*/
#include "Driver_k.h"

//MODULE_LICENSE("Dual BSD/GPL");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vignesh S");
MODULE_DESCRIPTION("Simple DMA Driver");

#define DEVICE_NAME         "SimpleDMA"
#define DEVICE_CLASS        "Simple"

static DEFINE_MUTEX(char_mutex);


static int    majorNumber;                  ///< Stores the device number -- determined automatically
static char*   message = NULL;           ///< Memory for the string that is passed from userspace
static short  size_of_message;              ///< Used to remember the size of the string stored
static int    numberOpens = 0;              ///< Counts the number of times the device is opened
static struct class*  charClass  = NULL; ///< The device-driver class struct pointer
static struct device* charDevice = NULL; ///< The device-driver device struct pointer

// The prototype functions for the character driver -- must come before the struct definition
static int     dev_open(struct inode *, struct file *);
static int     dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

/** @brief Devices are represented as file structure in the kernel. The file_operations structure from
 *  /linux/fs.h lists the callback functions that you wish to associated with your file operations
 *  using a C99 syntax structure. char devices usually implement open, read, write and release calls
 */
static struct file_operations fops =
{
 .open = dev_open,
 .read = dev_read,
 .write = dev_write,
 .release = dev_release,
};

static int CDInit(void)
{
    printk(KERN_INFO "SimpleDMA: Initializing character Driver\n");

    /* dynamically allocate major number */
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if(majorNumber < 0)
    {
        printk(KERN_ALERT "SimpleDMA: Registering character device failed..!\n");
        return majorNumber;
    }
    printk(KERN_INFO "SimpleDMA: registered with major number: %d \n", majorNumber);  

    /* register device class */
    charClass = class_create(THIS_MODULE, DEVICE_CLASS);
    if (IS_ERR(charClass))
    {                
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "SimpleDMA: Failed to register device class\n");
        // Correct way to return an error on a pointer
        return PTR_ERR(charClass);
    }
    printk(KERN_INFO "SimpleDMA: device class registered correctly\n");

   /* Register the device driver */
    charDevice = device_create(charClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(charDevice))
    {               
        // Clean up if there is an error
        class_destroy(charClass);           // Repeated code but the alternative is goto statements
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "SimpleDMA: Failed to create the device\n");
        return PTR_ERR(charDevice);
    }
    printk(KERN_INFO "SimpleDMA: device class created correctly\n"); // Made it! device was initialized

    /* allocate memory for message buffer */
    message = (char *)kmalloc(256, GFP_KERNEL);
    if(message == NULL)
    {
        printk(KERN_ALERT "SimpleDMA: Failed allocate memory for message buffer\n");   
        return ENOMEM;
    }
    printk(KERN_INFO "SimpleDMA: memory allocated for message buffer successfully\n");
    
    mutex_init(&char_mutex);

    /* init DMA */
    DMA_Init();

   return 0;
}

static void CDExit(void)
{
    device_destroy(charClass, MKDEV(majorNumber, 0));
    class_unregister(charClass);
    class_destroy(charClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    mutex_destroy(&char_mutex);
    printk(KERN_INFO "Simple DMA driver exit success\n");
}

static int dev_open(struct inode *inodep, struct file *filep)
{
    if(!mutex_trylock(&char_mutex))
    {    
        // Try to acquire the mutex (i.e., put the lock on/down)
        // returns 1 if successful and 0 if there is contention
        printk(KERN_ALERT "SimpleDMA: Device in use by another process");
        return -EBUSY;
    }

    numberOpens++;
    printk(KERN_INFO "SimpleDMA: Device has been opened %d time(s)\n", numberOpens);
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
    int error_count = 0;
    // copy_to_user has the format ( * to, *from, size) and returns 0 on success
    error_count = copy_to_user(buffer, message, size_of_message);

    if (error_count == 0)
    {            // if true then have success
        printk(KERN_INFO "SimpleDMA: Sent %d characters to the user\n", size_of_message);
        return (size_of_message = 0);  // clear the position to the start and return 0
    }
    else 
    {
        printk(KERN_INFO "SimpleDMA: Failed to send %d characters to the user\n", error_count);
        return -EFAULT;              // Failed -- return a bad address message (i.e. -14)
    }
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
    unsigned long ulRetVal = 0;
    
    ulRetVal = copy_from_user(message, buffer, len);
    sprintf((message + len), "(%zu letters)", len); 
    size_of_message = strlen(message);                 
    printk(KERN_INFO "SimpleDMA: Received %zu characters from the user\n", len);
    return len;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
    if(message != NULL)
    {
        kfree(message);
    }
    mutex_unlock(&char_mutex);
    printk(KERN_INFO "SimpleDMA: Device successfully closed\n");
    return 0;
}

module_init(CDInit);
module_exit(CDExit);
