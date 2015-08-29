/*
 * (C) Copyright 2006 OpenMoko, Inc.
 * Author: Harald Welte <laforge@openmoko.org>
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

#include <nand.h>
#include <asm/arch/s3c24x0_cpu.h>
#include <asm/io.h>

#include <asm/errno.h>	/* by wu */

/* When NAND is used as boot device, below is set to 1. */
int boot_nand = 0;

/* Nand flash definition values by jsgood */
#define S3C_NAND_TYPE_UNKNOWN	0x0
#define S3C_NAND_TYPE_SLC	0x1
#define S3C_NAND_TYPE_MLC	0x2
//#undef	S3C_NAND_DEBUG

/* Nand flash global values by jsgood */
int cur_ecc_mode = 0;
int nand_type = S3C_NAND_TYPE_UNKNOWN;

/* Nand flash oob definition for SLC 2k page size by jsgood */
static struct nand_ecclayout s3c_nand_oob_64 = {
	.useecc = MTD_NANDECC_AUTOPLACE,	/* Only for U-Boot */
	.eccbytes = 16,
	.eccpos = {40, 41, 42, 43, 44, 45, 46, 47,
		   48, 49, 50, 51, 52, 53, 54, 55},
	.oobfree = {
		{.offset = 2,
		 .length = 38}}
};

/*#define S3C2410_NFCONF_EN          (1<<15)
#define S3C2410_NFCONF_512BYTE     (1<<14)
#define S3C2410_NFCONF_4STEP       (1<<13)
#define S3C2410_NFCONF_INITECC     (1<<12)
#define S3C2410_NFCONF_nFCE        (1<<11)
#define S3C2410_NFCONF_TACLS(x)    ((x)<<8)
#define S3C2410_NFCONF_TWRPH0(x)   ((x)<<4)
#define S3C2410_NFCONF_TWRPH1(x)   ((x)<<0)

#define S3C2410_ADDR_NALE 4
#define S3C2410_ADDR_NCLE 8*/

#ifdef CONFIG_NAND_SPL

/* in the early stage of NAND flash booting, printf() is not available */
#define printf(fmt, args...)

static void nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	int i;
	struct nand_chip *this = mtd->priv;

	for (i = 0; i < len; i++)
		buf[i] = readb(this->IO_ADDR_R);
}
#endif


/*	ctrl	:表示做什么，选中芯片/取消片选，发命令，发地址
 *
 *	dat	:命令值或地址值
 */
static void s3c2440_hwcontrol(struct mtd_info *mtd, int dat, unsigned int ctrl)
{
/* 2012.04.01自带的 */
//	struct nand_chip *chip = mtd->priv;
//	struct s3c2440_nand *nand = s3c2440_get_base_nand();

//	debug("hwcontrol(): 0x%02x 0x%02x\n", cmd, ctrl);

//	if (ctrl & NAND_CTRL_CHANGE) {
//		ulong IO_ADDR_W = (ulong)nand;

//		if (!(ctrl & NAND_CLE))
//			IO_ADDR_W |= S3C2410_ADDR_NCLE;
//		if (!(ctrl & NAND_ALE))
//			IO_ADDR_W |= S3C2410_ADDR_NALE;

//		chip->IO_ADDR_W = (void *)IO_ADDR_W;

//		if (ctrl & NAND_NCE)	/* 使能选中 */
//			writel(readl(&nand->nfcont) & ~(1<<1),
//			       &nand->nfcont);
//		else		/* 取消选中 */
//			writel(readl(&nand->nfcont) | (1<<1),
//			       &nand->nfcont);
//	}

//	if (cmd != NAND_CMD_NONE)
//		writeb(cmd, chip->IO_ADDR_W);

/* 韦东山毕业班视频2.3.4添加的 */
//	if(ctrl & NAND_CLE)
//	{
//		/* 发命令 */
//		writeb(dat, &nand->nfcmd);
//	}
//	else if(ctrl & NAND_ALE)
//	{
//		/* 发地址 */
//		writeb(dat, &nand->nfaddr);
//	}

/* helper2416里的 */
	unsigned int cur;
	struct s3c2440_nand *nand = s3c2440_get_base_nand();

	if (ctrl & NAND_CTRL_CHANGE) 
	{
		if (ctrl & NAND_NCE)	/* 选中 */
		{
			if (dat != NAND_CMD_NONE) 
			{
				cur = readl(&nand->nfcont);
				
				if (boot_nand)
					cur &= ~(1<<1);
				else
					cur &= ~(1<<1);

				writel(cur, &nand->nfcont);
			}
		} 
		else 				/* 取消选中 */
		{
			cur = readl(&nand->nfcont);
			
			if (boot_nand)
				cur |= (1<<1);
			else
				cur |= (1<<1);

			writel(cur, &nand->nfcont);
		}
	}

	if (dat != NAND_CMD_NONE) 
	{
		if (ctrl & NAND_CLE)
//			writeb(dat, NFCMMD);
			writeb(dat, &nand->nfcmd);
		else if (ctrl & NAND_ALE)
//			writeb(dat, NFADDR);
			writeb(dat, &nand->nfaddr);
	}

	
}

