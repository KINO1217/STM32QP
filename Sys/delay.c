/**
 * @file delay.c
 * @brief 滴答定时器延时源文件
 * @author KINO电子工作室
 * @date 2026/10/02
 */
#include "delay.h"

void DELAY_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // 选择外部时钟源 HCLK/8
}

void DELAY_Us(uint32_t nus)
{
    u32 temp = 0x00;

    SysTick->LOAD = nus * 9;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
}

void DELAY_Ms(uint16_t nms)
{
    u32 temp = 0x00;

    SysTick->LOAD = nms * 9000;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
}
