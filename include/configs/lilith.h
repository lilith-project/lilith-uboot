/*
 * (C) Copyright 2007-2008
 * Stelian Pop <stelian.pop@leadtechdesign.com>
 * Lead Tech Design <www.leadtechdesign.com>
 *
 * Configuation settings for the AT91SAM9260EK & AT91SAM9G20EK boards.
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_AT91_LEGACY

/* ARM asynchronous clock */
#define CONFIG_SYS_AT91_MAIN_CLOCK	18432000	/* 18.432 MHz crystal */
#define CONFIG_SYS_HZ		1000

#define CONFIG_ARM926EJS	1	/* This is an ARM926EJS Core	*/

#ifdef CONFIG_AT91SAM9G20EK
#define CONFIG_AT91SAM9G20	1	/* It's an Atmel AT91SAM9G20 SoC*/
#else
#define CONFIG_AT91SAM9260	1	/* It's an Atmel AT91SAM9260 SoC*/
#endif

#define CONFIG_ARCH_CPU_INIT
#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff	*/

#define CONFIG_CMDLINE_TAG	1	/* enable passing of ATAGs	*/
#define CONFIG_SETUP_MEMORY_TAGS 1
#define CONFIG_INITRD_TAG	1

/*#define CONFIG_SKIP_LOWLEVEL_INIT*/
#define CONFIG_SKIP_RELOCATE_UBOOT

/*
 * Hardware drivers
 */
#define CONFIG_AT91_GPIO	1
#define CONFIG_ATMEL_USART	1
#undef CONFIG_USART0
#undef CONFIG_USART1
#undef CONFIG_USART2
#define CONFIG_USART3		1	/* USART 3 is DBGU */

/* LED */
#define CONFIG_AT91_LED
#define	CONFIG_RED_LED		AT91_PIN_PA9	/* this is the power led */
#define	CONFIG_GREEN_LED	AT91_PIN_PA6	/* this is the user led */

#define CONFIG_BOOTDELAY	1


/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#undef CONFIG_CMD_BDI
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_IMI
#undef CONFIG_CMD_IMLS
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_SOURCE

#undef CONFIG_CMD_NET
#undef CONFIG_CMD_NFS
#undef CONFIG_CMD_PING
#undef CONFIG_CMD_DHCP
#undef CONFIG_CMD_NAND
#undef CONFIG_CMD_USB

/* SDRAM */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			0x20000000
#define PHYS_SDRAM_SIZE			0x04000000	/* 64 megs */

/* SD/MMC card */
#define CONFIG_MMC			1
#define CONFIG_GENERIC_MMC		1
#define CONFIG_GENERIC_ATMEL_MCI	1
#define CONFIG_ATMEL_MCI_PORTB		1	/* L9260 uses port B */
#define CONFIG_SYS_MMC_CD_PIN		AT91_PIN_PC8
#define CONFIG_CMD_MMC			1

#define CONFIG_CMD_FAT			1
#define CONFIG_CMD_EXT2			1


/* DataFlash */
#define CONFIG_ATMEL_DATAFLASH_SPI
#define CONFIG_HAS_DATAFLASH		1
#define CONFIG_SYS_SPI_WRITE_TOUT		(5*CONFIG_SYS_HZ)
#define CONFIG_SYS_MAX_DATAFLASH_BANKS		2
#define CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS0	0xC0000000	/* CS0 */
#define CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS1	0xD0000000	/* CS1 */
#define AT91_SPI_CLK			15000000

#ifdef CONFIG_AT91SAM9G20EK
#define DATAFLASH_TCSS			(0x22 << 16)
#else
#define DATAFLASH_TCSS			(0x1a << 16)
#endif
#define DATAFLASH_TCHS			(0x1 << 24)

/* NAND flash */
#ifdef CONFIG_CMD_NAND
#define CONFIG_NAND_ATMEL
#define CONFIG_SYS_MAX_NAND_DEVICE		1
#define CONFIG_SYS_NAND_BASE			0x40000000
#define CONFIG_SYS_NAND_DBW_8			1
/* our ALE is AD21 */
#define CONFIG_SYS_NAND_MASK_ALE		(1 << 21)
/* our CLE is AD22 */
#define CONFIG_SYS_NAND_MASK_CLE		(1 << 22)
#define CONFIG_SYS_NAND_ENABLE_PIN		AT91_PIN_PC14
#define CONFIG_SYS_NAND_READY_PIN		AT91_PIN_PC13
#endif

/* NOR flash - no real flash on this board */
#define CONFIG_SYS_NO_FLASH			1

/* Ethernet */
#undef CONFIG_MACB
#undef CONFIG_RMII
#undef CONFIG_NET_MULTI
#undef CONFIG_NET_RETRY_COUNT
#undef CONFIG_RESET_PHY_R

