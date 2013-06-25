/*
 * Marvell Dove SoC gpio
 *
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#ifndef __ARCH_DOVE_GPIO_H
#define __ARCH_DOVE_GPIO_H

#include <kw_gpio.h>

#define GPIO_MAX		70
#define GPIO_BASE(pin)		(((pin) >= 64) ? DOVE_GPIO2_BASE : \
				 ((pin) >= 32) ? DOVE_GPIO1_BASE : \
				 DOVE_GPIO0_BASE)

#endif
