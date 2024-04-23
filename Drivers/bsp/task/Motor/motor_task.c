//
// Created by 15368 on 2024/3/25.
//

#include "motor_task.h"
#include "timer_task.h"
#include "app_task.h"

//电机运行任务句柄
TaskHandle_t Motor1_Run_Task_Handle = NULL;
TaskHandle_t Motor2_Run_Task_Handle = NULL;
TaskHandle_t Motor3_Run_Task_Handle = NULL;
TaskHandle_t Motor4_Run_Task_Handle = NULL;
TaskHandle_t Motor5_Run_Task_Handle = NULL;
TaskHandle_t Motor6_Run_Task_Handle = NULL;

//电机初始化任务句柄
TaskHandle_t Motor1_Init_Task_Handle = NULL;
TaskHandle_t Motor2_Init_Task_Handle = NULL;
TaskHandle_t Motor3_Init_Task_Handle = NULL;
TaskHandle_t Motor4_Init_Task_Handle = NULL;
TaskHandle_t Motor5_Init_Task_Handle = NULL;
TaskHandle_t Motor6_Init_Task_Handle = NULL;

//电机控制结构体
Motor_ctrl Motor[7];

//初始化脉冲角度比例
float Motor_Dev[7] = {0.0f,motor1_dev,motor2_dev,motor3_dev,motor4_dev,motor5_dev,motor6_dev};


//角度转脉冲
int Angle_to_Pulse(float angle,int motor_id)
{
  int pulse = 0;
  pulse = (int)(angle * Motor_Dev[motor_id]);
  return pulse;
}
//脉冲转角度
float Pulse_to_Angle(int pulse,int motor_id)
{
  float angle = 0.0f;
  angle = (float)((float)pulse / Motor_Dev[motor_id]);
  return angle;
}


//电机初始化任务
void Motor1_Init_Task(void *pvParameters)
{
  Motor[1].max_pulse = 11500;
  Motor[1].min_pulse = -11500;
  Motor[1].now_pulse = 0;
  Motor[1].target_pulse = 30000;
  Motor[1].speed = MOTOR_SPEED_MID;

  int flag = 0;

  for(;;)
  {
    if(!HAL_GPIO_ReadPin(IN1_GPIO_Port,IN1_Pin) && (flag == 0))//没到达限位
    {
      Motor[1].en = 1;
      __HAL_TIM_SET_PRESCALER(&htim1,Motor[1].speed);
      HAL_TIM_PWM_Start_IT(&htim1,TIM_CHANNEL_1);
    }
    else if(HAL_GPIO_ReadPin(IN1_GPIO_Port,IN1_Pin))//到达限位
    {
      flag = 1;
      Motor[1].en = 0;
      HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
//      Motor[1].now_pulse = 11500;
//      Motor[1].target_pulse = 0;
      Motor[1].now_pulse = Angle_to_Pulse(90.0f,1);
      Motor[1].target_pulse = Angle_to_Pulse(0.0f,1);

      Motor[1].en = 1;
      HAL_TIM_PWM_Start_IT(&htim1,TIM_CHANNEL_1);
    }
    if(flag == 1 && Motor[1].en == 0)
    {
      //创建第二轴初始化任务
      xTaskCreate(Motor2_Init_Task, "Motor2_Init_Task", 128, NULL, 3, &Motor2_Init_Task_Handle);
      if(Motor2_Init_Task_Handle != NULL)
      {
        vTaskDelete(Motor1_Init_Task_Handle);//删除第一轴初始化任务
        vTaskDelay(pdMS_TO_TICKS(20));
      }
    }
  }
}


