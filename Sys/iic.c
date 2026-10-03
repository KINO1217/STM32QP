/**
 * @file iic.c
 * @brief I2C通信接口源文件
 * @author KINO电子工作室
 * @date 2026/10/02
 */
#include "iic.h"
#include <stdlib.h>

void IIC_DELAY_5Us(void);

c_iic IIC_Create(GPIO_TypeDef *scl_port, uint16_t scl_pin, GPIO_TypeDef *sda_port, uint16_t sda_pin)
{
    c_iic *new;
    GPIO_InitTypeDef GPIO_InitStructure;

    new = (c_iic *)malloc(sizeof(c_iic));
    new->SCL_Port = scl_port;
    new->SCL_Pin = scl_pin;
    new->SDA_Port = sda_port;
    new->SDA_Pin = sda_pin;

    // 配置SCL引脚
    GPIO_InitStructure.GPIO_Pin = scl_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(scl_port, &GPIO_InitStructure);

    // 配置SDA引脚
    GPIO_InitStructure.GPIO_Pin = sda_pin;
    GPIO_Init(sda_port, &GPIO_InitStructure);

    return *new;
}

void IIC_DELAY_5Us(void)
{
    uint8_t i = 50;
    while (i--)
    {
        __NOP();
    }
}

void IIC_Start(c_iic *this)
{
    GPIO_WriteBit(this->SDA_Port, this->SDA_Pin, Bit_SET);
    GPIO_WriteBit(this->SCL_Port, this->SCL_Pin, Bit_SET);
    IIC_DELAY_5Us();
    GPIO_WriteBit(this->SDA_Port, this->SDA_Pin, Bit_RESET);
    IIC_DELAY_5Us();
    GPIO_WriteBit(this->SCL_Port, this->SCL_Pin, Bit_RESET);
    IIC_DELAY_5Us();
}

void IIC_Stop(c_iic *this)
{
    GPIO_WriteBit(this->SDA_Port, this->SDA_Pin, Bit_RESET);
    GPIO_WriteBit(this->SCL_Port, this->SCL_Pin, Bit_SET);
    IIC_DELAY_5Us();
    GPIO_WriteBit(this->SDA_Port, this->SDA_Pin, Bit_SET);
    IIC_DELAY_5Us();
}

void IIC_SendByte(c_iic *this, uint8_t datas)
{
    uint8_t i = 0;

    for (i = 0; i < 8; i++)
    {
        if ((datas << i) & 0x80)
            GPIO_WriteBit(this->SDA_Port, this->SDA_Pin, Bit_SET);
        else
            GPIO_WriteBit(this->SDA_Port, this->SDA_Pin, Bit_RESET);
        IIC_DELAY_5Us();
        GPIO_WriteBit(this->SCL_Port, this->SCL_Pin, Bit_SET);
        IIC_DELAY_5Us();
        GPIO_WriteBit(this->SCL_Port, this->SCL_Pin, Bit_RESET);
        IIC_DELAY_5Us();
    }
}

uint8_t IIC_ReadByte(c_iic *this)
{
    uint8_t i = 0;
    uint8_t datas = 0;

    GPIO_WriteBit(this->SDA_Port, this->SDA_Pin, Bit_SET); // 释放SDA线
    for (i = 0; i < 8; i++)
    {
        datas <<= 1;
        GPIO_WriteBit(this->SCL_Port, this->SCL_Pin, Bit_SET);
        IIC_DELAY_5Us();
        if (GPIO_ReadInputDataBit(this->SDA_Port, this->SDA_Pin))
            datas |= 0x01;
        IIC_DELAY_5Us();
        GPIO_WriteBit(this->SCL_Port, this->SCL_Pin, Bit_RESET);
        IIC_DELAY_5Us();
    }

    return datas;
}

void IIC_SendAck(c_iic *this, uint8_t ack)
{
    GPIO_WriteBit(this->SDA_Port, this->SDA_Pin, ack ? Bit_SET : Bit_RESET);
    IIC_DELAY_5Us();
    GPIO_WriteBit(this->SCL_Port, this->SCL_Pin, Bit_SET);
    IIC_DELAY_5Us();
    GPIO_WriteBit(this->SCL_Port, this->SCL_Pin, Bit_RESET);
    IIC_DELAY_5Us();
}

uint8_t IIC_CheckAck(c_iic *this)
{
    uint8_t ack;

    GPIO_WriteBit(this->SDA_Port, this->SDA_Pin, Bit_SET); // 释放SDA线
    IIC_DELAY_5Us();
    GPIO_WriteBit(this->SCL_Port, this->SCL_Pin, Bit_SET);
    IIC_DELAY_5Us();
    ack = GPIO_ReadInputDataBit(this->SDA_Port, this->SDA_Pin);
    IIC_DELAY_5Us();
    GPIO_WriteBit(this->SCL_Port, this->SCL_Pin, Bit_RESET);
    IIC_DELAY_5Us();

    return ack;
}
