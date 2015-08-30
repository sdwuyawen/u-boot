/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002, 2010
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
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

#include <common.h>
#include <netdev.h>
#include <asm/io.h>
#include <asm/arch/s3c24x0_cpu.h>

DECLARE_GLOBAL_DATA_PTR;

#define FCLK_SPEED 1

#if FCLK_SPEED==0		/* Fout = 203MHz, Fin = 12MHz for Audio */
#define M_MDIV	0xC3
#define M_PDIV	0x4
#define M_SDIV	0x1
#elif FCLK_SPEED==1		/* Fout = 202.8MHz */
#define M_MDIV	0xA1
#define M_PDIV	0x3
#define M_SDIV	0x1
#endif

#define USB_CLOCK 1

#if USB_CLOCK==0
#define U_M_MDIV	0xA1
#define U_M_PDIV	0x3
#define U_M_SDIV	0x1
#elif USB_CLOCK==1
#define U_M_MDIV	0x48
#define U_M_PDIV	0x3
#define U_M_SDIV	0x2
#endif

static inline void pll_delay(unsigned long loops)
{
	__asm__ volatile ("1:\n"
	  "subs %0, %1, #1\n"
	  "bne 1b":"=r" (loops):"0" (loops));
}

/*
 * Miscellaneous platform dependent initialisations
 */
 
static void cs8900_pre_init(void)
{
#if 1
	SMBIDCYR1_REG = 0;				//Bank1 Idle cycle ctrl.
	SMBWSTWRR1_REG = 14;			//Bank1 Write Wait State ctrl.
	SMBWSTOENR1_REG = 2;			//Bank1 Output Enable Assertion Delay ctrl.     Tcho?
	SMBWSTWENR1_REG = 2;			//Bank1 Write Enable Assertion Delay ctrl.
	SMBWSTRDR1_REG = 14;			//Bank1 Read Wait State cont. = 14 clk	    Tacc?
#endif
	SMBCR1_REG |=  ((1<<15)|(1<<7));		//dsf
	SMBCR1_REG |=  ((1<<2)|(1<<0));		//SMWAIT active High, Read Byte Lane Enabl	    WS1?
	SMBCR1_REG &= ~((3<<20)|(3<<12));	//SMADDRVALID = always High when Read/Write
	SMBCR1_REG &= ~(3<<4);			//Clear Memory Width
	SMBCR1_REG |=  (1<<4);			//Memory Width = 16bit
}


static void dm9000_pre_init(void)
{
     u32 val;

/*
#define S3C24XX_VA_SROMC    S3C2410_ADDR(0x03700000)
#define S3C2443_PA_SROMC    (0x4F000000)
#define S3C24XX_SZ_SROMC    SZ_1M
*/
    /* Bank2 Idle cycle ctrl. */
//    writel(0xf, S3C_SSMC_SMBIDCYR2);
	SMBIDCYR2_REG = 0x0f;

	/* Bank2 Read Wait State cont. = 14 clk          Tacc? */
	/* WSTRD表示从nCS有效到nRD无效总长度，即nRD总长度，包含WSTOEN部分，WSTOEN必须<=WSTRD */
//    writel(12, S3C_SSMC_SMBWSTRDR2);
	SMBWSTRDR2_REG = 12;

	/* Bank2 Write Wait State ctrl. */
	/* WSTWR表示从nCS有效到nWE无效总长度，即nWR总长度，包含WSTWEN部分，WSTWEN必须<=WSTWR */
//    writel(12, S3C_SSMC_SMBWSTWRR2);
	SMBWSTWRR2_REG = 12;

    /* Bank2 Output Enable Assertion Delay ctrl.     Tcho? */
	/* nCS有效到nOE有效之间的间隔，和WSTRD配套使用 */
//    writel(2, S3C_SSMC_SMBWSTOENR2);
	SMBWSTOENR2_REG = 2;


    /* Bank2 Write Enable Assertion Delay ctrl. */
	/* nCS有效到nWE有效之间的间隔，和WSTWR配套使用 */
//    writel(2, S3C_SSMC_SMBWSTWENR2);
	SMBWSTWENR2_REG = 2;

	/* 在ADDR信号和nCS信号之间插入delay，数值由SMBCR中DELAYnCS确定 */
//    val = readl(S3C_SSMC_SMBCR2);
	val = SMBCR2_REG;

    val |=  ((1<<15)|(1<<7));       /* .bit7 = 1, .bit15 = 1 */
//  val &=  ~((1<<15)|(1<<7));      /* .bit7 = 0, .bit15 = 0 */
//    writel(val, S3C_SSMC_SMBCR2);
	SMBCR2_REG = val;

	/* bit2是使能nWait,=1表示使能
       * =0时，WSTRD,WSTWR,WSTOEN,WSTWEN有效
       * =1时，SMBCR.DRnOWE=1时
       *             nCS到nOE的时间由WSTOEN确定，必须大于1
       *             nCS到nWE的时间由WSTWEN确定，必须大于1
       *       SMBCR.DRnCS=1时
       *             ADDR Signal和nCS之间的时间由SMBCR.DELAYnCS确定
       *
       */
      /* bit1配置nWait的极性，默认0表示低电平有效 */
      /* bit0是RBLE,=1表示在read时nBE[1:0]保持为0
       * nBE[1:0]在板子上未连接
       */
//    val = readl(S3C_SSMC_SMBCR2);
	val = SMBCR2_REG;
    val |=  ((1<<2)|(1<<0));    /* .bit2 = 1, .bit0 = 1 */
//  val &=  ~(1<<2);            /* .bit2 = 0 */
//  val |=  (1<<0);         /* .bit0 = 1 */
//    writel(val, S3C_SSMC_SMBCR2);
	SMBCR2_REG = val;

    /* SMAddrValid = always High when Read/Write
     * RSMAVD保持为高 
	 */
//    val = readl(S3C_SSMC_SMBCR2);
	val = SMBCR2_REG;
    val &= ~((3<<20)|(3<<12));
//    writel(val, S3C_SSMC_SMBCR2);
	SMBCR2_REG = val;

	/* 设置位宽,8 */
//    val = readl(S3C_SSMC_SMBCR2);
	val = SMBCR2_REG;
    val &= ~(3<<4);
//    writel(val, S3C_SSMC_SMBCR2);
	SMBCR2_REG = val;

//    val = readl(S3C_SSMC_SMBCR2);
	val = SMBCR2_REG;
    val |= (0<<4);

//    writel(val, S3C_SSMC_SMBCR2);
	SMBCR2_REG = val;
}

