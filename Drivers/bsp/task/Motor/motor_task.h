//
// Created by 15368 on 2024/3/25.
//

#ifndef V2_MOTOR_TASK_H
#define V2_MOTOR_TASK_H

#include "main.h"

//电机运行任务句柄
extern TaskHandle_t Motor1_Run_Task_Handle;
extern TaskHandle_t Motor2_Run_Task_Handle;
extern TaskHandle_t Motor3_Run_Task_Handle;
extern TaskHandle_t Motor4_Run_Task_Handle;
extern TaskHandle_t Motor5_Run_Task_Handle;
extern TaskHandle_t Motor6_Run_Task_Handle;

//电机初始化任务句柄
extern TaskHandle_t Motor1_Init_Task_Handle;
extern TaskHandle_t Motor2_Init_Task_Handle;
extern TaskHandle_t Motor3_Init_Task_Handle;
extern TaskHandle_t Motor4_Init_Task_Handle;
extern TaskHandle_t Motor5_Init_Task_Handle;
extern TaskHandle_t Motor6_Init_Task_Handle;

//电机控制宏
//电机1
#define MOTOR1_EN_LOW()         HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin,GPIO_PIN_RESET);
#define MOTOR1_EN_HIGH()        HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin,GPIO_PIN_SET);
#define MOTOR1_DIR_LOW()        HAL_GPIO_WritePin(DIR1_GPIO_Port,DIR1_Pin,GPIO_PIN_RESET);
#define MOTOR1_DIR_HIGH()       HAL_GPIO_WritePin(DIR1_GPIO_Port,DIR1_Pin,GPIO_PIN_SET);

//电机2
#define MOTOR2_EN_LOW()         HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin,GPIO_PIN_RESET);
#define MOTOR2_EN_HIGH()       HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin,GPIO_PIN_SET);
#define MOTOR2_DIR_LOW()        HAL_GPIO_WritePin(DIR2_GPIO_Port,DIR2_Pin,GPIO_PIN_RESET);
#define MOTOR2_DIR_HIGH()       HAL_GPIO_WritePin(DIR2_GPIO_Port,DIR2_Pin,GPIO_PIN_SET);

//电机3
#define MOTOR3_EN_LOW()         HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin,GPIO_PIN_RESET);
#define MOTOR3_EN_HIGH()        HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin,GPIO_PIN_SET);
#define MOTOR3_DIR_LOW()        HAL_GPIO_WritePin(DIR3_GPIO_Port,DIR3_Pin,GPIO_PIN_RESET);
#define MOTOR3_DIR_HIGH()       HAL_GPIO_WritePin(DIR3_GPIO_Port,DIR3_Pin,GPIO_PIN_SET);

//电机4
#define MOTOR4_EN_LOW()         HAL_GPIO_WritePin(EN4_GPIO_Port,EN4_Pin,GPIO_PIN_RESET);
#define MOTOR4_EN_HIGH()        HAL_GPIO_WritePin(EN4_GPIO_Port,EN4_Pin,GPIO_PIN_SET);
#define MOTOR4_DIR_LOW()        HAL_GPIO_WritePin(DIR4_GPIO_Port,DIR4_Pin,GPIO_PIN_RESET);
#define MOTOR4_DIR_HIGH()       HAL_GPIO_WritePin(DIR4_GPIO_Port,DIR4_Pin,GPIO_PIN_SET);

//电机5
#define MOTOR5_EN_LOW()         HAL_GPIO_WritePin(EN5_GPIO_Port,EN5_Pin,GPIO_PIN_RESET);
#define MOTOR5_EN_HIGH()        HAL_GPIO_WritePin(EN5_GPIO_Port,EN5_Pin,GPIO_PIN_SET);
#define MOTOR5_DIR_LOW()        HAL_GPIO_WritePin(DIR5_GPIO_Port,DIR5_Pin,GPIO_PIN_RESET);
#define MOTOR5_DIR_HIGH()       HAL_GPIO_WritePin(DIR5_GPIO_Port,DIR5_Pin,GPIO_PIN_SET);

//电机6
#define MOTOR6_EN_LOW()         HAL_GPIO_WritePin(EN6_GPIO_Port,EN6_Pin,GPIO_PIN_RESET);
#define MOTOR6_EN_HIGH()        HAL_GPIO_WritePin(EN6_GPIO_Port,EN6_Pin,GPIO_PIN_SET);
#define MOTOR6_DIR_LOW()        HAL_GPIO_WritePin(DIR6_GPIO_Port,DIR6_Pin,GPIO_PIN_RESET);
#define MOTOR6_DIR_HIGH()       HAL_GPIO_WritePin(DIR6_GPIO_Port,DIR6_Pin,GPIO_PIN_SET);


//电机转速枚举
enum motor_speed
{
    MOTOR_SPEED_LOW = 9999,//100Hz
    MOTOR_SPEED_MID = 999,//1KHz
    MOTOR_SPEED_HIGH = 99,//10KHz
    MOTOR_SPEED_FAST = 49 //20KHz
};

//电机控制参数结构体
struct motor_ctrl
{
    int target_pulse;
    int now_pulse;
    uint8_t dir;
    uint8_t en;
    enum motor_speed speed;
};
extern struct motor_ctrl Motor[7];


//电机运行任务函数
void Motor1_Run_Task(void *pvParameters);
void Motor2_Run_Task(void *pvParameters);
void Motor3_Run_Task(void *pvParameters);
void Motor4_Run_Task(void *pvParameters);
void Motor5_Run_Task(void *pvParameters);
void Motor6_Run_Task(void *pvParameters);

//电机初始化任务函数
void Motor1_Init_Task(void *pvParameters);
void Motor2_Init_Task(void *pvParameters);
void Motor3_Init_Task(void *pvParameters);
void Motor4_Init_Task(void *pvParameters);
void Motor5_Init_Task(void *pvParameters);
void Motor6_Init_Task(void *pvParameters);

#endif //V2_MOTOR_TASK_H
