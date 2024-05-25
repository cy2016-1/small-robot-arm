//
// Created by 15368 on 2024/4/9.
//

#ifndef __KINEMATICS_TASK_H
#define __KINEMATICS_TASK_H


#include "main.h"
#include "math.h"
#include "arm_math.h"


extern const double dl1;  //��1���ּ��ٱ� = 8  7.15
extern const double dl2;  //��2���ּ��ٱ� = 6
extern const double dl3;  //��3���ּ��ٱ� = 5
extern const double dl4;  //��4���ּ��ٱ� = 56/20 = 2.8
extern const double dl5;  //��5���ּ��ٱ� = 42/20 = 2.1
extern const double dl6;  //��6���ּ��ٱ� = 1



extern TaskHandle_t Kinematics_IK_Task_Handle;
void Kinematics_IK_Task(void* pvParameters);


void invtran(float* Titi, float* Titf);
void pos2tran(float* Xpt, float* Tpt);
void DH1line(float thetadh, float alfadh, float rdh, float ddh, float* Tdh);
void MatrixMultiply(float* A, float* B, int m, int p, int n, float* C);
void MatrixScale(float* A, int m, int n, float k);

void InverseK(float* Xik, float* Jik);//��⣬
/*
  float Xhome[6]={123, 55.0, 3.0, 90.0, -90.0, 0.0}; //{x, y, z, ZYZ Euler angles}

  float Jhome[6];

  InverseK(Xhome, Jhome);

  Jhome[6] = {�Ƕ�1���Ƕ�2���Ƕ�3���Ƕ�4���Ƕ�5���Ƕ�6} ;
 *
 */

#endif //__KINEMATICS_TASK_H
