/**
 * Copyright (C) 2016 Nicolas Schurando <schurann@ext.essilor.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef BCM283X_SPI_RTDM_H
#define BCM283X_SPI_RTDM_H

/**
 * Maximum size for transmit and receive buffers.
 */
#define BCM283X_SPI_BUFFER_SIZE_MAX 1024

/**
 * IOCTL request for changing the SPI bit order.
 */
#define BCM283X_SPI_SET_BIT_ORDER 0

/**
 * IOCTL request for changing the SPI data mode.
 */
#define BCM283X_SPI_SET_DATA_MODE 1

/**
 * IOCTL request for changing the SPI bus speed.
 */
#define BCM283X_SPI_SET_SPEED 2

/**
 * IOCTL request for changing the SPI chip select polarity.
 */
#define BCM283X_SPI_SET_CS_POLARITY 3

/**
 * List of available speeds for the SPI bus.
 */
typedef enum bcm283x_spi_speed {
	BCM283X_SPI_SPEED_4kHz = 0,
	BCM283X_SPI_SPEED_7kHz = 32768,
	BCM283X_SPI_SPEED_15kHz = 16384,
	BCM283X_SPI_SPEED_30kHz = 8192,
	BCM283X_SPI_SPEED_61kHz = 4096,
	BCM283X_SPI_SPEED_122kHz = 2048,
	BCM283X_SPI_SPEED_244kHz = 1024,
	BCM283X_SPI_SPEED_488kHz = 512,
	BCM283X_SPI_SPEED_976kHz = 256,
	BCM283X_SPI_SPEED_2MHz = 128,
	BCM283X_SPI_SPEED_4MHz = 64,
	BCM283X_SPI_SPEED_8MHz = 32,
	BCM283X_SPI_SPEED_15MHz = 16,
	BCM283X_SPI_SPEED_31MHz = 8,
	BCM283X_SPI_SPEED_62MHz = 4,
	BCM283X_SPI_SPEED_125MHz = 2
} bcm2835_spi_speed_e;

/**
 * SPI chip select polarity.
 */
typedef enum {
	BCM283X_SPI_CS_POL_LOW = 0,
	BCM283X_SPI_CS_POL_HIGH = 1
} bcm283x_spi_cs_polarity_e;

/**
 * SPI data bit ordering.
 */
typedef enum {
	BCM283X_SPI_BIT_ORDER_LSBFIRST = 0,
	BCM283X_SPI_BIT_ORDER_MSBFIRST = 1
} bcm283x_spi_bit_order_e;

/**
 * SPI data mode.
 *  - Mode 0 : CPOL = 0, CPHA = 0
 *  - Mode 1 : CPOL = 0, CPHA = 1
 *  - Mode 2 : CPOL = 1, CPHA = 0
 *  - Mode 3 : CPOL = 1, CPHA = 1
 */
typedef enum {
	BCM283X_SPI_DATA_MODE_0 = 0,
	BCM283X_SPI_DATA_MODE_1 = 1,
	BCM283X_SPI_DATA_MODE_2 = 2,
	BCM283X_SPI_DATA_MODE_3 = 3
} bcm283x_spi_mode_e;

#endif /* BCM283X_SPI_RTDM_H */