static int s3c2440_dev_ready(struct mtd_info *mtd)
{
	struct s3c2440_nand *nand = s3c2440_get_base_nand();
//	debug("dev_ready\n");
	return readl(&nand->nfstat) & 0x01;
}

/*
 * We don't use bad block table
 */
static int s3c2440_nand_scan_bbt(struct mtd_info *mtdinfo)
{
	debug("s3c2440_nand_scan_bbt\r\n");
	return nand_default_bbt(mtdinfo);
}


static void s3c2440_nand_select(struct mtd_info *mtd, int chipnr)
{
	struct s3c2440_nand *nand = s3c2440_get_base_nand();

	switch (chipnr) {
	case -1:		/* 取消选中 */
//		writel((readl(&nand->nfcont) | (1<<1),&nand->nfcont);
		nand->nfcont |= (1<<1);
		break;
	case 0:		/* 选中 */
		nand->nfcont &= ~(1<<1);
		break;

	default:
		BUG();
	}
}

#ifdef CONFIG_S3C2440_NAND_HWECC
/*
 * Function for checking ECCEncDone in NFSTAT
 * Written by jsgood
 */
static void s3c_nand_wait_enc(void)
{
	debug("s3c_nand_wait_enc\r\n");

	/* S3C2412 can not check NFSTAT_ECCENCDONE */
#if defined(CONFIG_S3C2450) || defined(CONFIG_S3C2416) || defined(CONFIG_S3C2443)
	while (!(readl(NFSTAT) & NFSTAT_ECCENCDONE)) {}
#else
	return;
#endif
}

/*
 * Function for checking ECCDecDone in NFSTAT
 * Written by jsgood
 */
static void s3c_nand_wait_dec(void)
{
	debug("s3c_nand_wait_dec\r\n");

#if defined(CONFIG_S3C2450) || defined(CONFIG_S3C2416) || defined(CONFIG_S3C2443) || defined(CONFIG_S3C2412)
	while (!(readl(NFSTAT) & NFSTAT_ECCDECDONE)) {}
#else
	return;
#endif
}

/*
 * Function for checking ECC Busy
 * Written by jsgood
 */
static void s3c_nand_wait_ecc_busy(void)
{
	debug("s3c_nand_wait_ecc_busy\r\n");
	
#if defined(CONFIG_S3C2450) || defined(CONFIG_S3C2416) || defined(CONFIG_S3C2443) || defined(CONFIG_S3C2412)
	while (readl(NFESTAT0) & NFESTAT0_ECCBUSY) {}
#endif
}

/*
 *	选择1bit ECC，清ECC Value，解锁main area ecc，在read/write过程中自动计算ECC，保存在NFMECC0/1
 */
