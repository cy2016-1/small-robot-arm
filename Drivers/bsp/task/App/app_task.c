//
// Created by 15368 on 2024/3/5.
//
#include "app_task.h"
#include "motor_task.h"
#include "usart_task.h"

TaskHandle_t OLED_Task_Handler  = NULL;
TaskHandle_t App_Run_Task_Init_Handle  = NULL;
TaskHandle_t Camer_Snapshot_Task_Handle = NULL;

TimerHandle_t Camer_Timer_Handle = NULL;


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

      sprintf((char*)oled_buf,"tar_x:x:%d y:%d z:%d",54,43,20);
      u8g2_DrawStr(&u8g2, 0, 10, (const char*)oled_buf);//在屏幕上显示

      sprintf((char*)oled_buf,"now_x:%d %d %d",0,5,145);
      u8g2_DrawStr(&u8g2, 0, 20, (const char*)oled_buf);//在屏幕上显示

      sprintf((char*)oled_buf,"speed:%d",30);
      u8g2_DrawStr(&u8g2, 0, 30, (const char*)oled_buf);//在屏幕上显示

      sprintf((char*)oled_buf,"tar_pK:%d %d %d %d %d %d",5,3,4,-1,1,3);
      u8g2_DrawStr(&u8g2, 0, 40, (const char*)oled_buf);//在屏幕上显示

      sprintf((char*)oled_buf,"tar_p:%d %d %d %d %d %d",0,0,0,-0,0,0);
      u8g2_DrawStr(&u8g2, 0, 50, (const char*)oled_buf);//在屏幕上显示

      sprintf((char*)oled_buf,"now_KHz:%d %d %d %d %d %d",1,1,1,1,1,1);
      u8g2_DrawStr(&u8g2, 0, 60, (const char*)oled_buf);//在屏幕上显示
    }
    u8g2_SendBuffer(&u8g2);//刷新屏幕

    vTaskDelayUntil(&TickCount, pdMS_TO_TICKS(100));
  }
}


void App_Init_Task_Init(void)
{
  //创建电机初始化任务
  xTaskCreate(Motor1_Init_Task, "Motor1_Init_Task", 128, NULL, 3, &Motor1_Init_Task_Handle);
}


void App_Run_Task_Init(void *pvParameters)
{
  //创建USART任务
  xTaskCreate(USART1_Task, "USART1_Task", 512, NULL, 3, &USART1_Task_Handler);

  //创建运动学解析任务
  xTaskCreate(Kinematics_IK_Task, "Kinematics_IK_Task", 1024, NULL, 3, &Kinematics_IK_Task_Handle);

  //创建OLED任务
//  xTaskCreate(OLED_Task, "OLED_Task", 384, NULL, 3, &OLED_Task_Handler);

  //创建电机运行任务
  xTaskCreate(Motor1_Run_Task, "Motor1_Run_Task", 128, NULL, 3, &Motor1_Run_Task_Handle);
  xTaskCreate(Motor2_Run_Task, "Motor2_Run_Task", 128, NULL, 3, &Motor2_Run_Task_Handle);
  xTaskCreate(Motor3_Run_Task, "Motor3_Run_Task", 128, NULL, 3, &Motor3_Run_Task_Handle);
  xTaskCreate(Motor4_Run_Task, "Motor4_Run_Task", 128, NULL, 3, &Motor4_Run_Task_Handle);
  xTaskCreate(Motor5_Run_Task, "Motor5_Run_Task", 128, NULL, 3, &Motor5_Run_Task_Handle);
  xTaskCreate(Motor6_Run_Task, "Motor6_Run_Task", 128, NULL, 3, &Motor6_Run_Task_Handle);

  vTaskDelete(NULL);
}



