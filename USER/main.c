#include "main.h"

int main()
{
    // 硬件初始化
    RCC_CONFIG(); // 初始化时钟
    DELAY_Init(); // 初始化滴答定时器

    // 模块初始化

    while (1)
    {
    }
}

void RCC_CONFIG(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                               RCC_APB2Periph_GPIOB |
                               RCC_APB2Periph_GPIOC,
                           ENABLE);
}