void s3c2440_nand_enable_hwecc(struct mtd_info *mtd, int mode)
{
	/* 2012.04.01 */
//	struct s3c2440_nand *nand = s3c2440_get_base_nand();
//	debug("s3c2440_nand_enable_hwecc(%p, %d)\n", mtd, mode);
//	writel(readl(&nand->nfconf) | S3C2440_NFCONF_INITECC, &nand->nfconf);

	/* helper2416 */
/*
 * This function is called before encoding ecc codes to ready ecc engine.
 * Written by jsgood
 */
	u_long nfcont;
	cur_ecc_mode = mode;

//	debug("s3c2440_nand_enable_hwecc\r\n");
	
#if defined(CONFIG_S3C2450) || defined(CONFIG_S3C2416) || defined(CONFIG_S3C2443) || defined(CONFIG_S3C2412)
	u_long nfconf;

	nfconf = readl(NFCONF);

#if defined(CONFIG_S3C2450) || defined(CONFIG_S3C2416)
	nfconf &= ~(0x3 << 23);		/* 1bit ECC */

	if (nand_type == S3C_NAND_TYPE_SLC)
		nfconf |= NFCONF_ECC_1BIT;
	else
		nfconf |= NFCONF_ECC_4BIT;
#else
	if (nand_type == S3C_NAND_TYPE_SLC)
		nfconf &= ~NFCONF_ECC_MLC;	/* SLC */
	else
		nfconf |= NFCONF_ECC_MLC;	/* MLC */
#endif

	writel(nfconf, NFCONF);
#endif
	/* Initialize & unlock */
	nfcont = readl(NFCONT);
	nfcont |= NFCONT_INITMECC;
	nfcont &= ~NFCONT_MECCLOCK;

#if defined(CONFIG_S3C2450) || defined(CONFIG_S3C2416) || defined(CONFIG_S3C2443) || defined(CONFIG_S3C2412)
	if (nand_type == S3C_NAND_TYPE_MLC) {
		if (mode == NAND_ECC_WRITE)
			nfcont |= NFCONT_ECC_ENC;
		else if (mode == NAND_ECC_READ)
			nfcont &= ~NFCONT_ECC_ENC;
	}
#endif
	writel(nfcont, NFCONT);
}


/*
 * 完成main area的读写后调用，获取main area的ecc
 */
static int s3c2440_nand_calculate_ecc(struct mtd_info *mtd, const u_char *dat,
				      u_char *ecc_code)
{
	/* 2012.04.01 */
//	struct s3c2440_nand *nand = s3c2440_get_base_nand();
//	ecc_code[0] = readb(&nand->nfecc);
//	ecc_code[1] = readb(&nand->nfecc + 1);
//	ecc_code[2] = readb(&nand->nfecc + 2);
//	debug("s3c2440_nand_calculate_hwecc(%p,): 0x%02x 0x%02x 0x%02x\n",
//	       mtd , ecc_code[0], ecc_code[1], ecc_code[2]);

//	return 0;


	/* helper2416 */
/*
 * This function is called immediately after encoding ecc codes.
 * This function returns encoded ecc codes.
 * Written by jsgood
 */
	u_long nfcont, nfmecc0, nfmecc1;

//	debug("s3c2440_nand_calculate_ecc\r\n");

	/* Lock */
	nfcont = readl(NFCONT);
	nfcont |= NFCONT_MECCLOCK;
	writel(nfcont, NFCONT);

	if (nand_type == S3C_NAND_TYPE_SLC) 
	{
		nfmecc0 = readl(NFMECC0);
		
		ecc_code[0] = nfmecc0 & 0xff;
		ecc_code[1] = (nfmecc0 >> 8) & 0xff;
		ecc_code[2] = (nfmecc0 >> 16) & 0xff;
		ecc_code[3] = (nfmecc0 >> 24) & 0xff;
	} 
	else 
	{
		if (cur_ecc_mode == NAND_ECC_READ)
			s3c_nand_wait_dec();
		else {
			s3c_nand_wait_enc();
			
			nfmecc0 = readl(NFMECC0);
			nfmecc1 = readl(NFMECC1);

			ecc_code[0] = nfmecc0 & 0xff;
			ecc_code[1] = (nfmecc0 >> 8) & 0xff;
			ecc_code[2] = (nfmecc0 >> 16) & 0xff;
			ecc_code[3] = (nfmecc0 >> 24) & 0xff;			
			ecc_code[4] = nfmecc1 & 0xff;
			ecc_code[5] = (nfmecc1 >> 8) & 0xff;
			ecc_code[6] = (nfmecc1 >> 16) & 0xff;
			ecc_code[7] = (nfmecc1 >> 24) & 0xff;
		}
	}
	
	return 0;
}


