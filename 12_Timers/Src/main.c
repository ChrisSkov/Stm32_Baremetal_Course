#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"


#define GPIOAEN					(1U<<0) // GPIOA ENable

#define PIN5					(1U<<5)
#define LED						PIN5


int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;

	// 2. Set PA5 as output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	uart2_tx_init();
	tim2_1hz_init();


	while(1)
	{
		// Wait for UIF
		while(!(TIM2->SR & SR_UIF)){}
		// Clear UIF
		TIM2->SR &=~SR_UIF;

		printf("A second has passed \n\r");
		GPIOA->ODR ^= LED;


	}

}






