//
// Created by 15368 on 2024/4/9.
//

#include "kinematics_task.h"

Openmv_t openmv;

const double r1 = 47.0;
const double r2 = 110.0;
const double r3 = 26.0;
const double d1 = 133.0;
const double d3 = 0.0;
const double d4 = 117.50;
const double d6 = 28.0;


//�˶�ѧ����������
TaskHandle_t Kinematics_IK_Task_Handle;



//���������
void Kinematics_IK_Task(void* pvParameters)
{
  TickType_t TickCount = xTaskGetTickCount();

  for(;;)
  {

    ulTaskNotifyTake(pdTRUE,portMAX_DELAY);//�ȴ�֪ͨ

    for (int i = 0; i < 6; ++i) {
      Motor[i+1].en = 0;//ͣ���ȴ�
    }

    int num_buff[2];
    extractNumbers((const char*)usart6_recbuf,num_buff,2);//�������ַ�ת��������

    openmv.x = (float)num_buff[0];
    openmv.y = (float)num_buff[1];

    float Xhome[6]={openmv.x, openmv.y, Z_high, 90.0f, 180.0f, -90.0f}; //{x, y, z, ZYZ Euler angles}
    float Jhome[6];
    InverseK(Xhome, Jhome);

    printf("openmv:x:%.4f,y:%.4f\r\n",openmv.x,openmv.y);
    printf("Theta1:%.4f\r\nTheta2:%.4f\r\nTheta3:%.4f\r\nTheta4:%.4f\r\nTheta5:%.4f\r\nTheta6:%.4f\r\n",Jhome[0],Jhome[1],Jhome[2],Jhome[3],Jhome[4],Jhome[5]);

//    for(int i=0;i<6;++i)
//    {
//      Motor[i+1].target_pulse += (int)(Jhome[i]*Motor_Dev[i+1]);
//    }
//    for (int i = 0; i < 6; ++i) {
//      Motor[i+1].en = 1;//����ִ��
//    }

    vTaskDelayUntil(&TickCount, pdMS_TO_TICKS(100));
  }
}



void invtran(float* Titi, float* Titf)
{
  // finding the inverse of the homogeneous transformation matrix //����α任�������
  // first row  //��1��
  Titf[0*4 + 0] = Titi[0*4 + 0];
  Titf[0*4 + 1] = Titi[1*4 + 0];
  Titf[0*4 + 2] = Titi[2*4 + 0];
  Titf[0*4 + 3] = -Titi[0*4 + 0]*Titi[0*4 + 3]-Titi[1*4 + 0]*Titi[1*4 + 3]-Titi[2*4 + 0]*Titi[2*4 + 3];
  // second row //��2��
  Titf[1*4 + 0] = Titi[0*4 + 1];
  Titf[1*4 + 1] = Titi[1*4 + 1];
  Titf[1*4 + 2] = Titi[2*4 + 1];
  Titf[1*4 + 3] = -Titi[0*4 + 1]*Titi[0*4 + 3]-Titi[1*4 + 1]*Titi[1*4 + 3]-Titi[2*4 + 1]*Titi[2*4 + 3];
  // third row  //��3��
  Titf[2*4 + 0] = Titi[0*4 + 2];
  Titf[2*4 + 1] = Titi[1*4 + 2];
  Titf[2*4 + 2] = Titi[2*4 + 2];
  Titf[2*4 + 3] = -Titi[0*4 + 2]*Titi[0*4 + 3]-Titi[1*4 + 2]*Titi[1*4 + 3]-Titi[2*4 + 2]*Titi[2*4 + 3];
  // forth row  //��4��
  Titf[3*4 + 0] = 0.0;
  Titf[3*4 + 1] = 0.0;
  Titf[3*4 + 2] = 0.0;
  Titf[3*4 + 3] = 1.0;
}

