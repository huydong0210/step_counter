#include "stm32f10x.h"
#include "lcd16x2.h"
#include "delay.h"
#include "i2c.h"
#include "i2c_mpu6050.h"
#include "led.h"
#include "Systick.h"


#define ACTIVE 1
#define INACTIVE 0
#define GREEN_LED 2
#define RED_LED 3

#define LED_STATUS_ON 1
#define LED_STATUS_OFF 0


void caculate_init_average();
