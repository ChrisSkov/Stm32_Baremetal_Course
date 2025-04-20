#include "stm32f4xx.h"

#define GPIOAEN				(1U<<0)
#define PIN5				(1U<<5)
#define LED_PIN				PIN5

int main(void)
{
	// 1. Enable clock access to GPIOA
	// Bitwise OR ( | ). will set the bit to 1 if at least one of the bits are 1. otherwise 0
	RCC->AHB1ENR |= GPIOAEN;

	// 2. Set PA5 as output pin
	GPIOA->MODER |= (1U<<10); // set GPIOA mode register bit 10 to the value of 1

	GPIOA->MODER &=~(1u<<11); // set GPIOA mode register bit 11 to the value of 0

	while(1)
	{


		GPIOA->BSRR = LED_PIN;
		// For loop that counts to 50k acts as a improvised delay function
		for(int i = 0; i<100000; i++);
		GPIOA->BSRR = (1U<<21);
		for(int i = 0; i<100000; i++);
	}
}