void pos2tran(float* Xpt, float* Tpt)
{
  // pos to homogeneous transformation matrix //�ӵ����굽��α任����
  // first row  //��1��
  Tpt[0*4 + 0] = cos(Xpt[3])*cos(Xpt[4])*cos(Xpt[5])-sin(Xpt[3])*sin(Xpt[5]);
  Tpt[0*4 + 1] = -cos(Xpt[3])*cos(Xpt[4])*sin(Xpt[5])-sin(Xpt[3])*cos(Xpt[5]);
  Tpt[0*4 + 2] = cos(Xpt[3])*sin(Xpt[4]);
  Tpt[0*4 + 3] = Xpt[0];
  // second row //��2��
  Tpt[1*4 + 0] = sin(Xpt[3])*cos(Xpt[4])*cos(Xpt[5])+cos(Xpt[3])*sin(Xpt[5]);
  Tpt[1*4 + 1] = -sin(Xpt[3])*cos(Xpt[4])*sin(Xpt[5])+cos(Xpt[3])*cos(Xpt[5]);
  Tpt[1*4 + 2] = sin(Xpt[3])*sin(Xpt[4]);
  Tpt[1*4 + 3] = Xpt[1];
  // third row  //��3��
  Tpt[2*4 + 0] = -sin(Xpt[4])*cos(Xpt[5]);
  Tpt[2*4 + 1] = sin(Xpt[4])*sin(Xpt[5]);
  Tpt[2*4 + 2] = cos(Xpt[4]);
  Tpt[2*4 + 3] = Xpt[2];
  // forth row  //��4��
  Tpt[3*4 + 0] = 0.0;
  Tpt[3*4 + 1] = 0.0;
  Tpt[3*4 + 2] = 0.0;
  Tpt[3*4 + 3] = 1.0;
}

void DH1line(float thetadh, float alfadh, float rdh, float ddh, float* Tdh)
{
  // creats Denavit-Hartenberg homogeneous transformation matrix  //��������ά-����������α任����
  // first row  //��1��
  Tdh[0*4 + 0] = cos(thetadh);
  Tdh[0*4 + 1] = -sin(thetadh)*cos(alfadh);
  Tdh[0*4 + 2] = sin(thetadh)*sin(alfadh);
  Tdh[0*4 + 3] = rdh*cos(thetadh);
  // second row //��2��
  Tdh[1*4 + 0] = sin(thetadh);
  Tdh[1*4 + 1] = cos(thetadh)*cos(alfadh);
  Tdh[1*4 + 2] = -cos(thetadh)*sin(alfadh);
  Tdh[1*4 + 3] = rdh*sin(thetadh);
  // third row  //��3��
  Tdh[2*4 + 0] = 0.0;
  Tdh[2*4 + 1] = sin(alfadh);
  Tdh[2*4 + 2] = cos(alfadh);
  Tdh[2*4 + 3] = ddh;
  // forth row  //��4��
  Tdh[3*4 + 0] = 0.0;
  Tdh[3*4 + 1] = 0.0;
  Tdh[3*4 + 2] = 0.0;
  Tdh[3*4 + 3] = 1.0;
}


/*
 * MatrixMultiply
 * Matrix Multiplication Routine
 * C = A*B
 * ����ĳ˷�����
 */
void MatrixMultiply(float* A, float* B, int m, int p, int n, float* C)
{
  // A = input matrix (m x p)
  // B = input matrix (p x n)
  // m = number of rows in A
  // p = number of columns in A = number of rows in B
  // n = number of columns in B
  // C = output matrix = A*B (m x n)
  int i, j, k;
  for (i = 0; i < m; i++)
    for(j = 0; j < n; j++)
    {
      C[n * i + j] = 0;
      for (k = 0; k < p; k++)
        C[n * i + j] = C[n * i + j] + A[p * i + k] * B[n * k + j];
    }
}

/*
 * MatrixScale
 * Matrix Scale
 * ��������仯����
 */
void MatrixScale(float* A, int m, int n, float k)
{
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      A[n * i + j] = A[n * i + j] * k;
}

