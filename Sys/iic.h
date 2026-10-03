/**
 * @file iic.h
 * @brief I2C通信接口头文件
 * @author KINO电子工作室
 * @date 2026/10/02
 */

#ifndef __IIC_H__
#define __IIC_H__

#include "stm32f10x.h"

typedef struct
{
    GPIO_TypeDef *SCL_Port; // SCL端口
    uint16_t SCL_Pin;       // SCL引脚
    GPIO_TypeDef *SDA_Port; // SDA端口
    uint16_t SDA_Pin;       // SDA引脚
} c_iic;

c_iic IIC_Create(GPIO_TypeDef *scl_port, uint16_t scl_pin, GPIO_TypeDef *sda_port, uint16_t sda_pin);
void IIC_Start(c_iic *this);
void IIC_Stop(c_iic *this);
void IIC_SendByte(c_iic *this, uint8_t datas);
uint8_t IIC_ReadByte(c_iic *this);
void IIC_SendAck(c_iic *this, uint8_t ack);
uint8_t IIC_CheckAck(c_iic *this);

#endif
