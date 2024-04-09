#ifndef __oled_H
#define __oled_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "u8g2.h"



/*

!!!!!!!!!!!!!!!�޸�IIC������ĳ��Լ��ľ��!!!!!!!!!!!!!!


main.c ��

			#include "u8g2.h"
			#include "oled.h"
			
			whileǰ��
					u8g2_t u8g2; // ��ʾ����ʼ���ṹ��
					u8g2Init(&u8g2);   //��ʾ�����ó�ʼ������
			

��ʾ������

	���ӣ�
		u8g2_ClearBuffer(&u8g2);//���������
		u8g2_DrawFilledEllipse(&u8g2,64,32,60,30 ,U8G2_DRAW_ALL);//д�뻺��
		u8g2_SendBuffer(&u8g2);//ˢ����Ļ


		u8g2_ClearBuffer(&u8g2);//���������
		u8g2_DrawFilledEllipse(&u8g2,64,32,60,30 ,U8G2_DRAW_ALL);//д�뻺��
		u8g2_DrawLine(u8g2, 0, 0, 127, 0);  //��ֱ��,��(0,0)��(127,0)
		u8g2_DrawPixel(u8g2, 115, 32); //����(115��32)
		u8g2_DrawBox(u8g2,56,44,14,10);   //��ʵ�ľ���(x,y,w,h)
		u8g2_DrawFrame(u8g2,5,24,18,16);  //�����ľ�
		u8g2_SendBuffer(&u8g2);//ˢ����Ļ


*****************     һЩ���ú���       ******************************************

			u8g2_DrawLine(u8g2, 0, 0, 127, 0);  //��ֱ��,��(0,0)��(127,0)
			u8g2_DrawPixel(u8g2, 115, 32); //����(115��32)
			u8g2_DrawBox(u8g2,56,44,14,10);   //��ʵ�ľ���(x,y,w,h)
			u8g2_DrawFrame(u8g2,5,24,18,16);  //�����ľ���
			
			u8g2_DrawRFrame(u8g2,16,40,80,10,4);//Բ�Ǿ��ο���(x,y,w,h,r)
			u8g2_DrawRBox(u8g2,16,40,80,10,4);//Բ�Ǿ���ʵ��
			
			u8g2_DrawEllipse(x,y,w,,h,U8G2_DRAW_ALL)	//������Բ
			u8g2_DrawFilledEllipse(x,y,w,h,U8G2_DRAW_ALL)//ʵ����Բ
			u8g2_DrawDisc(x,y,r,U8G2_DRAW_ALL)		//��ʵ��Բ
			u8g2_DrawCircle(u8g2,62,13,10,U8G2_DRAW_ALL); //������Բ��(X,Y,R,��״)
				U8G2_DRAW_UPPER_RIGHT  ����1/4
				U8G2_DRAW_UPPER_LEFT   ����1/4
				U8G2_DRAW_LOWER_LEFT   ����1/4
				U8G2_DRAW_LOWER_RIGHT  ����1/4
				U8G2_DRAW_ALL					 ȫ��

			u8g2_DrawXBMP(&u8g2,0,0,128,64,array);//��ʾͼƬ(x,y,w,h,array)
			u8g2_DrawXBM(&u8g2,0,0,128,64,array);//��ʾͼƬ(x,y,w,h,array)

			u8g2_SetFont(u8g2, u8g2_font_6x12_tf);  //�趨�����С
			u8g2_DrawStr(u8g2, 80,36,"YYDS");    		//��ʾ�ַ�

			u8g2_SetFontDirection(u8g2, 1); 				//���巽��ѡ��0=����1=����
			u8g2_SetFont(u8g2, u8g2_font_inb16_mf); //�ֿ�ѡ��

			u8g2_DrawHLine(u8g2, 2, 35, 47);				//ˮƽ�߶�(x,y,len)
			u8g2_DrawVLine(u8g2, 45, 32, 12);				//��ֱ�߶�(x,y,len)
			
*********************************************************************************************
*/



#define HI2C hi2c1

#define u8         unsigned char  // ?unsigned char ????
#define MAX_LEN    128  //
#define OLED_ADDRESS  0x78 // oledģ��ӻ���ַ
#define OLED_CMD   0x00  // д����
#define OLED_DATA  0x40  // д����
 
/* USER CODE BEGIN Prototypes */
 uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
 uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
 void u8g2Init(u8g2_t *u8g2);


void draw(u8g2_t *u8g2);
void testDrawPixelToFillScreen(u8g2_t *u8g2);


 #ifdef __cplusplus
}
#endif
#endif /*__ i2c_H */
/* USER CODE END Prototypes */
