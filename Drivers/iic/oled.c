/**
 * @file iic.c
 * @brief I2C通信接口源文件
 * @author KINO电子工作室
 * @date 2026/10/02
 */
#include "oled.h"
#include "oled_font.h"
#include "stdarg.h"
#include "stdio.h"

void OLED_WriteCmd(c_iic *iic, uint8_t cmds);
void OLED_WriteData(c_iic *iic, uint8_t datas);

void OLED_Init(c_iic *iic)
{
    uint32_t i = 0;

    i = 720000;
    while (i--)
        ;

    OLED_WriteCmd(iic, 0xA8);
    OLED_WriteCmd(iic, 0x3F);
    OLED_WriteCmd(iic, 0xDA);
    OLED_WriteCmd(iic, 0x12);
    OLED_WriteCmd(iic, 0xD3);
    OLED_WriteCmd(iic, 0x00);
    OLED_WriteCmd(iic, 0x40);
    OLED_WriteCmd(iic, 0xA1);
    OLED_WriteCmd(iic, 0x81);
    OLED_WriteCmd(iic, 0xFF);
    OLED_WriteCmd(iic, 0xA4);
    OLED_WriteCmd(iic, 0xA6);
    OLED_WriteCmd(iic, 0x8D);
    OLED_WriteCmd(iic, 0x14);
    OLED_WriteCmd(iic, 0x20);
    OLED_WriteCmd(iic, 0x02);
    OLED_WriteCmd(iic, 0xC8);
    OLED_WriteCmd(iic, 0xB0);
    OLED_WriteCmd(iic, 0x00);
    OLED_WriteCmd(iic, 0x10);
    OLED_WriteCmd(iic, 0xD9);
    OLED_WriteCmd(iic, 0x22);
    OLED_WriteCmd(iic, 0xDB);
    OLED_WriteCmd(iic, 0x20);
    OLED_WriteCmd(iic, 0xAF);
}

void OLED_WriteCmd(c_iic *iic, uint8_t cmds)
{
    IIC_Start(iic);
    IIC_SendByte(iic, 0x78);
    IIC_CheckAck(iic);
    IIC_SendByte(iic, 0x00);
    IIC_CheckAck(iic);
    IIC_SendByte(iic, cmds);
    IIC_CheckAck(iic);
    IIC_Stop(iic);
}

void OLED_WriteData(c_iic *iic, uint8_t datas)
{
    IIC_Start(iic);
    IIC_SendByte(iic, 0x78);
    IIC_CheckAck(iic);
    IIC_SendByte(iic, 0x40);
    IIC_CheckAck(iic);
    IIC_SendByte(iic, datas);
    IIC_CheckAck(iic);
    IIC_Stop(iic);
}

void OLED_Clear(c_iic *iic)
{
    uint8_t i, j;

    for (i = 0; i < 8; i++)
    {
        OLED_WriteCmd(iic, 0xB0 + i);
        OLED_WriteCmd(iic, 0x00);
        OLED_WriteCmd(iic, 0x10);
        for (j = 0; j < 128; j++)
        {
            OLED_WriteData(iic, 0x00);
        }
    }
}

void OLED_On(c_iic *iic)
{
    OLED_WriteCmd(iic, 0x8D);
    OLED_WriteCmd(iic, 0x14);
    OLED_WriteCmd(iic, 0xAF);
}

void OLED_Off(c_iic *iic)
{
    OLED_WriteCmd(iic, 0x8D);
    OLED_WriteCmd(iic, 0x10);
    OLED_WriteCmd(iic, 0xAE);
}

void OLED_SetPos(c_iic *iic, uint8_t row, uint8_t col)
{
    OLED_WriteCmd(iic, 0xB0 + row);
    OLED_WriteCmd(iic, 0x00 + (col & 0x0F));
    OLED_WriteCmd(iic, 0x10 + ((col >> 4) & 0x0F));
}

void OLED_ShowChar(c_iic *iic, uint8_t row, uint8_t col, char ch)
{
    uint8_t index = 0;
    uint8_t i = 0;

    if (col > 127 || row > 7)
        return;

    index = ch - ' ';

    OLED_SetPos(iic, row, col);
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(iic, cFont8X16[index][i]);
    }

    OLED_SetPos(iic, row + 1, col);
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(iic, cFont8X16[index][i + 8]);
    }
}

void OLED_ShowString(c_iic *iic, uint8_t row, uint8_t col, const char *str, ...)
{
    char newStr[16] = {0};
    uint8_t len = 0;

    va_list vaList;
    va_start(vaList, str);
    vsprintf((char *)newStr, (char *)str, vaList);
    va_end(vaList); // 拼接字符串

    while (newStr[len] != '\0')
    {
        OLED_ShowChar(iic, row, col, newStr[len]);
        col += 8;
        if (col > 120)
        {
            col = col % 128;
            row += 2;
        }
        len++;
    }
}

void OLED_ShowChinese(c_iic *iic, uint8_t row, uint8_t col, const char *str)
{
    uint8_t hzSum = 0;
    uint8_t index = 0;
    uint8_t i = 0;

    if (col > 127 || row > 7)
        return;

    hzSum = sizeof(Hz_Table) / sizeof(Hz_Struct); // 计算汉字库数量

    for (index = 0; index < hzSum; index++)
    { // 查找汉字位置
        if (str[0] == Hz_Table[index].Hz[0] && str[1] == Hz_Table[index].Hz[1])
        {
            break;
        }
    }

    if (index >= hzSum)
        return; // 未找到汉字

    OLED_SetPos(iic, row, col);
    for (i = 0; i < 16; i++)
    {
        OLED_WriteData(iic, Hz_Table[index].HzCode[i]);
    }

    OLED_SetPos(iic, row + 1, col);
    for (i = 0; i < 16; i++)
    {
        OLED_WriteData(iic, Hz_Table[index].HzCode[i + 16]);
    }
}

void OLED_ShowChineses(c_iic *iic, uint8_t row, uint8_t col, const char *str)
{
    char newStr[2] = {0};
    uint8_t index = 0;

    while (str[index] != '\0')
    {
        newStr[0] = str[index];
        newStr[1] = str[index + 1];
        index += 2;
        OLED_ShowChinese(iic, row, col, newStr);
        col += 16;
        if (col > 127)
        {
            row += 2;
            col = col % 128;
        }
    }
}