/*
 * 把从spare area读取的4字节ecc写入NFMECCD0/1，并根据NFECCER0判断错误代码，可修复则修复
 * dat:	要correct的数组
 * read_ecc:	从读取的数据计算出的ECC
 */
static int s3c2440_nand_correct_data(struct mtd_info *mtd, u_char *dat,
				     u_char *read_ecc, u_char *calc_ecc)
{
	/* 2012.04.01 */
//	if (read_ecc[0] == calc_ecc[0] &&
//	    read_ecc[1] == calc_ecc[1] &&
//	    read_ecc[2] == calc_ecc[2])
//		return 0;

//	printf("s3c2440_nand_correct_data: not implemented\n");
//	return -1;


	/* helper2416 */
/*
 * This function determines whether read data is good or not.
 * If SLC, must write ecc codes to controller before reading status bit.
 * If MLC, status bit is already set, so only reading is needed.
 * If status bit is good, return 0.
 * If correctable errors occured, do that.
 * If uncorrectable errors occured, return -1.
 * Written by jsgood
 */
	int ret = -1;
	u_long nfestat0, nfestat1, nfmeccdata0, nfmeccdata1, nfmlcbitpt;
	u_char err_type;

//	debug("s3c2440_nand_correct_data\r\n");

	if (nand_type == S3C_NAND_TYPE_SLC) 
	{
		/* SLC: Write ecc to compare */
		nfmeccdata0 = (read_ecc[1] << 16) | read_ecc[0];
		nfmeccdata1 = (read_ecc[3] << 16) | read_ecc[2];
		writel(nfmeccdata0, NFMECCDATA0);
		writel(nfmeccdata1, NFMECCDATA1);

		/* Read ecc status */
		nfestat0 = readl(NFESTAT0);
		err_type = nfestat0 & 0x3;

		switch (err_type) {
		case 0: /* No error */
			ret = 0;
			break;

		case 1: /* 1 bit error (Correctable)
			   (nfestat0 >> 7) & 0x7ff	:error byte number
			   (nfestat0 >> 4) & 0x7	:error bit number */
			printk("s3c-nand: 1 bit error detected at byte %ld, correcting from "
					"0x%02x ", (nfestat0 >> 7) & 0x7ff, dat[(nfestat0 >> 7) & 0x7ff]);
			dat[(nfestat0 >> 7) & 0x7ff] ^= (1 << ((nfestat0 >> 4) & 0x7));
			printk("to 0x%02x...OK\n", dat[(nfestat0 >> 7) & 0x7ff]);
			ret = 1;
			break;

		case 2: /* Multiple error */
		case 3: /* ECC area error */
			printk("s3c-nand: ECC uncorrectable error detected\n");
			ret = -1;
			break;
		}
	} 
	else 
	{	
		/* MLC: */
		s3c_nand_wait_ecc_busy();
		
		nfestat0 = readl(NFESTAT0);
		nfestat1 = readl(NFESTAT1);

#if defined(CONFIG_S3C2450) || defined(CONFIG_S3C2416) || defined(CONFIG_S3C2443) || defined(CONFIG_S3C2412)
		nfmlcbitpt = readl(NFMLCBITPT);
#endif

		err_type = (nfestat0 >> 26) & 0x7;

		/* No error, If free page (all 0xff) */
		if ((nfestat0 >> 29) & 0x1) {
			err_type = 0;
		} else {
			/* No error, If all 0xff from 17th byte in oob (in case of JFFS2 format) */
			if (dat) {
				if (dat[17] == 0xff && dat[26] == 0xff && dat[35] == 0xff && dat[44] == 0xff && dat[54] == 0xff)
					err_type = 0;
			}
		}

		switch (err_type) {
		case 5: /* Uncorrectable */
			printk("s3c-nand: ECC uncorrectable error detected\n");
			ret = -1;
			break;

		case 4: /* 4 bit error (Correctable) */
			dat[(nfestat1 >> 16) & 0x3ff] ^= ((nfmlcbitpt >> 24) & 0xff);

		case 3: /* 3 bit error (Correctable) */
			dat[nfestat1 & 0x3ff] ^= ((nfmlcbitpt >> 16) & 0xff);

		case 2: /* 2 bit error (Correctable) */
			dat[(nfestat0 >> 16) & 0x3ff] ^= ((nfmlcbitpt >> 8) & 0xff);

		case 1: /* 1 bit error (Correctable) */
			printk("s3c-nand: %d bit(s) error detected, corrected successfully\n", err_type);
			dat[nfestat0 & 0x3ff] ^= (nfmlcbitpt & 0xff);
			ret = err_type;
			break;

		case 0: /* No error */
			ret = 0;
			break;
		}
	}

	return ret;
}

