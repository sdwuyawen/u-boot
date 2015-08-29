/*
 * (C) Copyright 2003
 * David M眉ller ELSOFT AG Switzerland. d.mueller@elsoft.ch
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/************************************************
 * NAME	    : s3c24x0.h
 * Version  : 31.3.2003
 *
 * common stuff for SAMSUNG S3C24X0 SoC
 ************************************************/

#ifndef __S3C24X0_H__
#define __S3C24X0_H__

/* S3C2416的寄存器定义，by wu */
#define UData(Data)	((unsigned long) (Data))

#define __REG(x)	(*(vu_long *)(x))
#define __REGl(x)	(*(vu_long *)(x))
#define __REGw(x)	(*(vu_short *)(x))
#define __REGb(x)	(*(vu_char *)(x))
#define __REG2(x,y)	(*(vu_long *)((x) + (y)))

/* S3C2416 only supports 512 Byte HW ECC */
#define S3C2410_ECCSIZE		512
#define S3C2410_ECCBYTES	3

/* S3C2416 device base addresses */
#define ELFIN_SSTONE_BASE	0x40000000 /* stepping stone on iROM boot */
#define ELFIN_DMA_BASE		0x4b000000
#define ELFIN_USB_HOST_BASE	0x49000000
#define ELFIN_USB_DEVICE_BASE	0x49800000
#define ELFIN_I2C_BASE		0x54000000
#define ELFIN_I2S_BASE		0x55000000
#define ELFIN_ADC_BASE		0x58000000
#define ELFIN_SPI_BASE		0x59000000

/*
 * Clock and power management
 */
#define ELFIN_CLOCK_POWER_BASE	0x4c000000

/* Clock & Power Controller */
#define LOCKCON0_OFFSET		0x00
#define LOCKCON1_OFFSET		0x04
#define OSCSET_OFFSET		0x08
#define MPLLCON_OFFSET		0x10
#define EPLLCON_OFFSET		0x18
#define CLKSRCCON_OFFSET	0x20
#define CLKDIV0CON_OFFSET	0x24
#define CLKDIV1CON_OFFSET	0x28
#define HCLKCON_OFFSET		0x30
#define PCLKCON_OFFSET		0x34
#define SCLKCON_OFFSET		0x38
#define PWRMODECON_OFFSET	0x40
#define SWRSTCON_OFFSET		0x44
#define BUSPRI0_OFFSET		0x50
#define BUS_MISC_OFFSET		0x58
#define SYSID_OFFSET		0x5c
#define PWRCFG_OFFSET		0x60
#define RSTCON_OFFSET		0x64
#define RSTSTAT_OFFSET		0x68
#define WKUPSTAT_OFFSET		0x6c
#define INFORM0_OFFSET		0x70
#define INFORM1_OFFSET		0x74
#define INFORM2_OFFSET		0x78
#define INFORM3_OFFSET		0x7c
#define USB_PHYCTRL_OFFSET	0x80
#define USB_PHYPWR_OFFSET	0x84
#define USB_RSTCON_OFFSET	0x88
#define USB_CLKCON_OFFSET	0x8c
#define USB_TESTTI_OFFSET	0x90
#define USB_TESTTO_OFFSET	0x94

#define LOCKCON0	(0x4c000000)
#define LOCKCON1	(0x4c000004)
#define OSCSET		(0x4c000008)
#define MPLLCON		(0x4c000010)
#define EPLLCON		(0x4c000018)
#define CLKSRCCON	(0x4c000020)
#define CLKDIV0CON	(0x4c000024)
#define CLKDIV1CON	(0x4c000028)
#define HCLKCON		(0x4c000030)
#define PCLKCON		(0x4c000034)
#define SCLKCON		(0x4c000038)
#define PWRMODECON	(0x4c000040)
#define SWRSTCON	(0x4c000044)
#define BUSPRI0		(0x4c000050)
#define BUS_MISC	(0x4c000058)
#define SYSID		(0x4c00005c)
#define PWRCFG		(0x4c000060)
#define RSTCON		(0x4c000064)
#define RSTSTAT		(0x4c000068)
#define WKUPSTAT	(0x4c00006c)
#define INFORM0		(0x4c000070)
#define INFORM1		(0x4c000074)
#define INFORM2		(0x4c000078)
#define INFORM3		(0x4c00007c)
#define USB_PHYCTRL	(0x4c000080)
#define USB_PHYPWR	(0x4c000084)
#define USB_RSTCON	(0x4c000088)
#define USB_CLKCON	(0x4c00008c)
#define USB_TESTTI	(0x4c000090)
#define USB_TESTTO	(0x4c000094)

#define LOCKCON0_REG		__REG(0x4c000000)
#define LOCKCON1_REG		__REG(0x4c000004)
#define OSCSET_REG		__REG(0x4c000008)
#define MPLLCON_REG		__REG(0x4c000010)
#define EPLLCON_REG		__REG(0x4c000018)
#define CLKSRCCON_REG		__REG(0x4c000020)
#define CLKDIV0CON_REG		__REG(0x4c000024)
#define CLKDIV1CON_REG		__REG(0x4c000028)
#define HCLKCON_REG		__REG(0x4c000030)
#define PCLKCON_REG		__REG(0x4c000034)
#define SCLKCON_REG		__REG(0x4c000038)
#define PWRMODECON_REG		__REG(0x4c000040)
#define SWRSTCON_REG		__REG(0x4c000044)
#define BUSPRI0_REG		__REG(0x4c000050)
#define BUS_MISC_REG		__REG(0x4c000058)
#define SYSID_REG		__REG(0x4c00005c)
#define PWRCFG_REG		__REG(0x4c000060)
#define RSTCON_REG		__REG(0x4c000064)
#define RSTSTAT_REG		__REG(0x4c000068)
#define WKUPSTAT_REG		__REG(0x4c00006c)
#define INFORM0_REG		__REG(0x4c000070)
#define INFORM1_REG		__REG(0x4c000074)
#define INFORM2_REG		__REG(0x4c000078)
#define INFORM3_REG		__REG(0x4c00007c)
#define USB_PHYCTRL_REG		__REG(0x4c000080)
#define USB_PHYPWR_REG		__REG(0x4c000084)
#define USB_RSTCON_REG		__REG(0x4c000088)
#define USB_CLKCON_REG		__REG(0x4c00008c)
#define USB_TESTTI_REG		__REG(0x4c000090)
#define USB_TESTTO_REG		__REG(0x4c000094)


/*
 * Bus Matrix (chap 3)
 */

#define ELFIN_BUS_MAT_BASE	0x4e800000
#define BPRIORITY0		(ELFIN_BUS_MAT_BASE+0x00)
#define BPRIORITY1		(ELFIN_BUS_MAT_BASE+0x04)
#define EBICON			(ELFIN_BUS_MAT_BASE+0x08)



/*
 * GPIO
 */

#define ELFIN_GPIO_BASE		0x56000000

#define GPACON_OFFSET		0x00
#define GPADAT_OFFSET		0x04

#define GPBCON_OFFSET		0x10
#define GPBDAT_OFFSET		0x14
#define GPBPU_OFFSET		0x18

#define GPCCON_OFFSET		0x20
#define GPCDAT_OFFSET		0x24
#define GPCPU_OFFSET		0x28

#define GPDCON_OFFSET		0x30
#define GPDDAT_OFFSET		0x34
#define GPDPU_OFFSET		0x38

#define GPECON_OFFSET		0x40
#define GPEDAT_OFFSET		0x44
#define GPEPU_OFFSET		0x48

#define GPFCON_OFFSET		0x50
#define GPFDAT_OFFSET		0x54
#define GPFPU_OFFSET		0x58

#define GPGCON_OFFSET		0x60
#define GPGDAT_OFFSET		0x64
#define GPGPU_OFFSET		0x68

#define GPHCON_OFFSET		0x70
#define GPHDAT_OFFSET		0x74
#define GPHPU_OFFSET		0x78

#define GPJCON_OFFSET		0xd0
#define GPJDAT_OFFSET		0xd4
#define GPJPU_OFFSET		0xd8

#define GPKCON_OFFSET		0xe0
#define GPKDAT_OFFSET		0xe4
#define GPKPU_OFFSET		0xe8

#define GPLCON_OFFSET		0xf0
#define GPLDAT_OFFSET		0xf4
#define GPLPU_OFFSET		0xf8