void InverseK(float* Xik, float* Jik)
{
  // from deg to rad    //�Ƕ���ת��������
  // Xik(4:6)=Xik(4:6)*pi/180;
  Xik[3]=Xik[3]*PI/180.0;
  Xik[4]=Xik[4]*PI/180.0;
  Xik[5]=Xik[5]*PI/180.0;
  // Denavit-Hartenberg matrix  //DH����ϵ����
  float theta[6]={0.0, -90.0, 0.0, 0.0, 0.0, 0.0};      // theta=[0; -90+0; 0; 0; 0; 0];    //��
  float alfa[6]={-90.0, 0.0, -90.0, 90.0, -90.0, 0.0};  // alfa=[-90; 0; -90; 90; -90; 0];  //a
  float r[6]={r1, r2, r3, 0.0, 0.0, 0.0};               // r=[47; 110; 26; 0; 0; 0];        //r
  float d[6]={d1, 0.0, d3, d4, 0.0, d6};                // d=[133; 0; 7; 117.5; 0; 28];     //d
  // from deg to rad  //�Ƕ���ת��������
  MatrixScale(theta, 6, 1, PI/180.0);   // theta=theta*pi/180;
  MatrixScale(alfa, 6, 1, PI/180.0);    // alfa=alfa*pi/180;
  // work frame   //��������ϵ
  float Xwf[6]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // Xwf=[0; 0; 0; 0; 0; 0];
  // tool frame   //��������ϵ
  float Xtf[6]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // Xtf=[0; 0; 0; 0; 0; 0];
  // work frame transformation matrix //��������ϵ�任����
  float Twf[16];
  pos2tran(Xwf, Twf); // Twf=pos2tran(Xwf);
  // tool frame transformation matrix //��������ϵ�任����
  float Ttf[16];
  pos2tran(Xtf, Ttf); // Ttf=pos2tran(Xtf);
  // total transformation matrix      //ȫ���ı任����
  float Twt[16];
  pos2tran(Xik, Twt); // Twt=pos2tran(Xik);
  // find T06 //�ҵ� T06
  float inTwf[16], inTtf[16], Tw6[16], T06[16];
  invtran(Twf, inTwf); // inTwf=invtran(Twf);
  invtran(Ttf, inTtf); // inTtf=invtran(Ttf);
  MatrixMultiply(Twt, inTtf, 4, 4, 4, Tw6); // Tw6=Twt*inTtf;
  MatrixMultiply(inTwf, Tw6, 4, 4, 4, T06); // T06=inTwf*Tw6;
  // positon of the spherical wrist //���������λ��
  float Xsw[3];
  // Xsw=T06(1:3,4)-d(6)*T06(1:3,3);
  Xsw[0]=T06[0*4 + 3]-d[5]*T06[0*4 + 2];
  Xsw[1]=T06[1*4 + 3]-d[5]*T06[1*4 + 2];
  Xsw[2]=T06[2*4 + 3]-d[5]*T06[2*4 + 2];
  // joints variable    //�ؽڱ���
  // Jik=zeros(6,1);
  // first joint        //��һ���ؽ�
  Jik[0]=atan2(Xsw[1],Xsw[0])-atan2(d[2],sqrt(Xsw[0]*Xsw[0]+Xsw[1]*Xsw[1]-d[2]*d[2])); // Jik(1)=atan2(Xsw(2),Xsw(1))-atan2(d(3),sqrt(Xsw(1)^2+Xsw(2)^2-d(3)^2));
  // second joint       //�ڶ����ؽ�
  Jik[1] = PI/2.0
           -acos((r[1]*r[1]+(Xsw[2]-d[0])*(Xsw[2]-d[0])+(sqrt(Xsw[0]*Xsw[0]+Xsw[1]*Xsw[1]-d[2]*d[2])-r[0])*(sqrt(Xsw[0]*Xsw[0]+Xsw[1]*Xsw[1]-d[2]*d[2])-r[0])-(r[2]*r[2]+d[3]*d[3]))/(2.0*r[1]*sqrt((Xsw[2]-d[0])*(Xsw[2]-d[0])+(sqrt(Xsw[0]*Xsw[0]+Xsw[1]*Xsw[1]-d[2]*d[2])-r[0])*(sqrt(Xsw[0]*Xsw[0]+Xsw[1]*Xsw[1]-d[2]*d[2])-r[0]))))
           -atan((Xsw[2]-d[0])/(sqrt(Xsw[0]*Xsw[0]+Xsw[1]*Xsw[1]-d[2]*d[2])-r[0])); // Jik(2)=pi/2-acos((r(2)^2+(Xsw(3)-d(1))^2+(sqrt(Xsw(1)^2+Xsw(2)^2-d(3)^2)-r(1))^2-(r(3)^2+d(4)^2))/(2*r(2)*sqrt((Xsw(3)-d(1))^2+(sqrt(Xsw(1)^2+Xsw(2)^2-d(3)^2)-r(1))^2)))-atan((Xsw(3)-d(1))/(sqrt(Xsw(1)^2+Xsw(2)^2-d(3)^2)-r(1)));
  // third joint        //�������ؽ�
  Jik[2]=PI
         -acos((r[1]*r[1]+r[2]*r[2]+d[3]*d[3]-(Xsw[2]-d[0])*(Xsw[2]-d[0])-(sqrt(Xsw[0]*Xsw[0]+Xsw[1]*Xsw[1]-d[2]*d[2])-r[0])*(sqrt(Xsw[0]*Xsw[0]+Xsw[1]*Xsw[1]-d[2]*d[2])-r[0]))/(2*r[1]*sqrt(r[2]*r[2]+d[3]*d[3])))
         -atan(d[3]/r[2]); // Jik(3)=pi-acos((r(2)^2+r(3)^2+d(4)^2-(Xsw(3)-d(1))^2-(sqrt(Xsw(1)^2+Xsw(2)^2-d(3)^2)-r(1))^2)/(2*r(2)*sqrt(r(3)^2+d(4)^2)))-atan(d(4)/r(3));
  // last three joints  //��������ؽ�
  float T01[16], T12[16], T23[16], T02[16], T03[16], inT03[16], T36[16];
  DH1line(theta[0]+Jik[0], alfa[0], r[0], d[0], T01); // T01=DH1line(theta(1)+Jik(1),alfa(1),r(1),d(1));
  DH1line(theta[1]+Jik[1], alfa[1], r[1], d[1], T12); // T12=DH1line(theta(2)+Jik(2),alfa(2),r(2),d(2));
  DH1line(theta[2]+Jik[2], alfa[2], r[2], d[2], T23); // T23=DH1line(theta(3)+Jik(3),alfa(3),r(3),d(3));
  MatrixMultiply(T01, T12, 4, 4, 4, T02); // T02=T01*T12;
  MatrixMultiply(T02, T23, 4, 4, 4, T03); // T03=T02*T23;
  invtran(T03, inT03); // inT03=invtran(T03);
  MatrixMultiply(inT03, T06, 4, 4, 4, T36); // T36=inT03*T06;
  // forth joint      //���ĸ��ؽ�
  Jik[3]=atan2(-T36[1*4+2], -T36[0*4+2]); // Jik(4)=atan2(-T36(2,3),-T36(1,3));
  // fifth joint      //������ؽ�
  Jik[4]=atan2(sqrt(T36[0*4+2]*T36[0*4+2]+T36[1*4+2]*T36[1*4+2]), T36[2*4+2]); // Jik(5)=atan2(sqrt(T36(1,3)^2+T36(2,3)^2),T36(3,3));
  // sixth joints     //�������ؽ�
  Jik[5]=atan2(-T36[2*4+1], T36[2*4+0]); // Jik(6)=atan2(-T36(3,2),T36(3,1));
  // rad to deg       //�Ƕ���ת������
  MatrixScale(Jik, 6, 1, 180.0/PI); // Jik=Jik/pi*180;
}