/* ecc.size：每一次硬件ECC所检验的字节个数 */
/* ecc.bytes：每一次硬件ECC所生成的字节个数 */
/* ecc.steps：每一页需要进行硬件ECC的次数 */
static int s3c2440_nand_read_page_1bit(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf)
{
	int i, stat, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	int secc_start = mtd->oobsize - eccbytes;	/* 64 - 4 = 60 */
	int col = 0;
	uint8_t *p = buf;	
	uint32_t *mecc_pos = chip->ecc.layout->eccpos;	/* main area的ecc在spare area中存放的偏移位置,eccpos[0]=40 */
	uint8_t *ecc_calc = chip->buffers->ecccalc;

//	debug("s3c2440_nand_read_page_1bit\r\n");

	col = mtd->writesize;
	chip->cmdfunc(mtd, NAND_CMD_RNDOUT, col, -1);

	/* spare area */
	chip->ecc.hwctl(mtd, NAND_ECC_READ);
	chip->read_buf(mtd, chip->oob_poi, secc_start);	/* 读取OOB60字节到chip->oob_poi */
	chip->ecc.calculate(mtd, p, &ecc_calc[chip->ecc.total]);	/* 计算前60字节的ecc，并存到ecc_calc[16]开始的4字节。ecc.total=16 */
	chip->read_buf(mtd, chip->oob_poi + secc_start, eccbytes);	/* 读取OOB剩余4字节 */

	/* jffs2 special case */
	if (!(chip->oob_poi[2] == 0x85 && chip->oob_poi[3] == 0x19))
		chip->ecc.correct(mtd, chip->oob_poi, chip->oob_poi + secc_start, 0);

	col = 0;

	/* main area */
	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		chip->cmdfunc(mtd, NAND_CMD_RNDOUT, col, -1);
		chip->ecc.hwctl(mtd, NAND_ECC_READ);	/* 初始化硬件ECC */
		chip->read_buf(mtd, p, eccsize);			/* 读取512字节 */
		chip->ecc.calculate(mtd, p, &ecc_calc[i]);	/* 锁定硬件ECC，计算4字节ECC并存到ecc_calc[0-15] */

		/*
		*	p是要修复的数据指针
		*	chip->oob_poi + mecc_pos[0] + ((chip->ecc.steps - eccsteps) * eccbytes)是
		*	从spare area读取的ECC，mecc_pos[0]是40，spare area的40字节开始存放main area的4次共16字节ECC
		*/
		stat = chip->ecc.correct(mtd, p, chip->oob_poi + mecc_pos[0] + ((chip->ecc.steps - eccsteps) * eccbytes), 0);
		if (stat == -1)
			mtd->ecc_stats.failed++;

		col = eccsize * (chip->ecc.steps + 1 - eccsteps);	/* 512*(4 + 1 - [4,3,2,1]) */
	}
	
	return 0;
}


/* ecc.size：每一次硬件ECC所检验的字节个数 */
/* ecc.bytes：每一次硬件ECC所生成的字节个数 */
/* ecc.steps：每一页需要进行硬件ECC的次数 */
static void s3c2440_nand_write_page_1bit(struct mtd_info *mtd, struct nand_chip *chip,
				  const uint8_t *buf)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	int secc_start = mtd->oobsize - eccbytes;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	const uint8_t *p = buf;
	
	uint32_t *eccpos = chip->ecc.layout->eccpos;

