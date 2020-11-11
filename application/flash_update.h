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

#ifndef		FLASH_UPDATE__H_
#define		FLASH_UPDATE__H_


#define		LED_ON()
#define		LED_OFF()
#define		LED_TOG()


#define		APP_FW_INFO_ADDR			(0x00003000)
#define		APP_FW_START_ADDR			(0x00003200)
#define		APP_FW_FLASH_SIZE			(1024*40)
typedef		void (*pFun)(void);


//=======================================
extern uint32_t UpdateAppCodeStart(uint8_t *filename,uint32_t filesize);
extern uint32_t UpdateAppCode(uint8_t *buff);
extern uint32_t UpdateAppCodeEnd(uint8_t *buff, uint32_t len);

#endif	//	