#define GPMCON_OFFSET		0x100
#define GPMDAT_OFFSET		0x104
#define GPMPU_OFFSET		0x108

#define MISCCR_OFFSET		0x80
#define DCLKCON_OFFSET		0x84

#define EINTCON0_OFFSET		0x88
#define EINTCON1_OFFSET		0x8c
#define EINTCON2_OFFSET		0x90

#define EINTFLT0_OFFSET		0x94
#define EINTFLT1_OFFSET		0x98
#define EINTFLT2_OFFSET		0x9c
#define EINTFLT3_OFFSET		0xa0

#define EINTMASK_OFFSET		0xa4
#define EINTPEND_OFFSET		0xa8

#define GSTATUS0_OFFSET		0xac
#define GSTATUS1_OFFSET		0xb0
#define GSTATUS3_OFFSET		0xb8
#define GSTATUS4_OFFSET		0xbc

#define DSC0_OFFSET		0xc0
#define DSC1_OFFSET		0xc4
#define DSC2_OFFSET		0xc8

#define MSLCON_OFFSET		0xcc

#define GPACON		(0x56000000)
#define GPADAT		(0x56000004)

#define GPBCON		(0x56000010)
#define GPBDAT		(0x56000014)
#define GPBPU		(0x56000018)

#define GPCCON		(0x56000020)
#define GPCDAT		(0x56000024)
#define GPCPU		(0x56000028)

#define GPDCON		(0x56000030)
#define GPDDAT		(0x56000034)
#define GPDPU		(0x56000038)

#define GPECON		(0x56000040)
#define GPEDAT		(0x56000044)
#define GPEPU		(0x56000048)

#define GPFCON		(0x56000050)
#define GPFDAT		(0x56000054)
#define GPFPU		(0x56000058)

#define GPGCON		(0x56000060)
#define GPGDAT		(0x56000064)
#define GPGPU		(0x56000068)

#define GPHCON		(0x56000070)
#define GPHDAT		(0x56000074)
#define GPHPU		(0x56000078)

#define GPJCON		(0x560000d0)
#define GPJDAT		(0x560000d4)
#define GPJPU		(0x560000d8)

#define GPKCON		(0x560000e0)
#define GPKDAT		(0x560000e4)
#define GPKPU		(0x560000e8)

#define GPLCON		(0x560000f0)
#define GPLDAT		(0x560000f4)
#define GPLPU		(0x560000f8)

#define GPMCON		(0x56000100)
#define GPMDAT		(0x56000104)
#define GPMPU		(0x56000108)

#define MISCCR		(0x56000080)
#define DCLKCON		(0x56000084)

#define EINTCON0	(0x56000088)
#define EINTCON1	(0x5600008c)
#define EINTCON2	(0x56000090)

#define EINTFLT0	(0x56000094)
#define EINTFLT1	(0x56000098)
#define EINTFLT2	(0x5600009c)
#define EINTFLT3	(0x560000a0)

#define EINTMASK	(0x560000a4)
#define EINTPEND	(0x560000a8)

#define GSTATUS0	(0x560000ac)
#define GSTATUS1	(0x560000b0)
#define GSTATUS3	(0x560000b8)
#define GSTATUS4	(0x560000bc)

#define DSC0		(0x560000c0)
#define DSC1		(0x560000c4)
#define DSC2		(0x560000c8)

#define MSLCON		(0x560000cc)

#define GPACON_REG	__REG(0x56000000)
#define GPADAT_REG	__REG(0x56000004)

#define GPBCON_REG	__REG(0x56000010)
#define GPBDAT_REG	__REG(0x56000014)
#define GPBPU_REG	__REG(0x56000018)

#define GPCCON_REG	__REG(0x56000020)
#define GPCDAT_REG	__REG(0x56000024)
#define GPCPU_REG	__REG(0x56000028)

#define GPDCON_REG	__REG(0x56000030)
#define GPDDAT_REG	__REG(0x56000034)
#define GPDPU_REG	__REG(0x56000038)

#define GPECON_REG	__REG(0x56000040)
#define GPEDAT_REG	__REG(0x56000044)
#define GPEPU_REG	__REG(0x56000048)

#define GPFCON_REG	__REG(0x56000050)
#define GPFDAT_REG	__REG(0x56000054)
#define GPFPU_REG	__REG(0x56000058)

#define GPGCON_REG	__REG(0x56000060)
#define GPGDAT_REG	__REG(0x56000064)
#define GPGPU_REG	__REG(0x56000068)

#define GPHCON_REG	__REG(0x56000070)
#define GPHDAT_REG	__REG(0x56000074)
#define GPHPU_REG	__REG(0x56000078)

#define GPJCON_REG	__REG(0x560000d0)
#define GPJDAT_REG	__REG(0x560000d4)
#define GPJPU_REG	__REG(0x560000d8)

#define GPKCON_REG	__REG(0x560000e0)
#define GPKDAT_REG	__REG(0x560000e4)
#define GPKPU_REG	__REG(0x560000e8)

#define GPLCON_REG	__REG(0x560000f0)
#define GPLDAT_REG	__REG(0x560000f4)
#define GPLPU_REG	__REG(0x560000f8)

#define GPMCON_REG	__REG(0x56000100)
#define GPMDAT_REG	__REG(0x56000104)
#define GPMPU_REG	__REG(0x56000108)

#define MISCCR_REG	__REG(0x56000080)
#define DCLKCON_REG	__REG(0x56000084)

#define EINTCON0_REG	__REG(0x56000088)
#define EINTCON1_REG	__REG(0x5600008c)
#define EINTCON2_REG	__REG(0x56000090)

#define EINTFLT0_REG	__REG(0x56000094)
#define EINTFLT1_REG	__REG(0x56000098)
#define EINTFLT2_REG	__REG(0x5600009c)
#define EINTFLT3_REG	__REG(0x560000a0)

#define EINTMASK_REG	__REG(0x560000a4)
#define EINTPEND_REG	__REG(0x560000a8)

#define GSTATUS0_REG	__REG(0x560000ac)
#define GSTATUS1_REG	__REG(0x560000b0)
#define GSTATUS3_REG	__REG(0x560000b8)
#define GSTATUS4_REG	__REG(0x560000bc)

#define DSC0_REG	__REG(0x560000c0)
#define DSC1_REG	__REG(0x560000c4)
#define DSC2_REG	__REG(0x560000c8)

#define MSLCON_REG	__REG(0x560000cc)


/*
 * Memory controller
 */

#define ELFIN_SROM_BASE	0x40c20000

#define SROM_BW_REG	__REG(0x40C20000)
#define SROM_BC0_REG	__REG(0x40C20004)
#define SROM_BC1_REG	__REG(0x40C20008)
#define SROM_BC2_REG	__REG(0x40C2000C)

/*
 * SDRAM Controller
 */

#define ELFIN_MEMCTL_BASE	0x48000000
#define BANKCFG_OFFSET		0x00
#define BANKCON1_OFFSET		0x04
#define BANKCON2_OFFSET		0x08
#define BANKCON3_OFFSET		0x0c
#define REFRESH_OFFSET		0x10
#define TIMEOUT_OFFSET		0x14

#define INIT_NORMAL	0x0
#define INIT_PALL	0x1
#define INIT_MRS	0x2
#define INIT_EMRS	0x3
#define INIT_MASK	0x3


/*
 * Nand flash controller
 */

#define ELFIN_NAND_BASE	0x4e000000

#define NFCONF_OFFSET		0x00
#define NFCONT_OFFSET		0x04
#define NFCMMD_OFFSET		0x08
#define NFADDR_OFFSET		0x0c
#define NFDATA_OFFSET		0x10
#define NFMECCDATA0_OFFSET	0x14
#define NFMECCDATA1_OFFSET	0x18
#define NFSECCDATA0_OFFSET	0x1c
#define NFSBLK_OFFSET		0x20
#define NFEBLK_OFFSET		0x24
#define NFSTAT_OFFSET		0x28
#define NFESTAT0_OFFSET		0x2c
#define NFESTAT1_OFFSET		0x30
#define NFMECC0_OFFSET		0x34
#define NFMECC1_OFFSET		0x38
#define NFSECC_OFFSET		0x3c
#define NFMLCBITPT_OFFSET       0x40
#define NF8ECCERR0_OFFSET	0x44
#define NF8ECCERR1_OFFSET	0x48
#define NF8ECCERR2_OFFSET	0x4c
#define NFM8ECC0_OFFSET		0x50
#define NFM8ECC1_OFFSET		0x54
#define NFM8ECC2_OFFSET		0x58
#define NFM8ECC3_OFFSET		0x5c
#define NFMLC8BITPT0_OFFSET	0x60
#define NFMLC8BITPT1_OFFSET	0x64

