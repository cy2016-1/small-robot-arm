//
// Created by 15368 on 2024/4/9.
//

#ifndef __KINEMATICS_TASK_H
#define __KINEMATICS_TASK_H


#include "main.h"
#include "math.h"
#include "arm_math.h"


extern const double dl1;  //轴1齿轮减速比 = 8  7.15
extern const double dl2;  //轴2齿轮减速比 = 6
extern const double dl3;  //轴3齿轮减速比 = 5
extern const double dl4;  //轴4齿轮减速比 = 56/20 = 2.8
extern const double dl5;  //轴5齿轮减速比 = 42/20 = 2.1
extern const double dl6;  //轴6齿轮减速比 = 1



extern TaskHandle_t Kinematics_IK_Task_Handle;
void Kinematics_IK_Task(void* pvParameters);


void invtran(float* Titi, float* Titf);
void pos2tran(float* Xpt, float* Tpt);
void DH1line(float thetadh, float alfadh, float rdh, float ddh, float* Tdh);
void MatrixMultiply(float* A, float* B, int m, int p, int n, float* C);
void MatrixScale(float* A, int m, int n, float k);

void InverseK(float* Xik, float* Jik);//逆解，
/*
  float Xhome[6]={123, 55.0, 3.0, 90.0, -90.0, 0.0}; //{x, y, z, ZYZ Euler angles}

  float Jhome[6];

  InverseK(Xhome, Jhome);

  Jhome[6] = {角度1，角度2，角度3，角度4，角度5，角度6} ;
 *
 */

#endif //__KINEMATICS_TASK_H
