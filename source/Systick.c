
#include "Systick.h"

static __IO uint32_t usTicks;
static uint64_t usCount;
void SysTick_Handler()
{
	if (usTicks != 0)
	{
		usTicks--;
	}
	usCount++;
}
void systick_init(){
	// Update SystemCoreClock value
	usCount=0;
	SystemCoreClockUpdate();
	// Configure the SysTick timer to overflow every 100 us
	SysTick_Config(SystemCoreClock / 10000);
}
uint64_t get_us_count(){
	return usCount;
}