#define NFCONF		(0x4e000000)
#define NFCONT		(0x4e000004)
#define NFCMMD		(0x4e000008)
#define NFADDR		(0x4e00000c)
#define NFDATA		(0x4e000010)
#define NFMECCDATA0	(0x4e000014)
#define NFMECCDATA1	(0x4e000018)
#define NFSECCDATA0	(0x4e00001c)
#define NFSBLK		(0x4e000020)
#define NFEBLK		(0x4e000024)
#define NFSTAT		(0x4e000028)
#define NFESTAT0	(0x4e00002c)
#define NFESTAT1	(0x4e000030)
#define NFMECC0		(0x4e000034)
#define NFMECC1		(0x4e000038)
#define NFSECC		(0x4e00003c)
#define NFMLCBITPT	(0x4e000040)
#define NF8ECCERR0		(0x4e000044)
#define NF8ECCERR1		(0x4e000048)
#define NF8ECCERR2		(0x4e00004c)
#define NFM8ECC0		(0x4e000050)
#define NFM8ECC1		(0x4e000054)
#define NFM8ECC2		(0x4e000058)
#define NFM8ECC3		(0x4e00005c)
#define NFMLC8BITPT0		(0x4e000060)
#define NFMLC8BITPT1		(0x4e000064)

#define NFCONF_REG		__REG(0x4e000000)
#define NFCONT_REG		__REG(0x4e000004)
#define NFCMD_REG		__REG(0x4e000008)
#define NFADDR_REG		__REG(0x4e00000c)
#define NFDATA_REG		__REG(0x4e000010)
#define NFDATA8_REG		__REGb(0x4e000010)
#define NFMECCDATA0_REG		__REG(0x4e000014)
#define NFMECCDATA1_REG		__REG(0x4e000018)
#define NFSECCDATA0_REG		__REG(0x4e00001c)
#define NFSBLK_REG		__REG(0x4e000020)
#define NFEBLK_REG		__REG(0x4e000024)
#define NFSTAT_REG		__REG(0x4e000028)
#define NFESTAT0_REG		__REG(0x4e00002c)
#define NFESTAT1_REG		__REG(0x4e000030)
#define NFMECC0_REG		__REG(0x4e000034)
#define NFMECC1_REG		__REG(0x4e000038)
#define NFSECC_REG		__REG(0x4e00003c)
#define NFMLCBITPT_REG		__REG(0x4e000040)

#define NFCONF_ECC_MLC		(1<<24)

#define NFCONF_ECC_1BIT		(0<<23)
#define NFCONF_ECC_4BIT		(2<<23)
#define NFCONF_ECC_8BIT		(1<<23)

#define NFCONT_ECC_ENC		(1<<18)
#define NFCONT_WP		(1<<16)
#define NFCONT_MECCLOCK		(1<<7)
#define NFCONT_SECCLOCK		(1<<6)
#define NFCONT_INITMECC		(1<<5)
#define NFCONT_INITSECC		(1<<4)
#define NFCONT_INITECC		(NFCONT_INITMECC | NFCONT_INITSECC)
#define NFCONT_CS_ALT		(1<<1)
#define NFCONT_CS		(1<<1)
#define NFSTAT_ECCENCDONE	(1<<7)
#define NFSTAT_ECCDECDONE	(1<<6)
#define NFSTAT_RnB		(1<<0)
#define NFESTAT0_ECCBUSY	(1<<31)

/*
 * Interrupt
 */
#define ELFIN_INTERRUPT_BASE	0x4a000000

#define INTMSK_OFFSET		0x08
#define INTSUBMSK_OFFSET	0x1c
#define INTMOD_OFFSET		0x04

#define SRCPND_REG		__REG(0x4a000000)
#define INTMOD_REG		__REG(0x4a000004)
#define INTMSK_REG		__REG(0x4a000008)
#define INTPND_REG		__REG(0x4a000010)
#define INTOFFSET_REG		__REG(0x4a000014)
#define SUBSRCPND_REG		__REG(0x4a000018)
#define INTSUBMSK_REG		__REG(0x4a00001C)
#define SUBSRCPND2_REG		__REG(0x4a000030)
#define INTSUBMSK2_REG		__REG(0x4a000034)
#define PRIORITY_MODE_REG	__REG(0x4a000038)
#define PRIORITY_UPDATE_REG	__REG(0x4a00003c)

/*
 * LCD Controller
 */
#define ELFIN_LCD_BASE	0x4c800000

#define VIDCON0		(0x4c800000)
#define VIDCON1		(0x4c800004)
#define VIDTCON0	(0x4c800008)
#define VIDTCON1	(0x4c80000C)
#define VIDTCON2	(0x4c800010)
#define WINCON0		(0x4c800014)
#define WINCON1		(0x4c800018)
#define VIDOSD0A	(0x4c800028)
#define VIDOSD0B	(0x4c80002C)
#define VIDOSD0C	(0x4c800030)
#define VIDOSD1A	(0x4c800034)
#define VIDOSD1B	(0x4c800038)
#define VIDOSD1C	(0x4c80003C)
#define VIDW00ADD0B0	(0x4c800064)
#define VIDW00ADD0B1	(0x4c800068)
#define VIDW01ADD0	(0x4c80006C)
#define VIDW00ADD1B0	(0x4c80007C)
#define VIDW00ADD1B1	(0x4c800080)
#define VIDW01ADD1	(0x4c800084)
#define VIDW00ADD2B0	(0x4c800094)
#define VIDW00ADD2B1	(0x4c800098)
#define VIDW01ADD2	(0x4c80009C)
#define VIDINTCON	(0x4c8000AC)
#define W1KEYCON0	(0x4c8000B0)
#define W1KEYCON1	(0x4c8000B4)
#define W2KEYCON0	(0x4c8000B8)
#define W2KEYCON1	(0x4c8000BC)
#define W3KEYCON0	(0x4c8000C0)
#define W3KEYCON1	(0x4c8000C4)
#define W4KEYCON0	(0x4c8000C8)
#define W4KEYCON1	(0x4c8000CC)
#define WIN0MAP		(0x4c8000D0)
#define WIN1MAP		(0x4c8000D4)
#define WPALCON		(0x4c8000E4)
#define SYSIFCON0	(0x4c800130)
#define SYSIFCON1	(0x4c800134)
#define DITHMODE1	(0x4c800138)
#define SIFCCON0	(0x4c80013C)
#define SIFCCON1	(0x4c800140)
#define SIFCCON2	(0x4c800144)
#define CPUTRIGCON1	(0x4c80015C)
#define CPUTRIGCON2	(0x4c800160)
#define VIDW00ADD0B1	(0x4c800068)
#define VIDW01ADD0	(0x4c80006C)


/*
 * Watchdog timer
 */
#define ELFIN_WATCHDOG_BASE	0x53000000

#define WTCON_REG		__REG(0x53000000)
#define WTDAT_REG		__REG(0x53000004)
#define WTCNT_REG		__REG(0x53000008)

/*
 * EBI(External Bus Interface)
 */
#define EBIPR_REG		__REG(0x48800000)
#define BANK_CFG_REG		__REG(0x48800004)

/*
 * SSMC
 */
#define SMBIDCYR0_REG	__REG(0x4F000000)
#define SMBIDCYR1_REG	__REG(0x4F000020)
#define SMBIDCYR2_REG	__REG(0x4F000040)
#define SMBIDCYR3_REG	__REG(0x4F000060)
#define SMBIDCYR4_REG	__REG(0x4F000080)
#define SMBIDCYR5_REG	__REG(0x4F0000A0)

#define SMBWSTRDR0_REG	__REG(0x4F000004)
#define SMBWSTRDR1_REG	__REG(0x4F000024)
#define SMBWSTRDR2_REG	__REG(0x4F000044)
#define SMBWSTRDR3_REG	__REG(0x4F000064)
#define SMBWSTRDR4_REG	__REG(0x4F000084)
#define SMBWSTRDR5_REG	__REG(0x4F0000A4)

