#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"



#define GPIOAEN					(1U<<0) // GPIOA ENable

#define PIN5					(1U<<5)
#define LED						PIN5

void systick_callback(void);

int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;

	// 2. Set PA5 as output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	uart2_tx_init();
	systick_1hz_interrupt();


	while(1)
	{



	}

}

void systick_callback(void)
{
	printf("A second has passed \n\r");
	GPIOA->ODR ^= LED;
}

void SysTick_Handler(void)
{
	// Do something...
	systick_callback();
}




