#include "ddl.h"

#define APP_FW_START_ADDR 0x00004000    //APP 起始地址

typedef void (*pFun)(void);
void jumpToApp(uint32_t addr)
{
    uint32_t *pData = (uint32_t *)(addr);
    //if((*pData > 0x20000000) && (*pData < 0x20008000))
    if(((*(uint32_t*)addr)&0x2FFE0000)==0x20000000)             // 检查栈顶地址是否合法
    {
        pFun jumpFun = (pFun) * (__IO uint32_t *)(addr + 4);    // 用户代码区的第二个字为程序开始地址(复位地址)
        __set_MSP(*(__IO uint32_t *)(addr));                    // 初始化 APP 堆栈指针(用户代码区的第一个字用于存放栈顶地址)
        jumpFun();                                              // 跳转到 APP
    }
}

int32_t main(void)
{
    jumpToApp(APP_FW_START_ADDR);
    while (1);
}