#define SMBWSTWRR0_REG	__REG(0x4F000008)
#define SMBWSTWRR1_REG	__REG(0x4F000028)
#define SMBWSTWRR2_REG	__REG(0x4F000048)
#define SMBWSTWRR3_REG	__REG(0x4F000068)
#define SMBWSTWRR4_REG	__REG(0x4F000088)
#define SMBWSTWRR5_REG	__REG(0x4F0000A8)

#define SMBWSTOENR0_REG __REG(0x4F00000C)
#define SMBWSTOENR1_REG __REG(0x4F00002C)
#define SMBWSTOENR2_REG __REG(0x4F00004C)
#define SMBWSTOENR3_REG __REG(0x4F00006C)
#define SMBWSTOENR4_REG __REG(0x4F00008C)
#define SMBWSTOENR5_REG __REG(0x4F0000AC)

#define SMBWSTWENR0_REG	__REG(0x4F000010)
#define SMBWSTWENR1_REG	__REG(0x4F000030)
#define SMBWSTWENR2_REG	__REG(0x4F000050)
#define SMBWSTWENR3_REG __REG(0x4F000070)
#define SMBWSTWENR4_REG __REG(0x4F000090)
#define SMBWSTWENR5_REG __REG(0x4F0000B0)

#define SMBCR0_REG	__REG(0x4F000014)
#define SMBCR1_REG	__REG(0x4F000034)
#define SMBCR2_REG	__REG(0x4F000054)
#define SMBCR3_REG	__REG(0x4F000074)
#define SMBCR4_REG	__REG(0x4F000094)
#define SMBCR5_REG	__REG(0x4F0000B4)

#define SMBSR0_REG	__REG(0x4F000018)
#define SMBSR1_REG	__REG(0x4F000038)
#define SMBSR2_REG	__REG(0x4F000058)
#define SMBSR3_REG	__REG(0x4F000078)
#define SMBSR4_REG	__REG(0x4F000098)
#define SMBSR5_REG	__REG(0x4F0000B8)

#define SMBWSTBDR0_REG	__REG(0x4F00001C)
#define SMBWSTBDR1_REG	__REG(0x4F00003C)
#define SMBWSTBDR2_REG	__REG(0x4F00005C)
#define SMBWSTBDR3_REG	__REG(0x4F00007C)
#define SMBWSTBDR4_REG	__REG(0x4F00009C)
#define SMBWSTBDR5_REG	__REG(0x4F0000BC)

#define SSMCSR_REG	__REG(0x4F000200)
#define SSMCCR_REG	__REG(0x4F000204)

/*
 * UART
 */
#define ELFIN_UART_BASE	0x50000000

#define ULCON0_REG		__REG(0x50000000)
#define UCON0_REG		__REG(0x50000004)
#define UFCON0_REG		__REG(0x50000008)
#define UMCON0_REG		__REG(0x5000000C)
#define UTRSTAT0_REG		__REG(0x50000010)
#define UERSTAT0_REG		__REG(0x50000014)
#define UFSTAT0_REG		__REG(0x50000018)
#define UMSTAT0_REG		__REG(0x5000001C)
#define UTXH0_REG		__REG(0x50000020)
#define URXH0_REG		__REG(0x50000024)
#define UBRDIV0_REG		__REG(0x50000028)

#define ULCON1_REG		__REG(0x50004000)
#define UCON1_REG		__REG(0x50004004)
#define UFCON1_REG		__REG(0x50004008)
#define UMCON1_REG		__REG(0x5000400C)
#define UTRSTAT1_REG		__REG(0x50004010)
#define UERSTAT1_REG		__REG(0x50004014)
#define UFSTAT1_REG		__REG(0x50004018)
#define UMSTAT1_REG		__REG(0x5000401C)
#define UTXH1_REG		__REG(0x50004020)
#define URXH1_REG		__REG(0x50004024)
#define UBRDIV1_REG		__REG(0x50004028)

#define ULCON2_REG		__REG(0x50008000)
#define UCON2_REG		__REG(0x50008004)
#define UFCON2_REG		__REG(0x50008008)
#define UMCON2_REG		__REG(0x5000800C)
#define UTRSTAT2_REG		__REG(0x50008010)
#define UERSTAT2_REG		__REG(0x50008014)
#define UFSTAT2_REG		__REG(0x50008018)
#define UMSTAT2_REG		__REG(0x5000801C)
#define UTXH2_REG		__REG(0x50008020)
#define URXH2_REG		__REG(0x50008024)
#define UBRDIV2_REG		__REG(0x50008028)

#define ULCON_OFFSET		0x00
#define UCON_OFFSET		0x04
#define UFCON_OFFSET		0x08
#define UMCON_OFFSET		0x0C
#define UTRSTAT_OFFSET		0x10
#define UERSTAT_OFFSET		0x14
#define UFSTAT_OFFSET		0x18
#define UMSTAT_OFFSET		0x1C
#define UTXH_OFFSET		0x20
#define URXH_OFFSET		0x24
#define UBRDIV_OFFSET		0x28
#define UDIVSLOT_OFFSET		0x2c


#define UTRSTAT_TX_EMPTY	(1 << 2)
#define UTRSTAT_RX_READY	(1 << 0)
#define UART_ERR_MASK		0xF

/*
 * PWM timer
 */
#define ELFIN_TIMER_BASE	0x51000000

#define TCFG0_REG		__REG(0x51000000)
#define TCFG1_REG		__REG(0x51000004)
#define TCON_REG		__REG(0x51000008)
#define TCNTB0_REG		__REG(0x5100000C)
#define TCMPB0_REG		__REG(0x51000010)
#define TCNTO0_REG		__REG(0x51000014)
#define TCNTB1_REG		__REG(0x51000018)
#define TCMPB1_REG		__REG(0x5100001C)
#define TCNTO1_REG		__REG(0x51000020)
#define TCNTB2_REG		__REG(0x51000024)
#define TCMPB2_REG		__REG(0x51000028)
#define TCNTO2_REG		__REG(0x5100002C)
#define TCNTB3_REG		__REG(0x51000030)
#define TCMPB3_REG		__REG(0x51000034)
#define TCNTO3_REG		__REG(0x51000038)
#define TCNTB4_REG		__REG(0x5100003C)
#define TCNTO4_REG		__REG(0x51000040)

/* Fields */
#define fTCFG0_DZONE		Fld(8,16)       /* the dead zone length (= timer 0) */
#define fTCFG0_PRE1		Fld(8,8)        /* prescaler value for time 2,3,4 */
#define fTCFG0_PRE0		Fld(8,0)        /* prescaler value for time 0,1 */
#define fTCFG1_MUX4		Fld(4,16)
/* bits */
#define TCFG0_DZONE(x)		FInsrt((x), fTCFG0_DZONE)
#define TCFG0_PRE1(x)		FInsrt((x), fTCFG0_PRE1)
#define TCFG0_PRE0(x)		FInsrt((x), fTCFG0_PRE0)
#define TCON_4_AUTO		(1 << 22)       /* auto reload on/off for Timer 4 */
#define TCON_4_UPDATE		(1 << 21)       /* manual Update TCNTB4 */
#define TCON_4_ONOFF		(1 << 20)       /* 0: Stop, 1: start Timer 4 */
#define COUNT_4_ON		(TCON_4_ONOFF*1)
#define COUNT_4_OFF		(TCON_4_ONOFF*0)
#define TCON_3_AUTO		(1 << 19)       /* auto reload on/off for Timer 3 */
#define TIMER3_ATLOAD_ON	(TCON_3_AUTO*1)
#define TIMER3_ATLAOD_OFF	FClrBit(TCON, TCON_3_AUTO)
#define TCON_3_INVERT		(1 << 18)       /* 1: Inverter on for TOUT3 */
#define TIMER3_IVT_ON		(TCON_3_INVERT*1)
#define TIMER3_IVT_OFF		(FClrBit(TCON, TCON_3_INVERT))
#define TCON_3_MAN		(1 << 17)       /* manual Update TCNTB3,TCMPB3 */
#define TIMER3_MANUP		(TCON_3_MAN*1)
#define TIMER3_NOP		(FClrBit(TCON, TCON_3_MAN))
#define TCON_3_ONOFF		(1 << 16)       /* 0: Stop, 1: start Timer 3 */
#define TIMER3_ON		(TCON_3_ONOFF*1)
#define TIMER3_OFF		(FClrBit(TCON, TCON_3_ONOFF))
/* macros */
#define GET_PRESCALE_TIMER4(x)	FExtr((x), fTCFG0_PRE1)
#define GET_DIVIDER_TIMER4(x)	FExtr((x), fTCFG1_MUX4)

