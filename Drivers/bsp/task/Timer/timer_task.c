//
// Created by 15368 on 2024/3/25.
//

#include "timer_task.h"
#include "motor_task.h"



//定时器PWM回调函数
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  //Motor1
  if(htim->Instance == TIM1)
  {
    if(Motor[1].en == 1)
    {
      if(Motor[1].now_pulse == Motor[1].target_pulse)
      {
        HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
        Motor[1].en = 0;
      }
      else if(Motor[1].now_pulse < Motor[1].target_pulse)
      {
        MOTOR1_DIR_HIGH();
        Motor[1].now_pulse++;
      }
      else if(Motor[1].now_pulse > Motor[1].target_pulse)
      {
        MOTOR1_DIR_LOW();
        Motor[1].now_pulse--;
      }

    }
  }

  //Motor2
  else if(htim->Instance == TIM2)
  {
    if(Motor[2].en == 1)
    {
      if(Motor[2].now_pulse == Motor[2].target_pulse)
      {
        HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_1);
        Motor[2].en = 0;
      }
      else if(Motor[2].now_pulse < Motor[2].target_pulse)
      {
        MOTOR2_DIR_HIGH();
        Motor[2].now_pulse++;
      }
      else if(Motor[2].now_pulse > Motor[2].target_pulse)
      {
        MOTOR2_DIR_LOW();
        Motor[2].now_pulse--;
      }
    }
  }

  //Motor3
  else if(htim->Instance == TIM3)
  {
    if(Motor[3].en == 1)
    {
      if(Motor[3].now_pulse == Motor[3].target_pulse)
      {
        HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
        Motor[3].en = 0;
      }
      else if(Motor[3].now_pulse < Motor[3].target_pulse)
      {
        MOTOR3_DIR_LOW();
        Motor[3].now_pulse++;
      }
      else if(Motor[3].now_pulse > Motor[3].target_pulse)
      {
        MOTOR3_DIR_HIGH();
        Motor[3].now_pulse--;
      }

    }
  }

  //Motor4
  else if(htim->Instance == TIM4)
  {
    if(Motor[4].en== 1)
    {
      if(Motor[4].now_pulse == Motor[4].target_pulse)
      {
        HAL_TIM_PWM_Stop_IT(&htim4, TIM_CHANNEL_1);
        Motor[4].en = 0;
      }
      else if(Motor[4].now_pulse < Motor[4].target_pulse)
      {
        MOTOR4_DIR_HIGH();
        Motor[4].now_pulse++;
      }
      else if(Motor[4].now_pulse > Motor[4].target_pulse)
      {
        MOTOR4_DIR_LOW();
        Motor[4].now_pulse--;
      }
    }
  }

  //Motor5
  else if(htim->Instance == TIM5)
  {
    if(Motor[5].en == 1)
    {
      if(Motor[5].now_pulse == Motor[5].target_pulse)
      {
        HAL_TIM_PWM_Stop_IT(&htim5, TIM_CHANNEL_1);
        Motor[5].en = 0;
      }
      else if(Motor[5].now_pulse < Motor[5].target_pulse)
      {
        MOTOR5_DIR_HIGH();
        Motor[5].now_pulse++;
      }
      else if(Motor[5].now_pulse > Motor[5].target_pulse)
      {
        MOTOR5_DIR_LOW();
        Motor[5].now_pulse--;
      }

    }
  }

  //Motor6
  else if(htim->Instance == TIM9)
  {
    if(Motor[6].en== 1)
    {
      if(Motor[6].now_pulse == Motor[6].target_pulse)
      {
        HAL_TIM_PWM_Stop_IT(&htim9, TIM_CHANNEL_1);
        Motor[6].en = 0;
      }
      else if(Motor[6].now_pulse < Motor[6].target_pulse)
      {
        MOTOR6_DIR_LOW();
        Motor[6].now_pulse++;
      }
      else if(Motor[6].now_pulse > Motor[6].target_pulse)
      {
        MOTOR6_DIR_HIGH();
        Motor[6].now_pulse--;
      }
    }
  }

}
