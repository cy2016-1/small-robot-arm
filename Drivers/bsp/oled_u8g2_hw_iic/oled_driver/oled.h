#ifndef __oled_H
#define __oled_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "u8g2.h"



/*

!!!!!!!!!!!!!!!修改IIC句柄，改成自己的句柄!!!!!!!!!!!!!!


main.c ：

			#include "u8g2.h"
			#include "oled.h"
			
			while前：
					u8g2_t u8g2; // 显示器初始化结构体
					u8g2Init(&u8g2);   //显示器调用初始化函数
			

显示函数：

	例子：
		u8g2_ClearBuffer(&u8g2);//先清除缓存
		u8g2_DrawFilledEllipse(&u8g2,64,32,60,30 ,U8G2_DRAW_ALL);//写入缓存
		u8g2_SendBuffer(&u8g2);//刷新屏幕


		u8g2_ClearBuffer(&u8g2);//先清除缓存
		u8g2_DrawFilledEllipse(&u8g2,64,32,60,30 ,U8G2_DRAW_ALL);//写入缓存
		u8g2_DrawLine(u8g2, 0, 0, 127, 0);  //画直线,从(0,0)到(127,0)
		u8g2_DrawPixel(u8g2, 115, 32); //画点(115，32)
		u8g2_DrawBox(u8g2,56,44,14,10);   //画实心矩形(x,y,w,h)
		u8g2_DrawFrame(u8g2,5,24,18,16);  //画空心矩
		u8g2_SendBuffer(&u8g2);//刷新屏幕


*****************     一些常用函数       ******************************************

			u8g2_DrawLine(u8g2, 0, 0, 127, 0);  //画直线,从(0,0)到(127,0)
			u8g2_DrawPixel(u8g2, 115, 32); //画点(115，32)
			u8g2_DrawBox(u8g2,56,44,14,10);   //画实心矩形(x,y,w,h)
			u8g2_DrawFrame(u8g2,5,24,18,16);  //画空心矩形
			
			u8g2_DrawRFrame(u8g2,16,40,80,10,4);//圆角矩形空心(x,y,w,h,r)
			u8g2_DrawRBox(u8g2,16,40,80,10,4);//圆角矩形实心
			
			u8g2_DrawEllipse(x,y,w,,h,U8G2_DRAW_ALL)	//空心椭圆
			u8g2_DrawFilledEllipse(x,y,w,h,U8G2_DRAW_ALL)//实心椭圆
			u8g2_DrawDisc(x,y,r,U8G2_DRAW_ALL)		//画实心圆
			u8g2_DrawCircle(u8g2,62,13,10,U8G2_DRAW_ALL); //画空心圆形(X,Y,R,形状)
				U8G2_DRAW_UPPER_RIGHT  右上1/4
				U8G2_DRAW_UPPER_LEFT   左上1/4
				U8G2_DRAW_LOWER_LEFT   左下1/4
				U8G2_DRAW_LOWER_RIGHT  右下1/4
				U8G2_DRAW_ALL					 全部

			u8g2_DrawXBMP(&u8g2,0,0,128,64,array);//显示图片(x,y,w,h,array)
			u8g2_DrawXBM(&u8g2,0,0,128,64,array);//显示图片(x,y,w,h,array)

			u8g2_SetFont(u8g2, u8g2_font_6x12_tf);  //设定字体大小
			u8g2_DrawStr(u8g2, 80,36,"YYDS");    		//显示字符

			u8g2_SetFontDirection(u8g2, 1); 				//字体方向选择【0=竖向，1=横向】
			u8g2_SetFont(u8g2, u8g2_font_inb16_mf); //字库选择

			u8g2_DrawHLine(u8g2, 2, 35, 47);				//水平线段(x,y,len)
			u8g2_DrawVLine(u8g2, 45, 32, 12);				//垂直线段(x,y,len)
			
*********************************************************************************************
*/



#define HI2C hi2c1

#define u8         unsigned char  // ?unsigned char ????
#define MAX_LEN    128  //
#define OLED_ADDRESS  0x78 // oled模块从机地址
#define OLED_CMD   0x00  // 写命令
#define OLED_DATA  0x40  // 写数据
 
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