void Motor2_Init_Task(void *pvParameters)
{
  TickType_t TickCount = xTaskGetTickCount();
  Motor[2].speed = MOTOR_SPEED_MID;
  Motor[2].max_pulse = 18000;
  Motor[2].min_pulse = 0;

  if(HAL_GPIO_ReadPin(IN2_GPIO_Port,IN2_Pin))
  {
    Motor[2].target_pulse = 3000;
    Motor[2].now_pulse = 0;
    Motor[2].en = 1;
    __HAL_TIM_SET_PRESCALER(&htim2,Motor[2].speed);
    HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_1);
    while(HAL_GPIO_ReadPin(IN2_GPIO_Port,IN2_Pin))
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    HAL_TIM_PWM_Stop_IT(&htim2,TIM_CHANNEL_1);
    Motor[2].target_pulse = -1000;
    Motor[2].en = 1;
    HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_1);
    while(!HAL_GPIO_ReadPin(IN2_GPIO_Port,IN2_Pin))
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    HAL_TIM_PWM_Stop_IT(&htim2,TIM_CHANNEL_1);
    Motor[2].target_pulse = 0;
    Motor[2].now_pulse = 0;

    //创建第三轴初始化任务
    xTaskCreate(Motor3_Init_Task, "Motor3_Init_Task", 128, NULL, 3, &Motor3_Init_Task_Handle);
    if(Motor3_Init_Task_Handle != NULL)
    {
      vTaskDelete(Motor2_Init_Task_Handle);//删除第二轴初始化任务
      vTaskDelay(pdMS_TO_TICKS(10));
    }
  }
  else if(!HAL_GPIO_ReadPin(IN2_GPIO_Port,IN2_Pin))
  {
    Motor[2].target_pulse = -18000;
    Motor[2].now_pulse = 0;
    Motor[2].en = 1;
    __HAL_TIM_SET_PRESCALER(&htim2,Motor[2].speed);
    HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_1);

    while(!HAL_GPIO_ReadPin(IN2_GPIO_Port,IN2_Pin))
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    HAL_TIM_PWM_Stop_IT(&htim2,TIM_CHANNEL_1);
    Motor[2].target_pulse = 0;
    Motor[2].now_pulse = 0;
    //创建第三轴初始化任务
    xTaskCreate(Motor3_Init_Task, "Motor3_Init_Task", 128, NULL, 3, &Motor3_Init_Task_Handle);
    if(Motor3_Init_Task_Handle != NULL)
    {
      vTaskDelete(Motor2_Init_Task_Handle);//删除第二轴初始化任务
      vTaskDelay(pdMS_TO_TICKS(10));
    }
  }
  vTaskDelayUntil(&TickCount,pdMS_TO_TICKS(20));
}



void Motor3_Init_Task(void *pvParameters)
{
  TickType_t TickCount = xTaskGetTickCount();
  Motor[3].speed = MOTOR_SPEED_MID;
  Motor[3].max_pulse = 16000;
  Motor[3].min_pulse = 0;

  if(HAL_GPIO_ReadPin(IN3_GPIO_Port,IN3_Pin))
  {
    Motor[3].target_pulse = 18000;
    Motor[3].now_pulse = 0;
    Motor[3].en = 1;
    __HAL_TIM_SET_PRESCALER(&htim3,Motor[3].speed);
    HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_1);
    while(HAL_GPIO_ReadPin(IN3_GPIO_Port,IN3_Pin))
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    HAL_TIM_PWM_Stop_IT(&htim3,TIM_CHANNEL_1);
    Motor[3].target_pulse = -18000;
    Motor[3].en = 1;
    HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_1);
    while(!HAL_GPIO_ReadPin(IN3_GPIO_Port,IN3_Pin))
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    HAL_TIM_PWM_Stop_IT(&htim3,TIM_CHANNEL_1);
    Motor[3].target_pulse = 0;
    Motor[3].now_pulse = 0;
    //创建第四轴初始化任务
    xTaskCreate(Motor4_Init_Task, "Motor4_Init_Task", 128, NULL, 3, &Motor4_Init_Task_Handle);
    if(Motor4_Init_Task_Handle != NULL)
    {
      vTaskDelete(Motor3_Init_Task_Handle);//删除第三轴初始化任务
    }
  }
  else if(!HAL_GPIO_ReadPin(IN3_GPIO_Port,IN3_Pin))
  {
    Motor[3].now_pulse = 0;
    Motor[3].target_pulse = -16000;
    Motor[3].en = 1;
    __HAL_TIM_SET_PRESCALER(&htim3,Motor[3].speed);
    HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_1);

    while(!HAL_GPIO_ReadPin(IN3_GPIO_Port,IN3_Pin))
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    HAL_TIM_PWM_Stop_IT(&htim3,TIM_CHANNEL_1);
    Motor[3].target_pulse = 0;
    Motor[3].now_pulse = 0;

    //创建第四轴初始化任务
    xTaskCreate(Motor4_Init_Task, "Motor4_Init_Task", 128, NULL, 3, &Motor4_Init_Task_Handle);
    if(Motor4_Init_Task_Handle != NULL)
    {
      vTaskDelete(Motor3_Init_Task_Handle);//删除第三轴初始化任务
      vTaskDelay(pdMS_TO_TICKS(10));
    }

  }
  vTaskDelayUntil(&TickCount,pdMS_TO_TICKS(20));
}



