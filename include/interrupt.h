#include "stm32f10x.h"
#include "led.h"
#include "delay.h"


void EXTI1_IRQHandler(void);
void interrupt_init(uint32_t RCC_APB2Periph_GPIOX ,uint32_t GPIO_Pin_X, uint32_t GPIO_PortSourceGPIOX, 
	uint32_t GPIO_PinSourceX, uint32_t EXTI_LineX, uint32_t EXTIX_IRQn,uint8_t NVIC_IRQChannelPreemptionPriorityX);
uint8_t read_interrupt ();
void init_current_status(int *current_status, int *current_step);

