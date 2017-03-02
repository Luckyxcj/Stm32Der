#ifndef __LCD_5510_MAIN_H__
#define __LCD_5510_MAIN_H__

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

//LCD¶Ë¿Ú¶¨Òå
#define NOKIA5110_CLK_H	HAL_GPIO_WritePin(CLK_5510_GPIO_Port, CLK_5510_Pin, GPIO_PIN_SET);
#define NOKIA5110_DIN_H	HAL_GPIO_WritePin(DIN_5510_GPIO_Port, DIN_5510_Pin, GPIO_PIN_SET);
#define NOKIA5110_DC_H	HAL_GPIO_WritePin(DC_5510_GPIO_Port,  DC_5510_Pin,  GPIO_PIN_SET);
#define NOKIA5110_CE_H	HAL_GPIO_WritePin(CE_5510_GPIO_Port,  CE_5510_Pin,  GPIO_PIN_SET);
#define NOKIA5110_RST_H HAL_GPIO_WritePin(RST_5510_GPIO_Port, RST_5510_Pin, GPIO_PIN_SET);
#define NOKIA5110_BL_H  HAL_GPIO_WritePin(BL_5510_GPIO_Port,  BL_5510_Pin,  GPIO_PIN_SET);
//#define NOKIA5110_LED_ON	P2OUT |= BIT0

#define NOKIA5110_CLK_L	HAL_GPIO_WritePin(CLK_5510_GPIO_Port, CLK_5510_Pin, GPIO_PIN_RESET);
#define NOKIA5110_DIN_L	HAL_GPIO_WritePin(DIN_5510_GPIO_Port, DIN_5510_Pin, GPIO_PIN_RESET);
#define NOKIA5110_DC_L	HAL_GPIO_WritePin(DC_5510_GPIO_Port,  DC_5510_Pin,  GPIO_PIN_RESET);
#define NOKIA5110_CE_L	HAL_GPIO_WritePin(CE_5510_GPIO_Port,  CE_5510_Pin,  GPIO_PIN_RESET);
#define NOKIA5110_RST_L HAL_GPIO_WritePin(RST_5510_GPIO_Port, RST_5510_Pin, GPIO_PIN_RESET);
//#define NOKIA5110_LED_OFF	P2OUT &= ~BIT0

#define SCLK_H  NOKIA5110_CLK_H
#define SDIN_H  NOKIA5110_DIN_H
#define LCD_DC_H NOKIA5110_DC_H
#define LCD_CE_H NOKIA5110_CE_H
#define LCD_RST_H NOKIA5110_RST_H
#define SCLK_L NOKIA5110_CLK_L
#define SDIN_L NOKIA5110_DIN_L
#define LCD_DC_L NOKIA5110_DC_L
#define LCD_CE_L NOKIA5110_CE_L
#define LCD_RST_L NOKIA5110_RST_L
//#define NOKIA5110_BL_H  HAL_GPIO_WritePin(BL_5510_GPIO_Port,  BL_5510_Pin,  GPIO_PIN_SET);
//#define NOKIA5110_LED_ON	P2OUT |= BIT0

extern void LCD_init(void)	;
extern void LCD_clear(void);
extern void LCD_set_XY(unsigned char X, unsigned char Y) ;
extern void LCD_write_char(unsigned char c) ;
extern void LCD_write_english_string(unsigned char X,unsigned char Y,char *s)	;
extern void LCD_write_num_string(unsigned char X,unsigned char Y,const char *name,int i);
extern void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map,
                  unsigned char Pix_x,unsigned char Pix_y);
extern void LCD_write_byte(unsigned char dat, unsigned char command) ;

#endif/*__LCD_5510_MAIN_H__*/