/* USB */
#undef CONFIG_USB_ATMEL
#undef CONFIG_USB_OHCI_NEW
#define CONFIG_DOS_PARTITION		1
#undef CONFIG_SYS_USB_OHCI_CPU_INIT
#undef CONFIG_SYS_USB_OHCI_REGS_BASE
#undef CONFIG_SYS_USB_OHCI_SLOT_NAME
#undef CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS
#undef CONFIG_USB_STORAGE


#define CONFIG_SYS_LOAD_ADDR			0x22000000	/* load address */

#define CONFIG_SYS_MEMTEST_START		PHYS_SDRAM
#define CONFIG_SYS_MEMTEST_END			0x23e00000

/* bootstrap + u-boot + env + linux in dataflash on CS1 */
#define CONFIG_ENV_IS_IN_DATAFLASH	1
#define CONFIG_SYS_MONITOR_BASE	(CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS1 + 0x8400)
#define CONFIG_ENV_OFFSET		0x4200
#define CONFIG_ENV_ADDR		(CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS1 + CONFIG_ENV_OFFSET)
#define CONFIG_ENV_SIZE		0x4200
#define CONFIG_BOOTCOMMAND	"mmcinfo; ext2load mmc 0 0x22200000 uImage; bootm 0x22200000"
#define CONFIG_BOOTARGS		"console=ttyS0,115200 "			\
				"root=/dev/mmcblk0p1 rw "		\
				"rootwait lpj=44748"

#define CONFIG_BAUDRATE		115200
#define CONFIG_SYS_BAUDRATE_TABLE	{115200 , 19200, 38400, 57600, 9600 }

#define CONFIG_SYS_PROMPT		"U-Boot> "
#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#undef CONFIG_SYS_LONGHELP
#undef CONFIG_CMDLINE_EDITING


/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		ROUND(3 * CONFIG_ENV_SIZE + 128*1024, 0x1000)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* 128 bytes for initial data */

#define CONFIG_STACKSIZE		(32*1024)	/* regular stack */

#ifdef CONFIG_USE_IRQ
#error CONFIG_USE_IRQ not supported
#endif












/*
 *   Shameless copy-paste from 9263ek, need checking
 */


#define MASTER_PLL_MUL		171
#define MASTER_PLL_DIV		14
#define MASTER_PLL_OUT		3

/* clocks */
#define CONFIG_SYS_MOR_VAL						\
		(AT91_PMC_MOR_MOSCEN | AT91_PMC_MOR_OSCOUNT(255))
#define CONFIG_SYS_PLLAR_VAL					\
	(AT91_PMC_PLLAR_29 |					\
	AT91_PMC_PLLXR_OUT(MASTER_PLL_OUT) |			\
	AT91_PMC_PLLXR_PLLCOUNT(63) |				\
	AT91_PMC_PLLXR_MUL(MASTER_PLL_MUL - 1) | 		\
	AT91_PMC_PLLXR_DIV(MASTER_PLL_DIV))

/* PCK/2 = MCK Master Clock from PLLA */
#define	CONFIG_SYS_MCKR1_VAL		\
	(AT91_PMC_MCKR_CSS_SLOW | AT91_PMC_MCKR_PRES_1 |	\
	 AT91_PMC_MCKR_MDIV_2)

/* PCK/2 = MCK Master Clock from PLLA */
#define	CONFIG_SYS_MCKR2_VAL		\
	(AT91_PMC_MCKR_CSS_PLLA | AT91_PMC_MCKR_PRES_1 | 	\
	AT91_PMC_MCKR_MDIV_2)

/* define PDC[31:16] as DATA[31:16] */
#define CONFIG_SYS_PIOD_PDR_VAL1	0xFFFF0000
/* no pull-up for D[31:16] */
#define CONFIG_SYS_PIOD_PPUDR_VAL	0xFFFF0000
/* EBI0_CSA, CS1 SDRAM, CS3 NAND Flash, 3.3V memories */
#define CONFIG_SYS_MATRIX_EBICSA_VAL					\
	(AT91_MATRIX_CSA_DBPUC | AT91_MATRIX_CSA_VDDIOMSEL_3_3V |	\
	 AT91_MATRIX_CSA_EBI_CS1A)

