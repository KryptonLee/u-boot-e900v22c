/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2019-2021 Toradex
 */

#ifndef __APALIS_IMX8_H
#define __APALIS_IMX8_H

#include <asm/arch/imx-regs.h>
#include <linux/sizes.h>

#define CONFIG_SYS_FSL_ESDHC_ADDR	0
#define USDHC1_BASE_ADDR		0x5b010000
#define USDHC2_BASE_ADDR		0x5b020000

/* Networking */
#define CONFIG_IPADDR			192.168.10.2
#define CONFIG_NETMASK			255.255.255.0
#define CONFIG_SERVERIP			192.168.10.1

#define MEM_LAYOUT_ENV_SETTINGS \
	"fdt_addr_r=0x84000000\0" \
	"kernel_addr_r=0x82000000\0" \
	"ramdisk_addr_r=0x94400000\0" \
	"scriptaddr=0x87000000\0"

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 1) \
	func(MMC, mmc, 2) \
	func(MMC, mmc, 0) \
	func(DHCP, dhcp, na)
#include <config_distro_bootcmd.h>
#undef BOOTENV_RUN_NET_USB_START
#define BOOTENV_RUN_NET_USB_START ""

/* Initial environment variables */
#define CONFIG_EXTRA_ENV_SETTINGS \
	BOOTENV \
	MEM_LAYOUT_ENV_SETTINGS \
	"boot_file=Image\0" \
	"console=ttyLP1 earlycon\0" \
	"fdt_addr=0x83000000\0"	\
	"fdt_file=fsl-imx8qm-apalis-eval.dtb\0" \
	"fdtfile=fsl-imx8qm-apalis-eval.dtb\0" \
	"finduuid=part uuid mmc ${mmcdev}:2 uuid\0" \
	"initrd_addr=0x83800000\0" \
	"initrd_high=0xffffffffffffffff\0" \
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
		"root=PARTUUID=${uuid} rootwait " \
	"mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0" \
	"mmcpart=1\0" \
	"netargs=setenv bootargs console=${console},${baudrate} " \
		"root=/dev/nfs ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp" \
		"\0" \
	"nfsboot=run netargs; dhcp ${loadaddr} ${boot_file}; tftp ${fdt_addr} " \
		"apalis-imx8/${fdt_file}; booti ${loadaddr} - ${fdt_addr}\0" \
	"panel=NULL\0" \
	"script=boot.scr\0" \
	"update_uboot=askenv confirm Did you load u-boot-dtb.imx (y/N)?; " \
		"if test \"$confirm\" = \"y\"; then " \
		"setexpr blkcnt ${filesize} + 0x1ff && setexpr blkcnt " \
		"${blkcnt} / 0x200; mmc dev 0 1; mmc write ${loadaddr} 0x0 " \
		"${blkcnt}; fi\0"

/* Link Definitions */

#define CONFIG_SYS_INIT_SP_ADDR		0x80200000

/* On Apalis iMX8 USDHC1 is eMMC, USDHC2 is 8-bit and USDHC3 is 4-bit MMC/SD */
#define CONFIG_SYS_FSL_USDHC_NUM	3

#define CONFIG_SYS_BOOTM_LEN		SZ_64M /* Increase max gunzip size */

#define CONFIG_SYS_SDRAM_BASE		0x80000000
#define PHYS_SDRAM_1			0x80000000
#define PHYS_SDRAM_2			0x880000000
#define PHYS_SDRAM_1_SIZE		SZ_2G		/* 2 GB */
#define PHYS_SDRAM_2_SIZE		SZ_2G		/* 2 GB */

/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE		SZ_2K
#define CONFIG_SYS_MAXARGS		64
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)

#endif /* __APALIS_IMX8_H */
