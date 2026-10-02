/**
 * @file switch.h
 * @brief 开关头文件
 * @author KINO电子工作室
 * @date 2026/10/02
 */

/**
 * 使用方法：
 * c_switch led = {0};
 * led = SWITCH_Create(GPIOC, GPIO_Pin_13); // 创建开关对象
 * SWITCH_Toggle(&led, SW_HIGH); // 设置开关为高电平
 * SWITCH_Toggle(&led, SW_LOW); // 设置开关为低电平
 */

#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "stm32f10x.h"

typedef struct
{
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
} c_switch;

typedef enum
{
    SW_LOW = 0,
    SW_HIGH
} switch_state;

c_switch SWITCH_Create(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void SWITCH_Toggle(c_switch *this, switch_state state);

#endif
