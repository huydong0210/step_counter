#include "main.h"


float x_init=0, y_init=0, z_init=0;
float threshold=1400;
float minave = 0;
float maxave = 0;
int sampling = 0;
float ave=0;
int status;
int step=0;
int led_status;
uint64_t hold = 1000000;
int led_green_status;

void reset_systick();

uint32_t clk;
int main(void){
	//--------------- Init--------
	delay_init();
	lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	led_init();
	I2C_MPU6050_Setup();

	// stop button
	interrupt_init(RCC_APB2Periph_GPIOB, GPIO_Pin_0, GPIO_PortSourceGPIOB, GPIO_PinSource0, EXTI_Line0, EXTI0_IRQn, 0x01);
	interrupt_init(RCC_APB2Periph_GPIOB, GPIO_Pin_1, GPIO_PortSourceGPIOB, GPIO_PinSource1,  EXTI_Line1, EXTI1_IRQn, 0x00);
	
	init_current_status(&status, &step);
	

	
  led_green_status = LED_STATUS_ON;
	status = ACTIVE;
	float x_pre=0, y_pre=0, z_pre=1000;
	int flag=0;
	
	
	lcd16x2_puts("Starting....");
	caculate_init_average();
	lcd16x2_clrscr();
	lcd16x2_put_int(step);
	
	turn_on_green_led();
	systick_init();
	while (1){
		if (status == ACTIVE && led_green_status == LED_STATUS_ON && get_us_count() >= 10000){
			turn_off_green_led();
			led_green_status=LED_STATUS_OFF;
			systick_init();
		}
		if (status == ACTIVE && led_green_status == LED_STATUS_OFF && get_us_count() >= 10000){
			turn_on_green_led();
			led_green_status=LED_STATUS_ON;
			systick_init();
		}
		if (status == INACTIVE){
			turn_on_red_led();
			turn_off_green_led();
			lcd16x2_gotoxy(0,1);
			lcd16x2_puts("Inactive");
			
		} else if (status == ACTIVE){
			turn_off_red_led();
//			turn_on_green_led();
			float *accel_data;
			accel_data = CTR_READ_ACCEL_MPU6050();
			float x, y, z;
			
			x= accel_data[0];
			y= accel_data[1];
			z= accel_data[2];
			
			if (x - x_pre >3000){
				x = x_pre;
			}
			if (y - y_pre >3000) {
				y = y_pre;
			}
			if (z - z_pre >3000){
				z = z_pre;
			}
			
			x_pre = x;
			y_pre = y;
			z_pre = z;
			
			ave = sqrt((x - x_init) * (x - x_init) + (y - y_init) * (y - y_init) + (z - z_init) * (z - z_init));
			
			if (sampling ==0){
				maxave = ave;
				minave = ave;
			} else {
				if (maxave < ave){
					maxave = ave;
				}
				if (minave > ave){
					minave = ave;
				}
			}
			
			sampling++;
			if (sampling >=50){
				threshold = (maxave + minave) / 2 + 285;
				sampling = 0;
			} 
			if (ave > threshold && flag ==0){
				step++;
				lcd16x2_clrscr();
				lcd16x2_puts("Steps: ");
				lcd16x2_put_int(step);
				lcd16x2_gotoxy(0,1);
				lcd16x2_puts("Active");
				flag=1;
			} else if (ave >threshold && flag ==1){
					lcd16x2_clrscr();
					lcd16x2_puts("Steps: ");
					lcd16x2_put_int(step);
					lcd16x2_gotoxy(0,1);
					lcd16x2_puts("Active");
			} else if (ave < threshold && flag==1){
					flag =0;
					lcd16x2_clrscr();
					lcd16x2_puts("Steps: ");
					lcd16x2_put_int(step);
					lcd16x2_gotoxy(0,1);
					lcd16x2_puts("Active");
			} else {
					lcd16x2_clrscr();
					lcd16x2_puts("Steps: ");
					lcd16x2_put_int(step);
					lcd16x2_gotoxy(0,1);
					lcd16x2_puts("Active");
			}
			
			
		}
		
	}
}

void caculate_init_average(){
	float * accel_data;
	float sumx=0,sumy=0,sumz=0;
	float x_pre_init = 0, y_pre_init = 0, z_pre_init = 1000;
	int i;
	for (i=0;i<100;i++){
		I2C_MPU6050_Setup();
		I2C_MPU6050_Init();
		accel_data = CTR_READ_ACCEL_MPU6050();
		
		float x = accel_data[0];
		float y = accel_data[1];
		float z = accel_data[2];
		if (x - x_pre_init > 3000 || y - y_pre_init >3000 || z - z_pre_init > 3000){
			x= x_pre_init;
			y= y_pre_init;
			z= z_pre_init;
		}
		
		x_pre_init = x;
		y_pre_init = y;
		z_pre_init = z;
		
		
		sumx=sumx + x;
		delay_ms(10);
		sumy=sumy+ y;
		delay_ms(10);
		sumz=sumz + z;
		delay_ms(10);

	}
	x_init=sumx/i;
	y_init=sumy/i;
	z_init=sumz/i;
	
}