/* SDRAM */
/* SDRAMC_MR Mode register */
#define CONFIG_SYS_SDRC_MR_VAL1		0
/* SDRAMC_TR - Refresh Timer register */
#define CONFIG_SYS_SDRC_TR_VAL1		0x13C
/* SDRAMC_CR - Configuration register*/
#define CONFIG_SYS_SDRC_CR_VAL							\
		(AT91_SDRAMC_NC_9 |						\
		 AT91_SDRAMC_NR_13 |						\
		 AT91_SDRAMC_NB_4 |						\
		 AT91_SDRAMC_CAS_3 |						\
		 AT91_SDRAMC_DBW_16 |						\
		 (1 <<  8) |		/* Write Recovery Delay */		\
		 (7 << 12) |		/* Row Cycle Delay */			\
		 (2 << 16) |		/* Row Precharge Delay */		\
		 (2 << 20) |		/* Row to Column Delay */		\
		 (5 << 24) |		/* Active to Precharge Delay */		\
		 (1 << 28))		/* Exit Self Refresh to Active Delay */

/* Memory Device Register -> SDRAM */
#define CONFIG_SYS_SDRC_MDR_VAL		AT91_SDRAMC_MD_SDRAM
#define CONFIG_SYS_SDRC_MR_VAL2		AT91_SDRAMC_MODE_PRECHARGE
#define CONFIG_SYS_SDRAM_VAL1		0		/* SDRAM_BASE */
#define CONFIG_SYS_SDRC_MR_VAL3		AT91_SDRAMC_MODE_REFRESH
#define CONFIG_SYS_SDRAM_VAL2		0		/* SDRAM_BASE */
#define CONFIG_SYS_SDRAM_VAL3		0		/* SDRAM_BASE */
#define CONFIG_SYS_SDRAM_VAL4		0		/* SDRAM_BASE */
#define CONFIG_SYS_SDRAM_VAL5		0		/* SDRAM_BASE */
#define CONFIG_SYS_SDRAM_VAL6		0		/* SDRAM_BASE */
#define CONFIG_SYS_SDRAM_VAL7		0		/* SDRAM_BASE */
#define CONFIG_SYS_SDRAM_VAL8		0		/* SDRAM_BASE */
#define CONFIG_SYS_SDRAM_VAL9		0		/* SDRAM_BASE */
#define CONFIG_SYS_SDRC_MR_VAL4		AT91_SDRAMC_MODE_LMR
#define CONFIG_SYS_SDRAM_VAL10		0		/* SDRAM_BASE */
#define CONFIG_SYS_SDRC_MR_VAL5		AT91_SDRAMC_MODE_NORMAL
#define CONFIG_SYS_SDRAM_VAL11		0		/* SDRAM_BASE */
#define CONFIG_SYS_SDRC_TR_VAL2		1200		/* SDRAM_TR */
#define CONFIG_SYS_SDRAM_VAL12		0		/* SDRAM_BASE */

/* setup SMC0, CS0 (NOR Flash) - 16-bit, 15 WS */
#define CONFIG_SYS_SMC0_SETUP0_VAL				\
	(AT91_SMC_SETUP_NWE(10) | AT91_SMC_SETUP_NCS_WR(10) |	\
	 AT91_SMC_SETUP_NRD(10) | AT91_SMC_SETUP_NCS_RD(10))
#define CONFIG_SYS_SMC0_PULSE0_VAL				\
	(AT91_SMC_PULSE_NWE(11) | AT91_SMC_PULSE_NCS_WR(11) |	\
	 AT91_SMC_PULSE_NRD(11) | AT91_SMC_PULSE_NCS_RD(11))
#define CONFIG_SYS_SMC0_CYCLE0_VAL	\
	(AT91_SMC_CYCLE_NWE(22) | AT91_SMC_CYCLE_NRD(22))
#define CONFIG_SYS_SMC0_MODE0_VAL				\
	(AT91_SMC_MODE_RM_NRD | AT91_SMC_MODE_WM_NWE |		\
	 AT91_SMC_MODE_DBW_16 |					\
	 AT91_SMC_MODE_TDF | AT91_SMC_MODE_TDF_CYCLE(6))

/* user reset enable */
#define CONFIG_SYS_RSTC_RMR_VAL			\
		(AT91_RSTC_KEY |		\
		AT91_RSTC_MR_URSTEN |		\
		AT91_RSTC_MR_ERSTL(15))

/* Disable Watchdog */
#define CONFIG_SYS_WDTC_WDMR_VAL				\
		(AT91_WDT_MR_WDIDLEHLT | AT91_WDT_MR_WDDBGHLT |	\
		 AT91_WDT_MR_WDV(0xfff) |			\
		 AT91_WDT_MR_WDDIS |				\
		 AT91_WDT_MR_WDD(0xfff))





/* we don't define any special values for pdc,
this is used for 32bits ram configuration */
#define CONFIG_SYS_PIOC_PDR_VAL1	0x00000000
/* no pull-up for D[31:16] */
#define CONFIG_SYS_PIOC_PPUDR_VAL	0x00000000






#endif
