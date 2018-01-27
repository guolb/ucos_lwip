#ifndef __LED_H
#define __LED_H	 

#include "stm32f10x.h"

#define LED0_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_8);
#define LED1_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_9);
#define LED2_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_14);
#define LED3_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_15);

#define LED0_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_8);
#define LED1_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_9);
#define LED2_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_14);
#define LED3_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_15);

void LED_Init(void);//≥ı ºªØ

		 				    
#endif