/*
 * RTC Controller
 */
#define ELFIN_RTC_BASE		0x57000000
#define RTCCON_REG		__REG(0x57000040)
#define TICNT_REG		__REG(0x57000044)
#define RTCALM_REG		__REG(0x57000050)
#define ALMSEC_REG		__REG(0x57000054)
#define ALMMIN_REG		__REG(0x57000058)
#define ALMHOUR_REG		__REG(0x5700005c)
#define ALMDATE_REG		__REG(0x57000060)
#define ALMMON_REG		__REG(0x57000064)
#define ALMYEAR_REG		__REG(0x57000068)
#define BCDSEC_REG		__REG(0x57000070)
#define BCDMIN_REG		__REG(0x57000074)
#define BCDHOUR_REG		__REG(0x57000078)
#define BCDDATE_REG		__REG(0x5700007c)
#define BCDDAY_REG		__REG(0x57000080)
#define BCDMON_REG		__REG(0x57000084)
#define BCDYEAR_REG		__REG(0x57000088)

/*
 * HS MMC Interface (chapter 28)
 */
#define ELFIN_HSMMC_BASE	0x4a800000

#define HM_SYSAD	(ELFIN_HSMMC_BASE+0x00)
#define HM_BLKSIZE	(ELFIN_HSMMC_BASE+0x04)
#define HM_BLKCNT	(ELFIN_HSMMC_BASE+0x06)
#define HM_ARGUMENT	(ELFIN_HSMMC_BASE+0x08)
#define HM_TRNMOD	(ELFIN_HSMMC_BASE+0x0c)
#define HM_CMDREG	(ELFIN_HSMMC_BASE+0x0e)
#define HM_RSPREG0	(ELFIN_HSMMC_BASE+0x10)
#define HM_RSPREG1	(ELFIN_HSMMC_BASE+0x14)
#define HM_RSPREG2	(ELFIN_HSMMC_BASE+0x18)
#define HM_RSPREG3	(ELFIN_HSMMC_BASE+0x1c)
#define HM_BDATA	(ELFIN_HSMMC_BASE+0x20)
#define HM_PRNSTS	(ELFIN_HSMMC_BASE+0x24)
#define HM_HOSTCTL	(ELFIN_HSMMC_BASE+0x28)
#define HM_PWRCON	(ELFIN_HSMMC_BASE+0x29)
#define HM_BLKGAP	(ELFIN_HSMMC_BASE+0x2a)
#define HM_WAKCON	(ELFIN_HSMMC_BASE+0x2b)
#define HM_CLKCON	(ELFIN_HSMMC_BASE+0x2c)
#define HM_TIMEOUTCON	(ELFIN_HSMMC_BASE+0x2e)
#define HM_SWRST	(ELFIN_HSMMC_BASE+0x2f)
#define HM_NORINTSTS	(ELFIN_HSMMC_BASE+0x30)
#define HM_ERRINTSTS	(ELFIN_HSMMC_BASE+0x32)
#define HM_NORINTSTSEN	(ELFIN_HSMMC_BASE+0x34)
#define HM_ERRINTSTSEN	(ELFIN_HSMMC_BASE+0x36)
#define HM_NORINTSIGEN	(ELFIN_HSMMC_BASE+0x38)
#define HM_ERRINTSIGEN	(ELFIN_HSMMC_BASE+0x3a)
#define HM_ACMD12ERRSTS	(ELFIN_HSMMC_BASE+0x3c)
#define HM_CAPAREG	(ELFIN_HSMMC_BASE+0x40)
#define HM_MAXCURR	(ELFIN_HSMMC_BASE+0x48)
#define HM_CONTROL2	(ELFIN_HSMMC_BASE+0x80)
#define HM_CONTROL3	(ELFIN_HSMMC_BASE+0x84)
#define HM_CONTROL4	(ELFIN_HSMMC_BASE+0x8C)
#define HM_HCVER	(ELFIN_HSMMC_BASE+0xfe)

#define ELFIN_CFCON_BASE	0x4B800000

#define ATA_MUX			(ELFIN_CFCON_BASE+0x1800)
#define ELFIN_ATA_BASE		(ELFIN_CFCON_BASE+0x1900)

/*
 * ATA Register (chapter 8)
 */
#define ATA_CONTROL	(ELFIN_ATA_BASE + 0x00)
#define ATA_STATUS	(ELFIN_ATA_BASE + 0x04)
#define ATA_COMMAND	(ELFIN_ATA_BASE + 0x08)
#define ATA_SWRST	(ELFIN_ATA_BASE + 0x0c)
#define ATA_IRQ		(ELFIN_ATA_BASE + 0x10)
#define ATA_IRQ_MASK	(ELFIN_ATA_BASE + 0x14)
#define ATA_CFG		(ELFIN_ATA_BASE + 0x18)

#define ATA_PIO_TIME	(ELFIN_ATA_BASE + 0x2c)
#define ATA_UDMA_TIME	(ELFIN_ATA_BASE + 0x30)
#define ATA_XFR_NUM	(ELFIN_ATA_BASE + 0x34)
#define ATA_XFR_CNT	(ELFIN_ATA_BASE + 0x38)
#define ATA_TBUF_START	(ELFIN_ATA_BASE + 0x3c)
#define ATA_TBUF_SIZE	(ELFIN_ATA_BASE + 0x40)
#define ATA_SBUF_START	(ELFIN_ATA_BASE + 0x44)
#define ATA_SBUF_SIZE	(ELFIN_ATA_BASE + 0x48)
#define ATA_CADR_TBUF	(ELFIN_ATA_BASE + 0x4c)
#define ATA_CADR_SBUF	(ELFIN_ATA_BASE + 0x50)
#define ATA_PIO_DTR	(ELFIN_ATA_BASE + 0x54)
#define ATA_PIO_FED	(ELFIN_ATA_BASE + 0x58)
#define ATA_PIO_SCR	(ELFIN_ATA_BASE + 0x5c)
#define ATA_PIO_LLR	(ELFIN_ATA_BASE + 0x60)
#define ATA_PIO_LMR	(ELFIN_ATA_BASE + 0x64)
#define ATA_PIO_LHR	(ELFIN_ATA_BASE + 0x68)
#define ATA_PIO_DVR	(ELFIN_ATA_BASE + 0x6c)
#define ATA_PIO_CSD	(ELFIN_ATA_BASE + 0x70)
#define ATA_PIO_DAD	(ELFIN_ATA_BASE + 0x74)
#define ATA_PIO_READY	(ELFIN_ATA_BASE + 0x78)
#define ATA_PIO_RDATA	(ELFIN_ATA_BASE + 0x7c)
#define BUS_FIFO_STATUS	(ELFIN_ATA_BASE + 0x90)
#define ATA_FIFO_STATUS	(ELFIN_ATA_BASE + 0x94)

/*
 * SD/MMC Interface (chapter 27)
 */
#define ELFIN_SDI_BASE		0x5a000000
#define ELFIN_HSMMC_0_BASE 	0x4AC00000
#define ELFIN_HSMMC_1_BASE 	0x4A800000

#define SDICON		(ELFIN_SDI_BASE+0x00)	/* SDI Control */
#define SDIPRE		(ELFIN_SDI_BASE+0x04)	/* SDI baud rate prescaler */
#define SDICARG		(ELFIN_SDI_BASE+0x08)	/* SDI command argument */
#define SDICCON		(ELFIN_SDI_BASE+0x0c)	/* SDI command control */
#define SDICSTA		(ELFIN_SDI_BASE+0x10)	/* SDI command status */
#define SDIRSP0		(ELFIN_SDI_BASE+0x14)	/* SDI response 0 */
#define SDIRSP1		(ELFIN_SDI_BASE+0x18)	/* SDI response 1 */
#define SDIRSP2		(ELFIN_SDI_BASE+0x1c)	/* SDI response 2 */
#define SDIRSP3		(ELFIN_SDI_BASE+0x20)	/* SDI response 3 */
#define SDIDTIMER	(ELFIN_SDI_BASE+0x24)	/* SDI data/busy timer */
#define SDIBSIZE	(ELFIN_SDI_BASE+0x28)	/* SDI block size */
#define SDIDCON		(ELFIN_SDI_BASE+0x2c)	/* SDI data control */
#define SDIDCNT		(ELFIN_SDI_BASE+0x30)	/* SDI data remain counter */
#define SDIDSTA		(ELFIN_SDI_BASE+0x34)	/* SDI data status */
#define SDIFSTA		(ELFIN_SDI_BASE+0x38)	/* SDI FIFO status */
#define SDIIMSK		(ELFIN_SDI_BASE+0x3c)	/* SDI Interrupt Mask */
#define SDIDAT		(ELFIN_SDI_BASE+0x40)	/* SDI Data register */


