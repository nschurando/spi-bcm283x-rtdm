# spi-bcm283x-rtdm

Real-Time SPI driver for the Broadcom BCM2835 (BCM2708) and BCM2836 (BCM2709) SoCs using the RTDM API.

## Introduction

This RTDM driver is intended to provide SPI communication between a Raspberry Pi running Xenomai 3.0 (or greater, potentially) and a maximum of two slave devices.

## Limitations

The driver currently only supports blocking data transfer.

Possible future improvements would be implementing interrupt-based and dma-based transfer.

## Build

The provided makefile will build the module out-of-tree.
If you are unfamiliar with this technique, you can read the related documentation at https://www.kernel.org/doc/Documentation/kbuild/modules.txt.
This requires that you provide, as an argument, the location of the sources of an already built Xenomai-enabled kernel.

Start by retrieving the source of the driver.
```bash
$ git clone https://github.com/nicolas-schurando/spi-bcm283x-rtdm.git
```

Then build against your already built kernel source.
```bash
$ make ARCH=arm CROSS_COMPILER=/path-to-gcc/prefix- KERNEL_DIR=/path-to-kernel-sources
```

Upon success, the release sub-folder will be populated with the generated kernel module.

## Usage

Copy the generated kernel module onto the target and load it with the following command.
```bash
$ sudo insmod spi-bcm283x-rtdm.ko
```

The system log should display something like:
```
[   59.577534] bcm283x_spi_rtdm_init: Starting driver ...
[   59.577582] bcm2835_init: Found device-tree node /soc.
[   59.577615] bcm2835_init: /soc/ranges = 0x7e000000 0x3f000000 0x01000000.
[   59.577638] bcm2835_init: Using device-tree values.
[   59.577998] mapmem: mapping 0x3f000000 for gpio succeded to 0xbe000000
[   59.578867] bcm283x_spi_rtdm_init: Device spidev0.0 registered without errors.
[   59.579362] bcm283x_spi_rtdm_init: Device spidev0.1 registered without errors.
```

Once loaded, the driver will expose the two devices listed below.
The number before the dot refers to the SPI interface and the number after the dot corresponds to the chip select pin.
The Raspberry Pi only exposes the SPI0 interface, with CS0 and CS1.
 * `/dev/rtdm/spidev0.0`
 * `/dev/rtdm/spidev0.1`

The driver uses hard-coded values for the Pi 1, but needs to fetch information from the device tree if running on a Pi 2.
For the latter, make sure that you compiled the kernel with device-tree enabled, and that you used the `mkknlimg` tool to add the DT-compatibility trailer.

Finally, below are a few relevant lines that should help you make use of the driver inside a Xenomai application.
```c
/* RTDM header */
#include <rtdm/rtdm.h>

/* BCM283x SPI RTDM driver header */
#include "spi-bcm283x-rtdm.h"

/** Transmit buffer */
static uint8_t tx_buffer[BCM283X_SPI_BUFFER_SIZE_MAX];

/** Receive buffer */
static uint8_t rx_buffer[BCM283X_SPI_BUFFER_SIZE_MAX];

/** Handle to the bcm283x rtdm spi driver instance. */
static int device_handle = -1;

/**
 * Open and configure device
 * @return 0 in case of success, a negative value otherwise.
 */
int open_device() {

	int res;
	int value;

	/* Open device */
	res = open("/dev/rtdm/spidev0.0", O_RDWR);
	if (res < 0) {
		printf("%s: Could not open spi device, open has failed with %d (%s).", __FUNCTION__, errno, strerror(errno));
		return;
	} else {
		printf("%s: Device opened.", __FUNCTION__);
		device_handle = res;
	}

	/* Configure device */
	value = BCM283X_SPI_BIT_ORDER_MSBFIRST;
	res = ioctl(device_handle, BCM283X_SPI_SET_BIT_ORDER, &value);
	if (res < 0) {
		printf("%s: Could not configure bit order, ioctl has failed with %d (%s).", __FUNCTION__, errno, strerror(errno));
		device_handle = NULL;
		return -1;
	}
	value = BCM283X_SPI_DATA_MODE_0;
	res = ioctl(device_handle, BCM283X_SPI_SET_DATA_MODE, &value);
	if (res < 0) {
		printf("%s: Could not configure data mode, ioctl has failed with %d (%s).", __FUNCTION__, errno, strerror(errno));
		device_handle = NULL;
		return -1;
	}
	value = BCM283X_SPI_SPEED_8MHz;
	res = ioctl(device_handle, BCM283X_SPI_SET_SPEED, &value);
	if (res < 0) {
		printf("%s: Could not configure bus speed, ioctl has failed with %d (%s).", __FUNCTION__, errno, strerror(errno));
		device_handle = NULL;
		return -1;
	}
	value = BCM283X_SPI_CS_POL_LOW;
	res = ioctl(device_handle, BCM283X_SPI_SET_CS_POLARITY, &value);
	if (res < 0) {
		printf("%s: Could not configure chip select polarity, ioctl has failed with %d (%s).", __FUNCTION__, errno, strerror(errno));
		device_handle = NULL;
		return -1;
	}

	printf("%s: Device sucessfully configured.", __FUNCTION__);
	return 0;

}

int main() {

	int res;

	/* Open device */
	res = open_device();
	if (res < 0) {
		printf("%s: Could not open device, exiting.", __FUNCTION__);
		return -1;
	}

	/* Do stuff */
	while (...) {
		ssize_t size;

		/* Write from tx buffer */
		size = write(device_handle, (const void *) tx_buffer, spi_frame_size);

		/* Receive to rx buffer */
		memset(rx_buffer, 0, 1024);
		size = read(device_handle, (void *) rx_buffer, spi_frame_size);

		/* ... */
	}

}
```

## Credits

This code should be considered as a wrapper around the great user-space bcm2835 library written by Mike McCauley and available at http://www.airspayce.com/mikem/bcm2835/.

His code underwent only minor modifications, in order to make it compatible with kernel-space.

Both the original work and this driver are licensed under the GNU General Public License version 2 (GPLv2).

Comments, issues, and contributions are welcome.

Author Nicolas Schurando (schurann@ext.essilor.com).