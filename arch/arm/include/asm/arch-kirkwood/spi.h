/*
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 *
 * Derived from drivers/spi/mpc8xxx_spi.c
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __KW_SPI_H__
#define __KW_SPI_H__

/* They are used to define CONFIG_SYS_KW_SPI_MPP
 * each of the below #defines selects which mpp is
 * configured for each SPI signal in spi_claim_bus
 * bit 0: selects pin for MOSI (MPP1 if 0, MPP6 if 1)
 * bit 1: selects pin for SCK (MPP2 if 0, MPP10 if 1)
 * bit 2: selects pin for MISO (MPP3 if 0, MPP11 if 1)
 */
#define MOSI_MPP6	(1 << 0)
#define SCK_MPP10	(1 << 1)
#define MISO_MPP11	(1 << 2)

#endif /* __KW_SPI_H__ */
