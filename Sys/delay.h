/**
 * @file delay.h
 * @brief 滴答定时器延时头文件
 * @author KINO电子工作室
 * @date 2026/10/02
 */
#ifndef __DELAY_H__
#define __DELAY_H__

#include "stm32f10x.h"

void DELAY_Init(void);
void DELAY_Us(uint32_t nus);
void DELAY_Ms(uint16_t nms);

#endif
