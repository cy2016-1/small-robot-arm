//
// Created by 15368 on 2024/3/5.
//

#ifndef __APP_TASK_H
#define __APP_TASK_H

#include "main.h"

extern TaskHandle_t OLED_Task_Handler;
extern TaskHandle_t App_Run_Task_Init_Handle;
extern TaskHandle_t Camer_Snapshot_Task_Handle;




void OLED_Task(void *pvParameters);

void Camer_TimerCallback(TimerHandle_t pxTimer);

void App_Init_Task_Init(void);
void App_Run_Task_Init(void *pvParameters);


#endif //__APP_TASK_H
