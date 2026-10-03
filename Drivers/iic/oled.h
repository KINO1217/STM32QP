/**
 * @file oled.h
 * @brief OLED显示驱动头文件
 * @author KINO电子工作室
 * @date 2026/10/02
 */
#ifndef __OLED_H__
#define __OLED_H__

#include "stm32f10x.h"
#include "iic.h"

void OLED_Init(c_iic *iic);
void OLED_Clear(c_iic *iic);
void OLED_On(c_iic *iic);
void OLED_Off(c_iic *iic);
void OLED_SetPos(c_iic *iic, uint8_t row, uint8_t col);
void OLED_ShowChar(c_iic *iic, uint8_t row, uint8_t col, char ch);
void OLED_ShowString(c_iic *iic, uint8_t row, uint8_t col, const char *str, ...);
void OLED_ShowChinese(c_iic *iic, uint8_t row, uint8_t col, const char *str);
void OLED_ShowChineses(c_iic *iic, uint8_t row, uint8_t col, const char *str);

#endif
