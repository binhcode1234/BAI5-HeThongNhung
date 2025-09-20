#include "stm32f10x.h"
#include <string.h>
#include <stdio.h>

void UART1_Init(void);
void GPIO_Init_LED(void);
void UART1_SendChar(char c);
void UART1_SendString(char *str);
char UART1_GetChar(void);

int main(void)
{
    char rxBuffer[10];
    int index = 0;

    SystemInit();
    UART1_Init();
    GPIO_Init_LED();

    UART1_SendString("Hello from STM32!\r\n");

    while (1)
    {
        char c = UART1_GetChar();   // nh?n 1 ký t? t? máy tính
        UART1_SendChar(c);          // g?i tr? l?i ký t? dó (echo)

        if (c == '\r' || c == '\n') // n?u nh?n Enter thì x? lý chu?i
        {
            rxBuffer[index] = '\0'; // k?t thúc chu?i

            if (strcmp(rxBuffer, "ON") == 0)
            {
                GPIO_SetBits(GPIOB, GPIO_Pin_12);  // b?t LED
                UART1_SendString("\r\nLED ON\r\n");
            }
            else if (strcmp(rxBuffer, "OFF") == 0)
            {
                GPIO_ResetBits(GPIOB, GPIO_Pin_12); // t?t LED
                UART1_SendString("\r\nLED OFF\r\n");
            }
            else if (index > 0)
            {
                UART1_SendString("\r\nERROR: Invalid command!\r\n");
            }

            index = 0; // reset b? d?m
        }
        else
        {
            if (index < sizeof(rxBuffer) - 1)
            {
                rxBuffer[index++] = c;
            }
        }
    }
}

void UART1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    // B?t clock GPIOA, USART1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    // PA9 (TX) - Alternate function push-pull
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA10 (RX) - Input floating
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // C?u hình USART1
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStruct);

    USART_Cmd(USART1, ENABLE);
}

void GPIO_Init_LED(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_ResetBits(GPIOB, GPIO_Pin_12); // m?c d?nh t?t LED
}

void UART1_SendChar(char c)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, c);
}

void UART1_SendString(char *str)
{
    while (*str)
    {
        UART1_SendChar(*str++);
    }
}

char UART1_GetChar(void)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return USART_ReceiveData(USART1);
}
