//
// Created by 15368 on 2024/3/25.
//
#include "usart_task.h"
#include "motor_task.h"

uint8_t usart1_rec = 0;
uint8_t usart1_recbuf[USART_REC_LEN] = {0};
uint8_t usart6_rec = 0;
uint8_t usart6_recbuf[USART_REC_LEN] = {0};

TaskHandle_t USART1_Task_Handler;
TaskHandle_t USART6_Task_Handler;


void USART1_Task(void *pvParameters)
{
  TickType_t TickCount = xTaskGetTickCount();

  int data_len = 0;

  for(;;)
  {
    xTaskNotifyWait(0,0xffffffff,(uint32_t*)&data_len,portMAX_DELAY);//等待通知

    for (int i = 0; i < 6; ++i) {
      Motor[i+1].en = 0;//停机等待
    }

    if(usart1_recbuf[0] == 'A')
    {
      int num_buff[6];
      extractNumbers((const char*)usart1_recbuf,num_buff,6);//将数据字符转换成数字

      Motor[1].target_pulse = num_buff[0];
      Motor[2].target_pulse = num_buff[1];
      Motor[3].target_pulse = num_buff[2];
      Motor[4].target_pulse = num_buff[3];
      Motor[5].target_pulse = num_buff[4];
      Motor[6].target_pulse = num_buff[5];
    }

    else if(usart1_recbuf[0] == 'S')
    {
      int num_buff[1];
      extractNumbers((const char *) usart1_recbuf, num_buff, 1);//将数据字符转换成数字

      Motor[1].speed = num_buff[0] / 100000;
      Motor[2].speed = (num_buff[0] / 10000) % 10;
      Motor[3].speed = (num_buff[0] / 1000) % 10;
      Motor[4].speed = (num_buff[0] / 100) % 10;
      Motor[5].speed = (num_buff[0] / 10) % 10;
      Motor[6].speed = num_buff[0] % 10;

      for (int i = 0; i < 6; ++i)
      {
        switch (Motor[i + 1].speed)
        {
          case 1:
            Motor[i + 1].speed = MOTOR_SPEED_FAST;
            break;
          case 2:
            Motor[i + 1].speed = MOTOR_SPEED_HIGH;
            break;
          case 3:
            Motor[i + 1].speed = MOTOR_SPEED_MID;
            break;
          case 4:
            Motor[i + 1].speed = MOTOR_SPEED_LOW;
            break;
          default:
            break;
        }
      }
    }
    memset(usart1_recbuf,0,50);
    for(int i = 0;i<6;i++)
    {
      printf("target[%d]= %d   speed[%d]= %d\r\n",i+1,Motor[i+1].target_pulse,i+1,Motor[i+1].speed);
    }

    for (int i = 0; i < 6; ++i) {
      Motor[i+1].en = 1;//开机
    }
    vTaskDelayUntil(&TickCount, pdMS_TO_TICKS(100));
  }
}


static BaseType_t pxTaskWoken = pdFALSE;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /*
   * USART1中断接收
   */
  if(huart->Instance == USART1)
  {
    static int cnt1 = 0;
    usart1_recbuf[cnt1++] = usart1_rec;
    if(usart1_rec == END_FLAG)
    {
      xTaskNotifyFromISR(USART1_Task_Handler,cnt1,eSetValueWithOverwrite,&pxTaskWoken);
      cnt1 = 0;
      portYIELD_FROM_ISR(pxTaskWoken);
    }
    else if(cnt1-1 == USART_REC_LEN)
    {
      memset(usart1_recbuf,0,USART_REC_LEN);
      cnt1 = 0;
    }
    HAL_UART_Receive_IT(&huart1,&usart1_rec,1);
  }
  /*
   * USART6中断接收
   */
  else if(huart->Instance == USART6)
  {
    static int cnt6 = 0;
    usart6_recbuf[cnt6++] = usart6_rec;
    if(usart6_rec == END_FLAG)
    {
      vTaskNotifyGiveFromISR(Kinematics_IK_Task_Handle,&pxTaskWoken);
      cnt6 = 0;
      portYIELD_FROM_ISR(pxTaskWoken);
    }
    else if(cnt6-1 == USART_REC_LEN)
    {
      memset(usart6_recbuf,0,USART_REC_LEN);
      cnt6 = 0;
    }
    HAL_UART_Receive_IT(&huart6,&usart6_rec,1);
  }

}


// 提取字符串中的浮点数并存入数组中
void extractFloats(const char *data, float *floats, int size)
{
  int float_index = 0; // 浮点数索引

  while (*data && float_index < size) {
    char *endptr; // 用于指向字符串中数字后面的字符
    float num = strtof(data, &endptr); // 将字符串转换为浮点数

    if (endptr != data) { // 如果成功转换了数字
      floats[float_index++] = num; // 将浮点数存入数组并增加索引
      data = endptr; // 更新字符串指针
    } else {
      data++; // 继续查找下一个字符
    }
  }
}

// 提取字符串中的整数数字并存入数组中
void extractNumbers(const char *data, int *numbers, int size)
{
  int num_index = 0; // 数字索引
  int is_negative = 0; // 是否为负数标志

  for (int i = 0; data[i] != '\0' && num_index < size; i++)
  {
    if (data[i] >= '0' && data[i] <= '9') { // 检查字符是否为数字
      int num = 0; // 用来存放提取的数字
      int j = i; // 用来向后遍历字符

      // 向后遍历直到非数字字符或字符串结束
      while (data[j] >= '0' && data[j] <= '9')
      {
        num = num * 10 + (data[j] - '0');
        j++;
      }

      // 如果之前的字符是负号，则将数字变为负数
      if (is_negative)
      {
        num *= -1;
        is_negative = 0; // 重置负数标志
      }

      numbers[num_index++] = num; // 将数字存入数组并增加数字索引
      i = j - 1; // 更新主循环的索引位置
    } else if (data[i] == '-')
    { // 检查是否为负号
      is_negative = 1; // 设置负数标志
    }
  }
}