/*
 * USB Device (Chapter 17)
 */
#define USB_DEVICE_PHYS_ADR	0x49800000
#define bUD(Nb)		__REG(USB_DEVICE_PHYS_ADR + (Nb))

#define UD_INDEX_REG			bUD(0x00) /* Index register */
#define UD_EP_INT_REG			bUD(0x04) /* EP Interrupt pending and clear */
#define UD_EP_INT_EN_REG		bUD(0x08) /* EP Interrupt enable */
#define UD_FUNC_ADDR_REG		bUD(0x0c) /* Function address */
#define UD_FRAME_NUM_REG		bUD(0x10) /* Frame number */
#define UD_EP_DIR_REG			bUD(0x14) /* Endpoint direction */
#define UD_TEST_REG			bUD(0x18) /* Test register */
#define UD_SYS_STATUS_REG		bUD(0x1c) /* System status */
#define UD_SYS_CON_REG			bUD(0x20) /* System control */
#define UD_EP0_STATUS_REG		bUD(0x24) /* Endpoint 0 status */
#define UD_EP0_CON_REG			bUD(0x28) /* Endpoint 0 control */
#define UD_EP0_BUF_REG			bUD(0x60) /* Endpoint 0 Buffer */
#define UD_EP1_BUF_REG			bUD(0x64) /* Endpoint 1 Buffer */
#define UD_EP2_BUF_REG			bUD(0x68) /* Endpoint 2 Buffer */
#define UD_EP3_BUF_REG			bUD(0x6c) /* Endpoint 3 Buffer */
#define UD_EP4_BUF_REG			bUD(0x70) /* Endpoint 4 Buffer */
#define UD_EP5_BUF_REG			bUD(0x74) /* Endpoint 5 Buffer */
#define UD_EP6_BUF_REG			bUD(0x78) /* Endpoint 6 Buffer */
#define UD_EP7_BUF_REG			bUD(0x7c) /* Endpoint 7 Buffer */
#define UD_EP8_BUF_REG			bUD(0x80) /* Endpoint 8 Buffer */
#define UD_FIFO_CON_REG			bUD(0x100) /* Burst FIFO-DMA Control */
#define UD_FIFO_STATUS_REG		bUD(0x104) /* Burst FIFO Status */

#define UD_EP_STATUS_REG		bUD(0x2c) /* Endpoints status */
#define UD_EP_CON_REG			bUD(0x30) /* Endpoints control */
#define UD_BYTE_READ_CNT_REG		bUD(0x34) /* Byte read count */
#define UD_BYTE_WRITE_CNT_REG		bUD(0x38) /* Byte write count */
#define UD_MAX_PKT_REG			bUD(0x3c) /* Max packet size */
#define UD_DMA_CON_REG			bUD(0x40) /* DMA control */
#define UD_DMA_CNT_REG			bUD(0x44) /* DMA count */
#define UD_DMA_FIFO_CNT_REG		bUD(0x48) /* DMA FIFO count */
#define UD_DMA_TOTAL_CNT1_REG		bUD(0x4c) /* DMA Total Transfer count1 */
#define UD_DMA_TOTAL_CNT2_REG		bUD(0x50) /* DMA Total Transfer count2 */
#define UD_DMA_IF_CON_REG		bUD(0x84) /* DMA interface Control */
#define UD_DMA_MEM_BASE_ADDR_REG	bUD(0x88) /* Mem Base Addr */
#define UD_DMA_MEM_CURRENT_ADDR_REG	bUD(0x8c) /* Mem current Addr */

/* index register set */
#define UD_INDEX_EP0		0
#define UD_INDEX_EP1		1
#define UD_INDEX_EP2		2
#define UD_INDEX_EP3		3
#define UD_INDEX_EP4		4

/* endpoint interrupt flag */
#define UD_INT_EP4		(1<<4)	// R/C
#define UD_INT_EP3		(1<<3)	// R/C
#define UD_INT_EP2		(1<<2)	// R/C
#define UD_INT_EP1		(1<<1)	// R/C
#define UD_INT_EP0		(1<<0)	// R/C

/* endpoint interrupt enable flag */
#define UD_INT_EN_EP4		(1<<4)
#define UD_INT_EN_EP3		(1<<3)
#define UD_INT_EN_EP2		(1<<2)
#define UD_INT_EN_EP1		(1<<1)
#define UD_INT_EN_EP0		(1<<0)

/* system status register Bits */
#define UD_INT_ERR		(0xff80)
#define UD_INT_VBUSON		(1<<8)
#define UD_INT_HSP		(1<<4) /* Host SPeed */
#define UD_INT_SDE		(1<<3) /* Speed Detection Dnd */
#define UD_INT_RESUME		(1<<2)
#define UD_INT_SUSPEND		(1<<1)
#define UD_INT_RESET		(1<<0)

/* system control register Bits */
#define UD_RRD_EN		(1<<5)
#define UD_SUS_EN		(1<<1)
#define UD_RST_EN		(1<<0)

/* EP0 status register Bits */
#define UD_EP0_SENT_STALL              (0x01<<4)
#define UD_EP0_DATA_END                (0x01<<3)
#define UD_EP0_SETUP_END               (0x03<<2)
#define UD_EP0_TX_SUCCESS              (0x01<<1)
#define UD_EP0_RX_SUCCESS              (0x01<<0)

/* Endpoint Status Register Bits */
#define UD_DMA_TOTAL_COUNT_ZERO        (0x1<<9)
#define UD_SHORT_PKT_RECEIVED          (0x1<<8)
#define UD_EP_FIFO_FLUSH               (0x1<<6)
#define UD_EP_SENT_STALL               (0x1<<5)
#define UD_EP_TX_SUCCESS               (0x1<<1)
#define UD_EP_RX_SUCCESS               (0x1<<0)

// USB Dma Operation
#define UD_DMA_AUTO_RX_DISABLE         (0x1<<5)
#define UD_DMA_FLY_ENABLE              (0x1<<4)
#define UD_DMA_FLY_DISABLE             (0x0<<4)
#define UD_DMA_DEMEND_ENABLE           (0x1<<3)
#define UD_DMA_DEMEND_DISABLE          (0x0<<3)
#define UD_DMA_TX_START                (0x1<<2)
#define UD_DMA_TX_STOP                 (0x0<<2)
#define UD_DMA_RX_START                (0x1<<1)
#define UD_DMA_RX_STOP                 (0x0<<1)
#define UD_USB_DMA_MODE                (0x1<<0)
#define UD_USB_INT_MODE                (0x0<<0)

/* DMA Interface Control Register Bits */
#define UD_MAX_BURST_INCR16            (0x3<<0)
#define UD_MAX_BURST_INCR8             (0x2<<0)
#define UD_MAX_BURST_INCR4             (0x1<<0)

/*Burst FIFO Control Register Bits */
#define UD_DMA_ENABLE                  (0x1<<8)
#define UD_DMA_DISABLE                 (0x0<<8)

/* Memory controller (see manual chapter 5) */
struct s3c24x0_memctl {
	u32	bwscon;
	u32	bankcon[8];
	u32	refresh;
	u32	banksize;
	u32	mrsrb6;
	u32	mrsrb7;
};


/* USB HOST (see manual chapter 12) */
struct s3c24x0_usb_host {
	u32	HcRevision;
	u32	HcControl;
	u32	HcCommonStatus;
	u32	HcInterruptStatus;
	u32	HcInterruptEnable;
	u32	HcInterruptDisable;
	u32	HcHCCA;
	u32	HcPeriodCuttendED;
	u32	HcControlHeadED;
	u32	HcControlCurrentED;
	u32	HcBulkHeadED;
	u32	HcBuldCurrentED;
	u32	HcDoneHead;
	u32	HcRmInterval;
	u32	HcFmRemaining;
	u32	HcFmNumber;
	u32	HcPeriodicStart;
	u32	HcLSThreshold;
	u32	HcRhDescriptorA;
	u32	HcRhDescriptorB;
	u32	HcRhStatus;
	u32	HcRhPortStatus1;
	u32	HcRhPortStatus2;
};


