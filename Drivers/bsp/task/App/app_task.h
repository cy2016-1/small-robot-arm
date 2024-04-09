//
// Created by 15368 on 2024/3/5.
//

#ifndef __APP_TASK_H
#define __APP_TASK_H

#include "main.h"

extern TaskHandle_t OLED_Task_Handler;


void OLED_Task(void *pvParameters);

void App_Init_Task_Init(void);
void App_Run_Task_Init(void);
void App_Init_Task_Deinit(void);



#endif //__APP_TASK_H
