/*
 * arch/asm-arm/mach-kirkwood/include/mach/gpio.h
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ARCH_KIRKWOOD_GPIO_H
#define __ARCH_KIRKWOOD_GPIO_H

#include <kw_gpio.h>

#define GPIO_MAX		50
#define GPIO_BASE(pin)		(((pin) >> 5) ? (KW_GPIO0_BASE + 0x0040) : KW_GPIO0_BASE)

#endif