//	debug("s3c2440_nand_write_page_1bit\r\n");

	/* main area */
	/* 每一次硬件能校验的字节数ecc.size = 512 */
	/* 每一次硬件ECC所生成的字节个数ecc.bytes = 4 */
	/* eccsteps = 2048 / 512 = 4 */
	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) 
	{
		chip->ecc.hwctl(mtd, NAND_ECC_WRITE);
		chip->write_buf(mtd, p, eccsize);	/* 512 */
		chip->ecc.calculate(mtd, p, &ecc_calc[i]);
	}

	for (i = 0; i < chip->ecc.total; i++)	/* ecc.total应该等于ecc.bytes * eccsteps = 4 * 4 = 16 */
		chip->oob_poi[eccpos[i]] = ecc_calc[i];/* eccpos[0]=40，从spare area的第40字节开始存16字节的main area的ECC */

	/* spare area */
	chip->ecc.hwctl(mtd, NAND_ECC_WRITE);
//	debug("eccpos[0] = %d\r\n", eccpos[0]);
//	debug("secc_start = %d\r\n", secc_start);
	chip->write_buf(mtd, chip->oob_poi, secc_start);	/* 在main area之后的区域(OOB区)继续写60字节，*/
												/* 把main area的ecc写入spare area, 长度是secc_start=64-4=60 */
	chip->ecc.calculate(mtd, p, &ecc_calc[chip->ecc.total]);	/* 计算spare area的ecc， 4字节 */

	/* 写入4字节，在OOB区域第60到第63字节写入OOB前60字节的ECC, secc_start = 60 */
	for (i = 0; i < eccbytes; i++)
		chip->oob_poi[secc_start + i] = ecc_calc[chip->ecc.total + i];

	chip->write_buf(mtd, chip->oob_poi + secc_start, eccbytes);
}

static int s3c2440_nand_read_oob_1bit(struct mtd_info *mtd, struct nand_chip *chip,
			     int page, int sndcmd)
{
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	int eccbytes = chip->ecc.bytes;		/* 4 */
	int secc_start = mtd->oobsize - eccbytes;	/* 64 - 4 = 60 */

//	debug("s3c2440_nand_read_oob_1bit\r\n");
	
	if (sndcmd) 	/* 发送读OOB指令，实际在nand_command_lp()中发送READ指令，列地址2048 */
	{
//		debug("chip->cmdfunc(), page = %08x\r\n", page);
		chip->cmdfunc(mtd, NAND_CMD_READOOB, 0, page);
		sndcmd = 0;
	}

	chip->ecc.hwctl(mtd, NAND_ECC_READ);			/* 初始化硬件ECC */
	chip->read_buf(mtd, chip->oob_poi, secc_start);	/* 读取60字节到chip->oob_poi */
	chip->ecc.calculate(mtd, 0, &ecc_calc[chip->ecc.total]);	/* 计算60字节的4字节ECC，保存到ecc_calc[16]开始的4字节 */
	chip->read_buf(mtd, chip->oob_poi + secc_start, eccbytes);	/* 读取OOB中剩余4字节字节到oob_poi[60]开始的4字节 */

	/* jffs2 special case */
	if (!(chip->oob_poi[2] == 0x85 && chip->oob_poi[3] == 0x19))
		chip->ecc.correct(mtd, chip->oob_poi, chip->oob_poi + secc_start, 0);
	
	return sndcmd;
}


static int s3c2440_nand_write_oob_1bit(struct mtd_info *mtd, struct nand_chip *chip,
			      int page)
{
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	int status = 0;
	int eccbytes = chip->ecc.bytes;		/* 4 */
	int secc_start = mtd->oobsize - eccbytes;	/* 64 - 4 = 60 */
	int i;

//	debug("s3c2440_nand_write_oob_1bit\r\n");

	chip->cmdfunc(mtd, NAND_CMD_SEQIN, mtd->writesize, page);

	/* spare area */
	chip->ecc.hwctl(mtd, NAND_ECC_WRITE);		/* 初始化硬件ECC */
	chip->write_buf(mtd, chip->oob_poi, secc_start);	/* 写入60字节 */
	chip->ecc.calculate(mtd, 0, &ecc_calc[chip->ecc.total]);	/* 计算出前60字节的4字节ECC，写入到ecc_calc[16]开始的4字节 */

	for (i = 0; i < eccbytes; i++)	/* 复制4字节ECC到写缓冲区 */
		chip->oob_poi[secc_start + i] = ecc_calc[chip->ecc.total + i];

	chip->write_buf(mtd, chip->oob_poi + secc_start, eccbytes);	/* 写入spare area前60字节的4字节ECC到spare area剩下的4字节 */

	/* Send command to program the OOB data */
	chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);

	status = chip->waitfunc(mtd, chip);		/* 调用nand_base.c中nand_wait()等待nfstat & 0x01 == 0x01 */

	return status & NAND_STATUS_FAIL ? -EIO : 0;
}




