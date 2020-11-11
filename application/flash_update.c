/*
///////////////////////////////////////////////////////////////////////////////
//文件名：		flash_update.c
//作者：		WoodData
//创建日期：	2019/08 
//备注功能：	
//
//
//修改记录：
//版本		日期		修改功能描述
//1：	
//
///////////////////////////////////////////////////////////////////////////////
*/

#include "hc32l19x.h"
#include "system_hc32l19x.h"
#include "flash.h"
#include "flash_update.h"

static uint32_t AppcodeCurAddr;

//////////////////////////////////////////////////////////////
void FLASH_Write(uint32_t addr, uint32_t byte)
{
	Flash_WriteWord(addr&(~0x0003),byte);
}

uint8_t FLASH_Read (uint32_t addr)
{
	uint32_t	* pdat;
	pdat = (uint32_t *)addr;
	return *pdat;
}

void FLASH_PageErase (uint32_t addr)
{
	Flash_SectorErase(addr);
}

void FLASH_PageWrite (uint32_t addr,uint8_t *buff,uint32_t len)
{
	uint32_t i,addr0;
	uint32_t *dat;

	addr0 = addr & (~0x1ff);	
	for(i=0;i<len;i+=4)		//page=512byte
	{
		dat = (uint32_t *)(buff+i);
		FLASH_Write(addr0,*dat);
		addr0 += 4;
	}
}



//////////////////////////////////////////////////////////////////
uint32_t UpdateAppCodeStart(uint8_t *filename, uint32_t filesize)
{
	AppcodeCurAddr = APP_FW_START_ADDR;
	if(filesize > APP_FW_FLASH_SIZE)
	{
		return 1;			
	}	
	FLASH_PageErase(APP_FW_START_ADDR - 4);
	LED_ON();
	return 0;	
}


uint32_t UpdateAppCode(uint8_t *buff)
{
	uint32_t i;

	FLASH_PageErase(AppcodeCurAddr);
	LED_ON();	
		
	FLASH_PageWrite(AppcodeCurAddr, buff,512);	
	
	for(i=0;i<512;i++)
	{
		if(buff[i] != FLASH_Read(AppcodeCurAddr ++))
		{
			return 1;
		}
	}
	LED_OFF();
	
	return 0;	
}


uint32_t UpdateAppCodeEnd(uint8_t *buff, uint32_t len)
{
	uint32_t i;

	if(len)
	{		
		FLASH_PageErase(AppcodeCurAddr);	
		
		LED_ON();	

		FLASH_PageWrite(AppcodeCurAddr, buff, len);
		
		for(i=0;i<len;i++)
		{
			if(buff[i] != FLASH_Read(AppcodeCurAddr ++))
			{
				return 1;
			}
		}
	}	
		
	FLASH_Write(APP_FW_START_ADDR - 4,0xAA55A55A);	//结束标志
	
	LED_OFF();
	
	return 0;
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
