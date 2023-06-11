#include "interrupt.h"
#include "led.h"
#include "main.h"
static int *status, *step ;

void init_current_status(int *current_status, int *current_step){
	status = current_status;
	step =current_step;
	
}
void EXTI0_IRQHandler()
{
					
  
		if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
       
			 if (*status == ACTIVE){
				 *status = INACTIVE;
				 turn_off_green_led();
				 turn_on_red_led();
			 } else if (*status == INACTIVE){
				 *status = ACTIVE;
				 turn_on_green_led();
				 turn_off_red_led();
			 }
			 delay_ms(500);
			 EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

void EXTI1_IRQHandler()
{
					
  
		if (EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        
				*step=0;
				delay_ms(700);
			EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

void interrupt_init(uint32_t RCC_APB2Periph_GPIOX ,uint32_t GPIO_Pin_X, uint32_t GPIO_PortSourceGPIOX, uint32_t GPIO_PinSourceX, 
	uint32_t EXTI_LineX, uint32_t EXTIX_IRQn,uint8_t NVIC_IRQChannelPreemptionPriorityX)
{
    GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // Bu?c 1: B?t clock cho GPIOB
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOX, ENABLE);

    // Bu?c 2: C?u hình chân GPIOB_PIN_0 là chân ngõ vào v?i pull-down
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_X;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Bu?c 3: C?u hình ng?t ngoài EXTI0
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOX, GPIO_PinSourceX);
		EXTI_InitStructure.EXTI_Line = EXTI_LineX;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
   
    // Bu?c 4: C?u hình uu tiên và cho phép ng?t ngoài EXTI0
    NVIC_InitStructure.NVIC_IRQChannel = EXTIX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriorityX;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
}
