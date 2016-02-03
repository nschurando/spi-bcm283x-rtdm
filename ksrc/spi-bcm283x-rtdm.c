/* Self header */
#include "../include/spi-bcm283x-rtdm.h"

/* Linux headers */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/init.h>

/* RTDM headers */
#include <rtdm/rtdm.h>
#include <rtdm/driver.h>

/*
 * Register module values
 */
MODULE_VERSION("0.1");
MODULE_DESCRIPTION("Real-Time SPI driver for the Broadcom BCM283x SoC familly using the RTDM API");
MODULE_AUTHOR("Nicolas Schurando <schurann@ext.essilor.com>");
MODULE_LICENSE("GPL v2");