/* INTERRUPT (see manual chapter 14) */
struct s3c24x0_interrupt {
	u32	srcpnd;
	u32	intmod;
	u32	intmsk;
	u32	priority;
	u32	intpnd;
	u32	intoffset;
#if defined(CONFIG_S3C2410) || defined(CONFIG_S3C2440)
	u32	subsrcpnd;
	u32	intsubmsk;
#endif
};


/* DMAS (see manual chapter 8) */
struct s3c24x0_dma {
	u32	disrc;
#if defined(CONFIG_S3C2410) || defined(CONFIG_S3C2440)
	u32	disrcc;
#endif
	u32	didst;
#if defined(CONFIG_S3C2410) || defined(CONFIG_S3C2440)
	u32	didstc;
#endif
	u32	dcon;
	u32	dstat;
	u32	dcsrc;
	u32	dcdst;
	u32	dmasktrig;
#if defined(CONFIG_S3C2400) || defined(CONFIG_S3C2410) \
		|| defined(CONFIG_S3C2440)
	u32	res[1];
#endif
};

struct s3c24x0_dmas {
	struct s3c24x0_dma	dma[4];
};


/* CLOCK & POWER MANAGEMENT (see S3C2400 manual chapter 6) */
/*                          (see S3C2410 manual chapter 7) */
struct s3c24x0_clock_power {
	u32	locktime;
	u32	mpllcon;
	u32	upllcon;
	u32	clkcon;
	u32	clkslow;
	u32	clkdivn;
#if defined(CONFIG_S3C2440)
	u32	camdivn;
#endif
};


/* LCD CONTROLLER (see manual chapter 15) */
struct s3c24x0_lcd {
	u32	lcdcon1;
	u32	lcdcon2;
	u32	lcdcon3;
	u32	lcdcon4;
	u32	lcdcon5;
	u32	lcdsaddr1;
	u32	lcdsaddr2;
	u32	lcdsaddr3;
	u32	redlut;
	u32	greenlut;
	u32	bluelut;
	u32	res[8];
	u32	dithmode;
	u32	tpal;
#if defined(CONFIG_S3C2410) || defined(CONFIG_S3C2440)
	u32	lcdintpnd;
	u32	lcdsrcpnd;
	u32	lcdintmsk;
	u32	lpcsel;
#endif
};


#ifdef CONFIG_S3C2410
/* NAND FLASH (see S3C2410 manual chapter 6) */
struct s3c2410_nand {
	u32	nfconf;
	u32	nfcmd;
	u32	nfaddr;
	u32	nfdata;
	u32	nfstat;
	u32	nfecc;
};
#endif
#ifdef CONFIG_S3C2440
/* NAND FLASH (see S3C2440 manual chapter 6) */
struct s3c2440_nand {		/* 修改成S3C2416的结构 */
	u32	nfconf;
	u32	nfcont;
	u32	nfcmd;
	u32	nfaddr;
	u32	nfdata;
	u32	nfeccd0;
	u32	nfeccd1;
	u32	nfeccd;
	u32	nfsblk;
	u32	nfeblk;
	u32	nfstat;
	u32	nfeccerr0;
	u32	nfeccerr1;
};
#endif


/* UART (see manual chapter 11) */
struct s3c24x0_uart {
	u32	ulcon;
	u32	ucon;
	u32	ufcon;
	u32	umcon;
	u32	utrstat;
	u32	uerstat;
	u32	ufstat;
	u32	umstat;
#ifdef __BIG_ENDIAN
	u8	res1[3];
	u8	utxh;
	u8	res2[3];
	u8	urxh;
#else /* Little Endian */
	u8	utxh;
	u8	res1[3];
	u8	urxh;
	u8	res2[3];
#endif
	u32	ubrdiv;
};


/* PWM TIMER (see manual chapter 10) */
struct s3c24x0_timer {
	u32	tcntb;
	u32	tcmpb;
	u32	tcnto;
};

struct s3c24x0_timers {
	u32	tcfg0;
	u32	tcfg1;
	u32	tcon;
	struct s3c24x0_timer	ch[4];
	u32	tcntb4;
	u32	tcnto4;
};


/* USB DEVICE (see manual chapter 13) */
struct s3c24x0_usb_dev_fifos {
#ifdef __BIG_ENDIAN
	u8	res[3];
	u8	ep_fifo_reg;
#else /*  little endian */
	u8	ep_fifo_reg;
	u8	res[3];
#endif
};

struct s3c24x0_usb_dev_dmas {
#ifdef __BIG_ENDIAN
	u8	res1[3];
	u8	ep_dma_con;
	u8	res2[3];
	u8	ep_dma_unit;
	u8	res3[3];
	u8	ep_dma_fifo;
	u8	res4[3];
	u8	ep_dma_ttc_l;
	u8	res5[3];
	u8	ep_dma_ttc_m;
	u8	res6[3];
	u8	ep_dma_ttc_h;
#else /*  little endian */
	u8	ep_dma_con;
	u8	res1[3];
	u8	ep_dma_unit;
	u8	res2[3];
	u8	ep_dma_fifo;
	u8	res3[3];
	u8	ep_dma_ttc_l;
	u8	res4[3];
	u8	ep_dma_ttc_m;
	u8	res5[3];
	u8	ep_dma_ttc_h;
	u8	res6[3];
#endif
};

struct s3c24x0_usb_device {
#ifdef __BIG_ENDIAN
	u8	res1[3];
	u8	func_addr_reg;
	u8	res2[3];
	u8	pwr_reg;
	u8	res3[3];
	u8	ep_int_reg;
	u8	res4[15];
	u8	usb_int_reg;
	u8	res5[3];
	u8	ep_int_en_reg;
	u8	res6[15];
	u8	usb_int_en_reg;
	u8	res7[3];
	u8	frame_num1_reg;
	u8	res8[3];
	u8	frame_num2_reg;
	u8	res9[3];
	u8	index_reg;
	u8	res10[7];
	u8	maxp_reg;
	u8	res11[3];
	u8	ep0_csr_in_csr1_reg;
	u8	res12[3];
	u8	in_csr2_reg;
	u8	res13[7];
	u8	out_csr1_reg;
	u8	res14[3];
	u8	out_csr2_reg;
	u8	res15[3];
	u8	out_fifo_cnt1_reg;
	u8	res16[3];
	u8	out_fifo_cnt2_reg;
#else /*  little endian */
	u8	func_addr_reg;
	u8	res1[3];
	u8	pwr_reg;
	u8	res2[3];
	u8	ep_int_reg;
	u8	res3[15];
	u8	usb_int_reg;
	u8	res4[3];
	u8	ep_int_en_reg;
	u8	res5[15];
	u8	usb_int_en_reg;
	u8	res6[3];
	u8	frame_num1_reg;
	u8	res7[3];
	u8	frame_num2_reg;
	u8	res8[3];
	u8	index_reg;
	u8	res9[7];
	u8	maxp_reg;
	u8	res10[7];
	u8	ep0_csr_in_csr1_reg;
	u8	res11[3];
	u8	in_csr2_reg;
	u8	res12[3];
	u8	out_csr1_reg;
	u8	res13[7];
	u8	out_csr2_reg;
	u8	res14[3];
	u8	out_fifo_cnt1_reg;
	u8	res15[3];
	u8	out_fifo_cnt2_reg;
	u8	res16[3];
#endif /*  __BIG_ENDIAN */
	struct s3c24x0_usb_dev_fifos	fifo[5];
	struct s3c24x0_usb_dev_dmas	dma[5];
};


/* WATCH DOG TIMER (see manual chapter 18) */
struct s3c24x0_watchdog {
	u32	wtcon;
	u32	wtdat;
	u32	wtcnt;
};


/* IIC (see manual chapter 20) */
struct s3c24x0_i2c {
	u32	iiccon;
	u32	iicstat;
	u32	iicadd;
	u32	iicds;
};


/* IIS (see manual chapter 21) */
struct s3c24x0_i2s {
#ifdef __BIG_ENDIAN
	u16	res1;
	u16	iiscon;
	u16	res2;
	u16	iismod;
	u16	res3;
	u16	iispsr;
	u16	res4;
	u16	iisfcon;
	u16	res5;
	u16	iisfifo;
#else /*  little endian */
	u16	iiscon;
	u16	res1;
	u16	iismod;
	u16	res2;
	u16	iispsr;
	u16	res3;
	u16	iisfcon;
	u16	res4;
	u16	iisfifo;
	u16	res5;
#endif
};


