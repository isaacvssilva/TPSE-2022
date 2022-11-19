/*
 * =====================================================================================
 *
 *       Filename:  hello.c
 *
 *    Description:  -
 *
 *        Version:  1.0
 *        Created:  16/11/2022 22:43:06
 *       Revision:  none
 *       Compiler:  arm-linux-gnueabihf-
 *
 *         Author:  Isaac Vinicius, isaacvinicius2121@alu.ufc.br
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include <linux/module.h>
//#error Are we building this file?

static int hello_init(void){
    printk(KERN_ALERT "----> Hello, World Embedded!\n");
    return 0;
}


static void hello_exit(void){
printk(KERN_ALERT "Goodbye\n");
printk(KERN_ALERT " _______ ______   _______ _______  ______   _____\n");
printk(KERN_ALERT "|__   __||  __ | / ____| |  ____| |_ _ _ | |_  __|\n");
printk(KERN_ALERT "  | |   | |__) | |(___   | |__      | |      | |\n");
printk(KERN_ALERT "  | |   |  ___/  |___  | |  __|     | |      | |\n");
printk(KERN_ALERT "  | |   | |      ____) | | |____   _| |_   _ | |_\n");
printk(KERN_ALERT "  |_|   |_|     |_____/  |______| |_____|  |_____|\n\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Isaac Vinicius");
MODULE_DESCRIPTION("Criacao de um novo driver");
MODULE_VERSION("1.0");
