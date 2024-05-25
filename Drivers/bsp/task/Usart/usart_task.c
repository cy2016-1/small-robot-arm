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
//TaskHandle_t USART6_Task_Handler;

volatile int8_t usart1_flag = 0;
volatile int8_t usart6_flag = 0;

void USART1_Task(void *pvParameters)
{
  TickType_t TickCount = xTaskGetTickCount();
  for(;;)
  {
    if(usart1_flag == 1)
    {
      usart1_flag = 0;
      for (int i = 0; i < 6; ++i) {
        Motor[i+1].en = 0;//ͣ���ȴ�
      }
      if(usart1_recbuf[0] == 'A') {
        for (int i = 0; i < 6; i++) {
          printf("target[%d]= %d\r\n", i + 1, Motor[i + 1].target_pulse);
        }
      }
      memset(usart1_recbuf,0,50);
      for (int i = 0; i < 6; ++i)
      {
        Motor[i+1].en = 1;//����
      }
    }
    vTaskDelayUntil(&TickCount, pdMS_TO_TICKS(100));
  }
}


static BaseType_t pxTaskWoken = pdFALSE;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /*
   * USART1�жϽ���
   */
  if(huart->Instance == USART1)
  {
    static int cnt1 = 0;
    usart1_recbuf[cnt1++] = usart1_rec;
    if(usart1_rec == END_FLAG)
    {
      usart1_flag = 1;
      cnt1 = 0;
    }
    else if(cnt1-1 == USART_REC_LEN)
    {
      memset(usart1_recbuf,0,USART_REC_LEN);
      cnt1 = 0;
    }
    HAL_UART_Receive_IT(&huart1,&usart1_rec,1);
  }
  /*
   * USART6�жϽ���
   */
  else if(huart->Instance == USART6)
  {
    static int cnt6 = 0;
    usart6_recbuf[cnt6++] = usart6_rec;
    if(usart6_rec == END_FLAG)
    {
      usart6_flag = 1;
      cnt6 = 0;
    }
    else if(cnt6-1 == USART_REC_LEN)
    {
      memset(usart6_recbuf,0,USART_REC_LEN);
      cnt6 = 0;
    }
    HAL_UART_Receive_IT(&huart6,&usart6_rec,1);
  }

}


// ��ȡ�ַ����еĸ�����������������
void extractFloats(const char *data, float *floats, int size)
{
  int float_index = 0; // ����������

  while (*data && float_index < size) {
    char *endptr; // ����ָ���ַ��������ֺ�����ַ�
    float num = strtof(data, &endptr); // ���ַ���ת��Ϊ������

    if (endptr != data) { // ����ɹ�ת��������
      floats[float_index++] = num; // ���������������鲢��������
      data = endptr; // �����ַ���ָ��
    } else {
      data++; // ����������һ���ַ�
    }
  }
}

// ��ȡ�ַ����е��������ֲ�����������
void extractNumbers(const char *data, int *numbers, int size)
{
  int num_index = 0; // ��������
  int is_negative = 0; // �Ƿ�Ϊ������־

  for (int i = 0; data[i] != '\0' && num_index < size; i++)
  {
    if (data[i] >= '0' && data[i] <= '9') { // ����ַ��Ƿ�Ϊ����
      int num = 0; // ���������ȡ������
      int j = i; // �����������ַ�

      // ������ֱ���������ַ����ַ�������
      while (data[j] >= '0' && data[j] <= '9')
      {
        num = num * 10 + (data[j] - '0');
        j++;
      }

      // ���֮ǰ���ַ��Ǹ��ţ������ֱ�Ϊ����
      if (is_negative)
      {
        num *= -1;
        is_negative = 0; // ���ø�����־
      }

      numbers[num_index++] = num; // �����ִ������鲢������������
      i = j - 1; // ������ѭ��������λ��
    } else if (data[i] == '-')
    { // ����Ƿ�Ϊ����
      is_negative = 1; // ���ø�����־
    }
  }
}

