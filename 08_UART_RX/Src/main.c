#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN					(1U<<0) // GPIOA ENable
#define PIN5					(1U<<5)

#define LED_PIN					PIN5

// Use debug mode -> live expression. add "key". connect via teraterm.
char key;
int main(void)
{

	// 1. Enable clock access to GPIOA
	// Bitwise OR ( | ). will set the bit to 1 if at least one of the bits are 1. otherwise 0
	RCC->AHB1ENR |= GPIOAEN;

	// 2. Set PA5 as output pin
	GPIOA->MODER |= (1U<<10); // set GPIOA mode register bit 10 to the value of 1
	GPIOA->MODER &=~(1u<<11); // set GPIOA mode register bit 11 to the value of 0


	uart2_rxtx_init();

	while(1)
	{
		key = uart2_read();
		if(key == '1')
		{
			GPIOA->ODR |= LED_PIN;
		}
		else{
			GPIOA->ODR &= ~LED_PIN;
		}
	}

}






