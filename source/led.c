#include "led.h"
void led_init(void){
	GPIO_InitTypeDef gpioInit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_7;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &gpioInit);
	
}


void turn_on_green_led(void){
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
}


void turn_on_red_led(void){
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
}

void turn_off_green_led(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

void turn_off_red_led(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
}