#include "stm32f10x.h"
#include "delay.h"


// khoi tao timer2
void delay_init(void){
	TIM_TimeBaseInitTypeDef timerInit;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	timerInit.TIM_Period = 0xFFFF;
	timerInit.TIM_Prescaler = 64 - 1;
	TIM_TimeBaseInit(TIM2, &timerInit);
}
void delay_1_ms(void){
	
	TIM_Cmd(TIM2, ENABLE);
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < 1000) {
	}
	TIM_Cmd(TIM2, DISABLE);
}
void delay_ms(uint32_t time){
	while (time) {
		delay_1_ms();
		time--;
	}
	
}

void delay_us(uint32_t time){
	TIM_Cmd(TIM2, ENABLE);
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < time) {
	}
	TIM_Cmd(TIM2, DISABLE);
	
}