#endif


int board_nand_init(struct nand_chip *nand)
{
	u_int32_t cfg;
	u_int8_t tacls, twrph0, twrph1;
	/* S3C2416不需要 */
//	struct s3c24x0_clock_power *clk_power = s3c24x0_get_base_clock_power();
	struct s3c2440_nand *nand_reg = s3c2440_get_base_nand();
#if defined(CONFIG_S3C2440_NAND_HWECC)
	int i;
	u_char tmp;
	u_char maf_id;
	u_char device_id;
	struct nand_flash_dev *type = NULL;
#endif

	debug("board_nand_init()\n");

	/* S3C2416不需要 */
//	writel(readl(&clk_power->clkcon) | (1 << 4), &clk_power->clkcon);

	/* 判断是否是NAND启动 */
	if (readl(&nand_reg->nfconf) & 0x80000000)
	{
		boot_nand = 1;
		debug("booting from nand\r\n");
	}
	else
	{
		boot_nand = 0;
		debug("not booting from nand\r\n");
	}

	/* initialize hardware */
#if defined(CONFIG_S3C24XX_CUSTOM_NAND_TIMING)
	tacls  = CONFIG_S3C24XX_TACLS;
	twrph0 = CONFIG_S3C24XX_TWRPH0;
	twrph1 =  CONFIG_S3C24XX_TWRPH1;
#else
	tacls = 0x07;
	twrph0 = 0x07;
	twrph1 = 0x07;
#endif

#if 0
	cfg = S3C2410_NFCONF_EN;
	cfg |= S3C2410_NFCONF_TACLS(tacls - 1);
	cfg |= S3C2410_NFCONF_TWRPH0(twrph0 - 1);
	cfg |= S3C2410_NFCONF_TWRPH1(twrph1 - 1);
#endif
	/* 初始化时序 */
	cfg = (tacls<<12)|(twrph0<<8)|(twrph1<<4);
	writel(cfg, &nand_reg->nfconf);

	/* 使能NAND Flash控制器, 初始化ECC, 禁止片选 */
//	writel((1<<4)|(1<<1)|(1<<0), &nand_reg->nfcont);
	/* 使能NAND Flash控制器, 关闭ECC, 禁止片选 */
	writel((1<<1)|(1<<0), &nand_reg->nfcont);
	
	/* initialize nand_chip data structure */
	nand->IO_ADDR_R = (void *)&nand_reg->nfdata;
	nand->IO_ADDR_W = (void *)&nand_reg->nfdata;

	nand->select_chip = s3c2440_nand_select;

	/* read_buf and write_buf are default */
	/* read_byte and write_byte are default */
#ifdef CONFIG_NAND_SPL
	nand->read_buf = nand_read_buf;
#endif

	/* hwcontrol always must be implemented */
	nand->cmd_ctrl = s3c2440_hwcontrol;
	nand->dev_ready = s3c2440_dev_ready;
	nand->scan_bbt = s3c2440_nand_scan_bbt;	/* 从helper2416复制过来的，2012.04.01本来没有 */
	nand->options = 0;						/* 从helper2416复制过来的，2012.04.01本来没有 */

//	nand->options |= NAND_SKIP_BBTSCAN;		/*  */
		
#ifdef CONFIG_S3C2440_NAND_HWECC
	nand->ecc.hwctl = s3c2440_nand_enable_hwecc;
	nand->ecc.calculate = s3c2440_nand_calculate_ecc;
	nand->ecc.correct = s3c2440_nand_correct_data;
	nand->ecc.mode = NAND_ECC_HW;

	/* 这两个值在下面读取ID后确定 */
//	nand->ecc.size = CONFIG_SYS_NAND_ECCSIZE;
//	nand->ecc.bytes = CONFIG_SYS_NAND_ECCBYTES;

	/* 发出READ ID命令，并读取4字节 */
	s3c2440_hwcontrol(0, NAND_CMD_READID, NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
//	s3c2440_hwcontrol(0, 0x00, NAND_CTRL_CHANGE | NAND_NCE | NAND_ALE);
	s3c2440_hwcontrol(0, 0x00, NAND_NCE | NAND_ALE);
//	s3c2440_hwcontrol(0, NAND_CMD_NONE, NAND_NCE | NAND_CTRL_CHANGE);
	s3c2440_dev_ready(0);

	maf_id = readb(nand->IO_ADDR_R); /* Maf. ID */
	device_id= readb(nand->IO_ADDR_R); /* Device ID */

	debug("Maf. ID = %x\r\n", maf_id);
	debug("Device ID = %x\r\n", device_id);

	debug("nand_flash_ids %08x\r\n", nand_flash_ids);
	/* 在列表中查找当前nandflash,列表在z:\home\wu\workspace\u-boot-2012.04.01\drivers\mtd\nand\Nand_ids.c */
	for (i = 0; nand_flash_ids[i].name != NULL; i++) {
		if (device_id == nand_flash_ids[i].id) {
			type = &nand_flash_ids[i];
			break;
		}
	}

	nand->cellinfo = readb(nand->IO_ADDR_R);	/* 3rd byte */
	tmp = readb(nand->IO_ADDR_R);			/* 4th byte */
	s3c2440_hwcontrol(0, NAND_CMD_NONE, 0);	/* 取消选中 */

	debug("3rd byte = %x\r\n", nand->cellinfo);
	debug("4th byte = %x\r\n", tmp);

	debug("K9F2G08 1 %08x\r\n", type);
	if (!type->pagesize) 
	{
		if (((nand->cellinfo >> 2) & 0x3) == 0) 
		{		
			/* K9F2G08 */
			nand_type = S3C_NAND_TYPE_SLC;
			/* ecc.size：每一次硬件ECC所检验的字节个数 */
			/* ecc.bytes：每一次硬件ECC所生成的字节个数 */
			/* ecc.steps：每一页需要进行硬件ECC的次数 */
			nand->ecc.size = 512;
			nand->ecc.bytes	= 4;
			
			if ((1024 << (tmp & 0x3)) > 512) 	/* Page Size > 512, K9F2G08  */
			{
				debug("K9F2G08 2\r\n");
				nand->ecc.read_page = s3c2440_nand_read_page_1bit;
				nand->ecc.write_page = s3c2440_nand_write_page_1bit;
				nand->ecc.read_oob = s3c2440_nand_read_oob_1bit;
				nand->ecc.write_oob = s3c2440_nand_write_oob_1bit;
				nand->ecc.layout = &s3c_nand_oob_64;
			} 
			else 
			{
//				nand->ecc.layout = &s3c_nand_oob_16;
			}
		} 
		else 
		{
			nand_type = S3C_NAND_TYPE_MLC;
			nand->options |= NAND_NO_SUBPAGE_WRITE;	/* NOP = 1 if MLC */
//			nand->ecc.read_page = s3c_nand_read_page_4bit;
//			nand->ecc.write_page = s3c_nand_write_page_4bit;
			nand->ecc.size = 512;
			nand->ecc.bytes = 8;	/* really 7 bytes */
//			nand->ecc.layout = &s3c_nand_oob_mlc_64;
		}
	} 
	else 
	{
		nand_type = S3C_NAND_TYPE_SLC;
		nand->ecc.size = 512;
		nand->cellinfo = 0;
		nand->ecc.bytes = 4;
//		nand->ecc.layout = &s3c_nand_oob_16;
	}
#else
	nand->ecc.mode = NAND_ECC_SOFT;
#endif

#ifdef CONFIG_S3C2410_NAND_BBT
	nand->options = NAND_USE_FLASH_BBT;
#else
	nand->options = 0;
#endif

	debug("end of board_nand_init\n");

	return 0;
}