/* I/O PORT (see manual chapter 9) */
struct s3c24x0_gpio {
#ifdef CONFIG_S3C2400
	u32	pacon;
	u32	padat;

	u32	pbcon;
	u32	pbdat;
	u32	pbup;

	u32	pccon;
	u32	pcdat;
	u32	pcup;

	u32	pdcon;
	u32	pddat;
	u32	pdup;

	u32	pecon;
	u32	pedat;
	u32	peup;

	u32	pfcon;
	u32	pfdat;
	u32	pfup;

	u32	pgcon;
	u32	pgdat;
	u32	pgup;

	u32	opencr;

	u32	misccr;
	u32	extint;
#endif
#ifdef CONFIG_S3C2410
	u32	gpacon;
	u32	gpadat;
	u32	res1[2];
	u32	gpbcon;
	u32	gpbdat;
	u32	gpbup;
	u32	res2;
	u32	gpccon;
	u32	gpcdat;
	u32	gpcup;
	u32	res3;
	u32	gpdcon;
	u32	gpddat;
	u32	gpdup;
	u32	res4;
	u32	gpecon;
	u32	gpedat;
	u32	gpeup;
	u32	res5;
	u32	gpfcon;
	u32	gpfdat;
	u32	gpfup;
	u32	res6;
	u32	gpgcon;
	u32	gpgdat;
	u32	gpgup;
	u32	res7;
	u32	gphcon;
	u32	gphdat;
	u32	gphup;
	u32	res8;

	u32	misccr;
	u32	dclkcon;
	u32	extint0;
	u32	extint1;
	u32	extint2;
	u32	eintflt0;
	u32	eintflt1;
	u32	eintflt2;
	u32	eintflt3;
	u32	eintmask;
	u32	eintpend;
	u32	gstatus0;
	u32	gstatus1;
	u32	gstatus2;
	u32	gstatus3;
	u32	gstatus4;
#endif
#if defined(CONFIG_S3C2440)
	u32	gpacon;
	u32	gpadat;
	u32	res1[2];
	u32	gpbcon;
	u32	gpbdat;
	u32	gpbup;
	u32	res2;
	u32	gpccon;
	u32	gpcdat;
	u32	gpcup;
	u32	res3;
	u32	gpdcon;
	u32	gpddat;
	u32	gpdup;
	u32	res4;
	u32	gpecon;
	u32	gpedat;
	u32	gpeup;
	u32	res5;
	u32	gpfcon;
	u32	gpfdat;
	u32	gpfup;
	u32	res6;
	u32	gpgcon;
	u32	gpgdat;
	u32	gpgup;
	u32	res7;
	u32	gphcon;
	u32	gphdat;
	u32	gphup;
	u32	res8;

	u32	misccr;
	u32	dclkcon;
	u32	extint0;
	u32	extint1;
	u32	extint2;
	u32	eintflt0;
	u32	eintflt1;
	u32	eintflt2;
	u32	eintflt3;
	u32	eintmask;
	u32	eintpend;
	u32	gstatus0;
	u32	gstatus1;
	u32	gstatus2;
	u32	gstatus3;
	u32	gstatus4;

	u32	res9;
	u32	dsc0;
	u32	dsc1;
	u32	mslcon;
	u32	gpjcon;
	u32	gpjdat;
	u32	gpjup;
	u32	res10;
#endif
};


/* RTC (see manual chapter 17) */
struct s3c24x0_rtc {
#ifdef __BIG_ENDIAN
	u8	res1[67];
	u8	rtccon;
	u8	res2[3];
	u8	ticnt;
	u8	res3[11];
	u8	rtcalm;
	u8	res4[3];
	u8	almsec;
	u8	res5[3];
	u8	almmin;
	u8	res6[3];
	u8	almhour;
	u8	res7[3];
	u8	almdate;
	u8	res8[3];
	u8	almmon;
	u8	res9[3];
	u8	almyear;
	u8	res10[3];
	u8	rtcrst;
	u8	res11[3];
	u8	bcdsec;
	u8	res12[3];
	u8	bcdmin;
	u8	res13[3];
	u8	bcdhour;
	u8	res14[3];
	u8	bcddate;
	u8	res15[3];
	u8	bcdday;
	u8	res16[3];
	u8	bcdmon;
	u8	res17[3];
	u8	bcdyear;
#else /*  little endian */
	u8	res0[64];
	u8	rtccon;
	u8	res1[3];
	u8	ticnt;
	u8	res2[11];
	u8	rtcalm;
	u8	res3[3];
	u8	almsec;
	u8	res4[3];
	u8	almmin;
	u8	res5[3];
	u8	almhour;
	u8	res6[3];
	u8	almdate;
	u8	res7[3];
	u8	almmon;
	u8	res8[3];
	u8	almyear;
	u8	res9[3];
	u8	rtcrst;
	u8	res10[3];
	u8	bcdsec;
	u8	res11[3];
	u8	bcdmin;
	u8	res12[3];
	u8	bcdhour;
	u8	res13[3];
	u8	bcddate;
	u8	res14[3];
	u8	bcdday;
	u8	res15[3];
	u8	bcdmon;
	u8	res16[3];
	u8	bcdyear;
	u8	res17[3];
#endif
};


/* ADC (see manual chapter 16) */
struct s3c2400_adc {
	u32	adccon;
	u32	adcdat;
};


/* ADC (see manual chapter 16) */
struct s3c2410_adc {
	u32	adccon;
	u32	adctsc;
	u32	adcdly;
	u32	adcdat0;
	u32	adcdat1;
};


/* SPI (see manual chapter 22) */
struct s3c24x0_spi_channel {
	u8	spcon;
	u8	res1[3];
	u8	spsta;
	u8	res2[3];
	u8	sppin;
	u8	res3[3];
	u8	sppre;
	u8	res4[3];
	u8	sptdat;
	u8	res5[3];
	u8	sprdat;
	u8	res6[3];
	u8	res7[16];
};

struct s3c24x0_spi {
	struct s3c24x0_spi_channel	ch[S3C24X0_SPI_CHANNELS];
};


/* MMC INTERFACE (see S3C2400 manual chapter 19) */
struct s3c2400_mmc {
#ifdef __BIG_ENDIAN
	u8	res1[3];
	u8	mmcon;
	u8	res2[3];
	u8	mmcrr;
	u8	res3[3];
	u8	mmfcon;
	u8	res4[3];
	u8	mmsta;
	u16	res5;
	u16	mmfsta;
	u8	res6[3];
	u8	mmpre;
	u16	res7;
	u16	mmlen;
	u8	res8[3];
	u8	mmcr7;
	u32	mmrsp[4];
	u8	res9[3];
	u8	mmcmd0;
	u32	mmcmd1;
	u16	res10;
	u16	mmcr16;
	u8	res11[3];
	u8	mmdat;
#else
	u8	mmcon;
	u8	res1[3];
	u8	mmcrr;
	u8	res2[3];
	u8	mmfcon;
	u8	res3[3];
	u8	mmsta;
	u8	res4[3];
	u16	mmfsta;
	u16	res5;
	u8	mmpre;
	u8	res6[3];
	u16	mmlen;
	u16	res7;
	u8	mmcr7;
	u8	res8[3];
	u32	mmrsp[4];
	u8	mmcmd0;
	u8	res9[3];
	u32	mmcmd1;
	u16	mmcr16;
	u16	res10;
	u8	mmdat;
	u8	res11[3];
#endif
};


/* SD INTERFACE (see S3C2410 manual chapter 19) */
struct s3c2410_sdi {
	u32	sdicon;
	u32	sdipre;
	u32	sdicarg;
	u32	sdiccon;
	u32	sdicsta;
	u32	sdirsp0;
	u32	sdirsp1;
	u32	sdirsp2;
	u32	sdirsp3;
	u32	sdidtimer;
	u32	sdibsize;
	u32	sdidcon;
	u32	sdidcnt;
	u32	sdidsta;
	u32	sdifsta;
#ifdef __BIG_ENDIAN
	u8	res[3];
	u8	sdidat;
#else
	u8	sdidat;
	u8	res[3];
#endif
	u32	sdiimsk;
};

#endif /*__S3C24X0_H__*/