int board_early_init_f(void)
{
	struct s3c24x0_clock_power * const clk_power =
					s3c24x0_get_base_clock_power();
	struct s3c24x0_gpio * const gpio = s3c24x0_get_base_gpio();

	/* to reduce PLL lock time, adjust the LOCKTIME register */
//	writel(0xFFFFFF, &clk_power->locktime);

	/* configure MPLL */
//	writel((M_MDIV << 12) + (M_PDIV << 4) + M_SDIV,
//	       &clk_power->mpllcon);

	/* some delay between MPLL and UPLL */
//	pll_delay(4000);

	/* configure UPLL */
//	writel((U_M_MDIV << 12) + (U_M_PDIV << 4) + U_M_SDIV,
//	       &clk_power->upllcon);

	/* some delay between MPLL and UPLL */
//	pll_delay(8000);

	/* set up the I/O ports */
	writel(0x007FFFFF, &gpio->gpacon);
//	writel(0x00044555, &gpio->gpbcon);
//	writel(0x000007FF, &gpio->gpbup);
	writel(0xAAAAAAAA, &gpio->gpccon);
	writel(0x0000FFFF, &gpio->gpcup);
	writel(0xAAAAAAAA, &gpio->gpdcon);
	writel(0x0000FFFF, &gpio->gpdup);
	writel(0xAAAAAAAA, &gpio->gpecon);
	writel(0x0000FFFF, &gpio->gpeup);
	writel(0x000055AA, &gpio->gpfcon);
	writel(0x000000FF, &gpio->gpfup);
	writel(0xFF95FFBA, &gpio->gpgcon);
	writel(0x0000FFFF, &gpio->gpgup);
	writel(0x002AFAAA, &gpio->gphcon);
	writel(0x000007FF, &gpio->gphup);

	/* RAADR0/GPA0, nRCS1/GPA12, EINT15/GPG7, */
	/* Set EBI Registers */
	cs8900_pre_init();		
	dm9000_pre_init();

	return 0;
}


/* SUBSRCPND,SRCPND1,SRCPND2,INTPND1,INTPND2 */
#define SUBSRCPND	0x4A000018
#define SRCPND1		0x4A000000
#define INTPND1		0x4A000010
#define SRCPND2		0x4A000040
#define INTPND2		0x4A000050
int board_int_clear(void)
{
	volatile unsigned long value = 0;
	
	value = __REG(SUBSRCPND);
	printf("SUBSRCPND=0x%08x\n", value);
	__REG(SUBSRCPND) = value;

	value = __REG(SRCPND1);
	printf("SRCPND1=0x%08x\n", value);
	__REG(SRCPND1) = value;

	value = __REG(INTPND1);
	printf("INTPND1=0x%08x\n", value);
	__REG(INTPND1) = value;

	value = __REG(SRCPND2);
	printf("SRCPND2=0x%08x\n", value);
	__REG(SRCPND2) = value;

	value = __REG(INTPND2);
	printf("INTPND2=0x%08x\n", value);
	__REG(INTPND2) = value;

	return 0;
}
int board_init(void)
{
	/* arch number of SMDK2410-Board */
	gd->bd->bi_arch_number = MACH_TYPE_SMDK2410;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0x30000100;

	/* ICACHE DCACHE */	
	icache_enable();
	dcache_enable();

	board_int_clear();		/* SUBSRCPND,SRCPND1,SRCPND2,INTPND1,INTPND2 */

	return 0;
}

int dram_init(void)
{
	/* dram_init must store complete ramsize in gd->ram_size */
	gd->ram_size = PHYS_SDRAM_1_SIZE;
	return 0;
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;

	debug("board_eth_init\r\n");
#ifdef CONFIG_CS8900
	rc = cs8900_initialize(0, CONFIG_CS8900_BASE);
#endif

#ifdef CONFIG_DRIVER_SMC911X
	rc = smc911x_initialize (0, CONFIG_DRIVER_SMC911X_BASE);
#endif

#ifdef CONFIG_DRIVER_DM9000
	rc = dm9000_initialize(bis);
#endif
	return rc;
}
#endif

/*
 * Hardcoded flash setup:
 * Flash 0 is a non-CFI AMD AM29LV800BB flash.
 */
ulong board_flash_get_legacy(ulong base, int banknum, flash_info_t *info)
{
	info->portwidth = FLASH_CFI_16BIT;
	info->chipwidth = FLASH_CFI_BY16;
	info->interface = FLASH_CFI_X16;
	return 1;
}