void Motor4_Init_Task(void *pvParameters)
{
  TickType_t TickCount = xTaskGetTickCount();
  Motor[3].target_pulse = 5000;
  Motor[3].en = 1;
  __HAL_TIM_SET_PRESCALER(&htim3,Motor[3].speed);
  HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_1);

  Motor[4].max_pulse = 9200;
  Motor[4].min_pulse = -9200;

  while (Motor[3].en == 1)
  {
    vTaskDelay(pdMS_TO_TICKS(1));
  }

  if(!HAL_GPIO_ReadPin(IN4_GPIO_Port,IN4_Pin))
  {
    Motor[4].now_pulse = 0;
    Motor[4].target_pulse = 15000;
    Motor[4].speed = MOTOR_SPEED_MID;
    Motor[4].en = 1;
    __HAL_TIM_SET_PRESCALER(&htim4,Motor[4].speed);
    HAL_TIM_PWM_Start_IT(&htim4,TIM_CHANNEL_1);
    while(!HAL_GPIO_ReadPin(IN4_GPIO_Port,IN4_Pin))
    {
      vTaskDelay(pdMS_TO_TICKS(10));
    }
    Motor[4].now_pulse = 9200;
    Motor[4].target_pulse = 0;
    Motor[4].en = 1;
    while(Motor[4].en == 1)
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    HAL_TIM_PWM_Stop_IT(&htim4,TIM_CHANNEL_1);

    xTaskCreate(Motor5_Init_Task, "Motor5_Init_Task", 128, NULL, 3, &Motor5_Init_Task_Handle);
    while(Motor5_Init_Task_Handle == NULL)
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    vTaskDelete(Motor4_Init_Task_Handle);
    vTaskDelay(pdMS_TO_TICKS(10));
  }
  xTaskDelayUntil(&TickCount, pdMS_TO_TICKS(10));
}


void Motor5_Init_Task(void *pvParameters)
{
  Motor[5].speed = MOTOR_SPEED_MID;

  Motor[5].max_pulse = 3500;
  Motor[5].min_pulse = -3500;

  __HAL_TIM_SET_PRESCALER(&htim5,Motor[5].speed);

  if(HAL_GPIO_ReadPin(IN5_GPIO_Port,IN5_Pin))
  {
    Motor[5].now_pulse = 0;
    Motor[5].target_pulse = -7000;
    Motor[5].en = 1;
    HAL_TIM_PWM_Start_IT(&htim5,TIM_CHANNEL_1);
    while(HAL_GPIO_ReadPin(IN5_GPIO_Port,IN5_Pin))
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    Motor[5].target_pulse = 7000;
    Motor[5].en = 1;
    HAL_TIM_PWM_Start_IT(&htim5,TIM_CHANNEL_1);
    while(!(HAL_GPIO_ReadPin(IN5_GPIO_Port,IN5_Pin)))
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    Motor[5].now_pulse = 3300;
    Motor[5].target_pulse = 0;
    Motor[5].en = 1;
    HAL_TIM_PWM_Start_IT(&htim5,TIM_CHANNEL_1);
    while(Motor[5].en == 1)
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    //第三轴归位
    Motor[3].target_pulse = 0;
    Motor[3].en = 1;
    HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_1);
    while(Motor[3].en == 1)
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    HAL_TIM_PWM_Stop_IT(&htim3,TIM_CHANNEL_1);//第三轴到位

    xTaskCreate(Motor6_Init_Task, "Motor6_Init_Task", 128, NULL, 3, &Motor6_Init_Task_Handle);
    while(Motor6_Init_Task_Handle == NULL)
    {
      vTaskDelay(pdMS_TO_TICKS(10));
    }

    vTaskDelete(Motor5_Init_Task_Handle);
  }

  else if(!(HAL_GPIO_ReadPin(IN5_GPIO_Port,IN5_Pin)))
  {
    Motor[5].now_pulse = 0;
    Motor[5].target_pulse = 7000;
    Motor[5].en = 1;
    HAL_TIM_PWM_Start_IT(&htim5,TIM_CHANNEL_1);
    while(!(HAL_GPIO_ReadPin(IN5_GPIO_Port,IN5_Pin)))
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    Motor[5].now_pulse = 3300;
    Motor[5].target_pulse = 0;
    Motor[5].en = 1;
    HAL_TIM_PWM_Start_IT(&htim5,TIM_CHANNEL_1);
    while(Motor[5].en == 1)
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    //第三轴归位
    Motor[3].now_pulse = 5000;
    Motor[3].speed = MOTOR_SPEED_MID;
    Motor[3].target_pulse = 0;
    Motor[3].en = 1;
    __HAL_TIM_SET_PRESCALER(&htim3,Motor[3].speed);
    HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_1);
    while(Motor[3].en == 1)
    {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    HAL_TIM_PWM_Stop_IT(&htim3,TIM_CHANNEL_1);//第三轴到位

    vTaskDelay(pdMS_TO_TICKS(10));

    xTaskCreate(Motor6_Init_Task, "Motor6_Init_Task", 128, NULL, 3, &Motor6_Init_Task_Handle);
    while(Motor6_Init_Task_Handle == NULL)
    {
      vTaskDelay(pdMS_TO_TICKS(10));
    }

    vTaskDelete(Motor5_Init_Task_Handle);
  }
  vTaskDelay(pdMS_TO_TICKS(10));
}

