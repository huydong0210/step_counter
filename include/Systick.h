#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

void systick_init();

void SysTick_Handler();

uint64_t get_us_count();

