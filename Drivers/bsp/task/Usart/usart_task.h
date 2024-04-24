//
// Created by 15368 on 2024/3/25.
//

#ifndef V2_USART_H
#define V2_USART_H

#include "main.h"

#define USART_REC_LEN  	50
#define END_FLAG ('X')


extern uint8_t usart1_rec;
extern uint8_t usart1_recbuf[USART_REC_LEN];
extern uint8_t usart6_rec;
extern uint8_t usart6_recbuf[USART_REC_LEN];


extern TaskHandle_t USART1_Task_Handler;

void USART1_Task(void *pvParameters);

//获取字符串中的整数
void extractNumbers(const char *data, int *numbers, int size);

//获取字符串中的浮点数
void extractFloats(const char *data, float *floats, int size);

#endif //V2_USART_H