void Motor6_Init_Task(void *pvParameters)
{
  Motor[6].speed = MOTOR_SPEED_MID;
  __HAL_TIM_SET_PRESCALER(&htim9,Motor[6].speed);

  Motor[6].en = 0;

  vTaskDelay(pdMS_TO_TICKS(200));

  Motor[6].now_pulse = -20;
  Motor[6].target_pulse = 0;
  Motor[6].en = 1;
  HAL_TIM_PWM_Start_IT(&htim9,TIM_CHANNEL_1);

  while(Motor[6].en == 1)
  {
    vTaskDelay(pdMS_TO_TICKS(10));
  }

  App_Run_Task_Init();//创建apptask
  vTaskDelay(pdMS_TO_TICKS(100));
  vTaskDelete(Motor6_Init_Task_Handle);
}


//电机运行任务
void Motor1_Run_Task(void *pvParameters)//tim1 ch1
{
  TickType_t TickCount = xTaskGetTickCount();
  for(;;)
  {
    if(Motor[1].en == 1)
    {
      Pulse_Limit(&Motor[1]);
      __HAL_TIM_SET_PRESCALER(&htim1,Motor[1].speed);
      HAL_TIM_PWM_Start_IT(&htim1,TIM_CHANNEL_1);
    }
    else
    {
      HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
    }
    vTaskDelayUntil(&TickCount,pdMS_TO_TICKS(10));
  }
}

void Motor2_Run_Task(void *pvParameters)//tim2 ch1
{
  TickType_t TickCount = xTaskGetTickCount();
  for(;;)
  {
    if(Motor[2].en == 1)
    {
      Pulse_Limit(&Motor[2]);
      __HAL_TIM_SET_PRESCALER(&htim2,Motor[2].speed);
      HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_1);
    }
    else
    {
      HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
    }
    vTaskDelayUntil(&TickCount,pdMS_TO_TICKS(10));
  }

}

void Motor3_Run_Task(void *pvParameters)//tim3 ch1
{
  TickType_t TickCount = xTaskGetTickCount();
  MOTOR3_EN_LOW();
  for(;;)
  {
    if(Motor[3].en == 1)
    {
      Pulse_Limit(&Motor[3]);
      __HAL_TIM_SET_PRESCALER(&htim3,Motor[3].speed);
      HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_1);
    }
    else
    {
      HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
    }

    vTaskDelayUntil(&TickCount,pdMS_TO_TICKS(10));
  }
}


void Motor4_Run_Task(void *pvParameters)//tim4 ch1
{
  TickType_t TickCount = xTaskGetTickCount();
  MOTOR4_EN_LOW();
  for(;;)
  {
    if(Motor[4].en == 1)
    {
      Pulse_Limit(&Motor[4]);
      __HAL_TIM_SET_PRESCALER(&htim4,Motor[4].speed);
      HAL_TIM_PWM_Start_IT(&htim4,TIM_CHANNEL_1);
    }
    else
    {
      HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
    }
    vTaskDelayUntil(&TickCount,pdMS_TO_TICKS(10));
  }

}

void Motor5_Run_Task(void *pvParameters)//tim5 ch1
{
  TickType_t TickCount = xTaskGetTickCount();
  MOTOR5_EN_LOW();
  for(;;)
  {
    if(Motor[5].en == 1)
    {
      Pulse_Limit(&Motor[5]);
      __HAL_TIM_SET_PRESCALER(&htim5,Motor[5].speed);
      HAL_TIM_PWM_Start_IT(&htim5,TIM_CHANNEL_1);
    }
    else
    {
      HAL_TIM_PWM_Stop(&htim5,TIM_CHANNEL_1);
    }

    vTaskDelayUntil(&TickCount,pdMS_TO_TICKS(10));
  }
}

void Motor6_Run_Task(void *pvParameters)//tim9 ch1
{
  TickType_t TickCount = xTaskGetTickCount();
  MOTOR6_EN_LOW();
  for(;;)
  {
    if(Motor[6].en == 1)
    {
      Pulse_Limit(&Motor[6]);
      __HAL_TIM_SET_PRESCALER(&htim9,Motor[6].speed);
      HAL_TIM_PWM_Start_IT(&htim9,TIM_CHANNEL_1);
    }
    else
    {
      HAL_TIM_PWM_Stop(&htim9,TIM_CHANNEL_1);
    }
    vTaskDelayUntil(&TickCount,pdMS_TO_TICKS(10));
  }
}


void Pulse_Limit(Motor_ctrl* pulse)
{
  if(pulse->target_pulse >= pulse->max_pulse)
    pulse->target_pulse = pulse->max_pulse;
  if(pulse->target_pulse <= pulse->min_pulse)
    pulse->target_pulse = pulse->min_pulse;
}