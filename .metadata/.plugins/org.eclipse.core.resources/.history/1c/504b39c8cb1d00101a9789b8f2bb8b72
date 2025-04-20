#include "stm32f4xx.h"

#define GPIOAEN				(1U<<0)
#define GPIOCEN				(1U<<2)

#define PIN5				(1U<<5)
#define PIN13				(1U<<13)

#define LED_PIN				PIN5
#define BTN_PIN				PIN13

int main(void)
{
	// Enable clock access to GPIOA and GPIOC
	// Bitwise OR ( | ). will set the bit to 1 if at least one of the bits are 1. otherwise 0
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	// Set PA5 as output pin
	GPIOA->MODER |= (1U<<10); // set GPIOA mode register bit 10 to the value of 1
	GPIOA->MODER &=~(1U<<11); // set GPIOA mode register bit 11 to the value of 0

	// Set PC13 as input pin
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	while(1)
	{
		// Check if button is pressed
		if(GPIOC->IDR & BTN_PIN)
		{
			GPIOA->BSRR = LED_PIN;
		}
		else{
			GPIOA->BSRR = (1U<<21);
		}
	}
}
