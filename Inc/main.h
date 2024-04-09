/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define PUL5_Pin GPIO_PIN_0
#define PUL5_GPIO_Port GPIOA
#define EN5_Pin GPIO_PIN_1
#define EN5_GPIO_Port GPIOA
#define PUL6_Pin GPIO_PIN_2
#define PUL6_GPIO_Port GPIOA
#define EN4_Pin GPIO_PIN_3
#define EN4_GPIO_Port GPIOA
#define EN3_Pin GPIO_PIN_4
#define EN3_GPIO_Port GPIOA
#define PUL2_Pin GPIO_PIN_5
#define PUL2_GPIO_Port GPIOA
#define PUL3_Pin GPIO_PIN_6
#define PUL3_GPIO_Port GPIOA
#define IN1_Pin GPIO_PIN_7
#define IN1_GPIO_Port GPIOA
#define IN2_Pin GPIO_PIN_0
#define IN2_GPIO_Port GPIOB
#define IN3_Pin GPIO_PIN_1
#define IN3_GPIO_Port GPIOB
#define IN4_Pin GPIO_PIN_2
#define IN4_GPIO_Port GPIOB
#define IN5_Pin GPIO_PIN_10
#define IN5_GPIO_Port GPIOB
#define EN1_Pin GPIO_PIN_12
#define EN1_GPIO_Port GPIOB
#define EN2_Pin GPIO_PIN_13
#define EN2_GPIO_Port GPIOB
#define DIR6_Pin GPIO_PIN_14
#define DIR6_GPIO_Port GPIOB
#define DIR5_Pin GPIO_PIN_15
#define DIR5_GPIO_Port GPIOB
#define PUL1_Pin GPIO_PIN_8
#define PUL1_GPIO_Port GPIOA
#define DIR4_Pin GPIO_PIN_15
#define DIR4_GPIO_Port GPIOA
#define DIR3_Pin GPIO_PIN_3
#define DIR3_GPIO_Port GPIOB
#define DIR2_Pin GPIO_PIN_4
#define DIR2_GPIO_Port GPIOB
#define DIR1_Pin GPIO_PIN_5
#define DIR1_GPIO_Port GPIOB
#define PUL4_Pin GPIO_PIN_6
#define PUL4_GPIO_Port GPIOB
#define EN6_Pin GPIO_PIN_7
#define EN6_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#include "FreeRTOS.h"
#include "task.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "u8g2.h"
#include "oled.h"
#include "stdio.h"
#include "string.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "stdlib.h"

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
