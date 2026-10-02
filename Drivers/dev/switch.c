/**
 * @file switch.c
 * @brief 开关源文件
 * @author KINO电子工作室
 * @date 2026/10/02
 */
#include "switch.h"
#include <stdlib.h>

c_switch SWITCH_Create(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    c_switch *new;
    GPIO_InitTypeDef GPIO_InitStructure;

    new = (c_switch *)malloc(sizeof(c_switch));
    new->GPIOx = GPIOx;
    new->GPIO_Pin = GPIO_Pin;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出模式
    GPIO_Init(GPIOx, &GPIO_InitStructure);           // 初始化 GPIO

    return *new;
}

void SWITCH_Toggle(c_switch *this, switch_state state)
{
    GPIO_WriteBit(this->GPIOx, this->GPIO_Pin, (BitAction)state);
}
