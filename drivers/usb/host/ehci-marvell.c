/*
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <usb.h>
#include "ehci.h"
#include <asm/arch/cpu.h>

#if defined(CONFIG_DOVE)
#include <asm/arch/dove.h>
#elif defined(CONFIG_KIRKWOOD)
#include <asm/arch/kirkwood.h>
#elif defined(CONFIG_ORION5X)
#include <asm/arch/orion5x.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

#define USB_TARGET_DRAM		0x0

/* USB 2.0 Bridge Address Decoding registers */
struct mvusb_bad_window_regs {
	u32 control;
	u32 base;
	u32 reserved[2];
};

struct mvusb_bridge_regs {
	u32 bridge_control;
	u32 reserved1[3];
	u32 int_cause; /* Bridge Interrupt Cause Register */
	u32 int_mask; /* Bridge Interrupt Mask Register */
	u32 reserved2;
	u32 error_addr; /* Bridge Error Address Register */
	struct mvusb_bad_window_regs window[4];
};

struct mvusb_regs {
	u32 unused1[0x40];
	u32 ehci_regs[0x80];
	struct mvusb_bridge_regs bridge;
};

/*
 * USB 2.0 Bridge Address Decoding registers setup
 */
static void usb_brg_adrdec_setup(struct mvusb_regs *usb_base)
{
	int i;
	u32 size, base, attrib;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {

		/* Enable DRAM bank */
		switch (i) {
		case 0:
			attrib = MVUSB0_CPU_ATTR_DRAM_CS0;
			break;
		case 1:
			attrib = MVUSB0_CPU_ATTR_DRAM_CS1;
			break;
		case 2:
			attrib = MVUSB0_CPU_ATTR_DRAM_CS2;
			break;
		case 3:
			attrib = MVUSB0_CPU_ATTR_DRAM_CS3;
			break;
		default:
			/* invalide bank, disable access */
			attrib = 0;
			break;
		}

		size = gd->bd->bi_dram[i].size;
		base = gd->bd->bi_dram[i].start;
		if (size && attrib)
			writel(MVCPU_WIN_CTRL_DATA(size, USB_TARGET_DRAM,
						   attrib, MVCPU_WIN_ENABLE),
			       usb_base->bridge.window[i].control);
		else
			writel(MVCPU_WIN_DISABLE,
			       usb_base->bridge.window[i].control);

		writel(base, usb_base->bridge.window[i].base);
	}
}

/*
 * Create the appropriate control structures to manage
 * a new EHCI host controller.
 */
int ehci_hcd_init(int index, struct ehci_hccr **hccr, struct ehci_hcor **hcor)
{
#ifdef MVUSB1_BASE
	struct mvusb_regs *usb_base =
		(struct mvusb_regs *)((index == 0) ? MVUSB0_BASE : MVUSB1_BASE);
#else
	struct mvusb_regs *usb_base = (struct mvusb_regs *)MVUSB0_BASE;
#endif

	usb_brg_adrdec_setup(usb_base);
	*hccr = (struct ehci_hccr *)(&usb_base->ehci_regs);
	*hcor = (struct ehci_hcor *)((uint32_t) *hccr
			+ HC_LENGTH(ehci_readl(&(*hccr)->cr_capbase)));

	debug("ehci-marvell: init hccr %x and hcor %x hc_length %d\n",
		(uint32_t)*hccr, (uint32_t)*hcor,
		(uint32_t)HC_LENGTH(ehci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

/*
 * Destroy the appropriate control structures corresponding
 * the the EHCI host controller.
 */
int ehci_hcd_stop(int index)
{
	return 0;
}
