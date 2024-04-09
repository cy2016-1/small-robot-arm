//
// Created by 15368 on 2024/3/5.
//
#include "app_task.h"
#include "motor_task.h"
#include "usart_task.h"

TaskHandle_t OLED_Task_Handler  = NULL;

void OLED_Task(void *pvParameters)
{

  TickType_t TickCount = xTaskGetTickCount();
  u8g2_t u8g2; // 显示器初始化结构体
  u8g2Init(&u8g2);   //显示器调用初始化函数

  uint8_t oled_buf[50];

  u8g2_SetFontDirection(&u8g2, 0); 				//字体方向选择
  u8g2_SetFont(&u8g2, u8g2_font_inb16_mf); //字库选择
  u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);  //设定字体大小

  for(;;)
  {
    u8g2_ClearBuffer(&u8g2);//先清除缓存
    for(int i = 0;i<6;i++)
    {

      sprintf((char*)oled_buf,"tar[%d]=%d S:%d\r\n",i+1,Motor[i+1].target_pulse,Motor[i+1].speed);
      u8g2_DrawStr(&u8g2, 0, 10+10*i, oled_buf);//在屏幕上显示

    }
    u8g2_SendBuffer(&u8g2);//刷新屏幕

    vTaskDelayUntil(&TickCount, pdMS_TO_TICKS(100));
  }
}



void App_Init_Task_Init(void)
{
  //创建电机初始化任务
  xTaskCreate(Motor1_Init_Task, "Motor1_Init_Task", 128, NULL, 3, &Motor1_Init_Task_Handle);
//  xTaskCreate(Motor2_Init_Task, "Motor2_Init_Task", 128, NULL, 3, &Motor2_Init_Task_Handle);
//  xTaskCreate(Motor3_Init_Task, "Motor3_Init_Task", 128, NULL, 3, &Motor3_Init_Task_Handle);
//  xTaskCreate(Motor4_Init_Task, "Motor4_Init_Task", 128, NULL, 3, &Motor4_Init_Task_Handle);
//  xTaskCreate(Motor5_Init_Task, "Motor5_Init_Task", 256, NULL, 3, &Motor5_Init_Task_Handle);
//  xTaskCreate(Motor6_Init_Task, "Motor6_Init_Task", 128, NULL, 3, &Motor6_Init_Task_Handle);

}

void App_Init_Task_Deinit(void)
{
  //删除初始化任务
  vTaskDelete(Motor1_Init_Task_Handle);
  vTaskDelete(Motor2_Init_Task_Handle);
  vTaskDelete(Motor3_Init_Task_Handle);
  vTaskDelete(Motor4_Init_Task_Handle);
  vTaskDelete(Motor5_Init_Task_Handle);
  vTaskDelete(Motor6_Init_Task_Handle);

  //创建app任务
//  App_Run_Task_Init();

}

void App_Run_Task_Init(void)
{
  //创建USART1任务
  xTaskCreate(USART1_Task, "USART1_Task", 512, NULL, 3, &USART1_Task_Handler);

  //创建OLED任务
  xTaskCreate(OLED_Task, "OLED_Task", 384, NULL, 3, &OLED_Task_Handler);

  //创建电机运行任务
  xTaskCreate(Motor1_Run_Task, "Motor1_Run_Task", 128, NULL, 3, &Motor1_Run_Task_Handle);
  xTaskCreate(Motor2_Run_Task, "Motor2_Run_Task", 128, NULL, 3, &Motor2_Run_Task_Handle);
  xTaskCreate(Motor3_Run_Task, "Motor3_Run_Task", 128, NULL, 3, &Motor3_Run_Task_Handle);
  xTaskCreate(Motor4_Run_Task, "Motor4_Run_Task", 128, NULL, 3, &Motor4_Run_Task_Handle);
  xTaskCreate(Motor5_Run_Task, "Motor5_Run_Task", 128, NULL, 3, &Motor5_Run_Task_Handle);
  xTaskCreate(Motor6_Run_Task, "Motor6_Run_Task", 128, NULL, 3, &Motor6_Run_Task_Handle);

} 



