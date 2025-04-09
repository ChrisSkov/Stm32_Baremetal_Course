// Where is LED connected?
// Port:	 A
// Pin: 	 5
#include "stdint.h"

#define PERIPH_BASE 			(0x40000000UL)
#define AHB1PERIPH_OFFSET 		(0x00020000UL)
#define AHB1PERIPH_BASE 		(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET			(0x0000UL)
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)


#define GPIOAEN					(1U<<0) // GPIOA ENable

#define PIN5					(1U<<5)
#define LED_PIN					PIN5

#define __IO volatile

typedef struct
{
  volatile uint32_t DUMMY[12];
  volatile uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */

} RCC_TypeDef;


typedef struct
{
	  volatile uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
	  volatile uint32_t DUMMY[4];
	  volatile uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */


}GPIO_TypeDef;

#define RCC			((RCC_TypeDef*) RCC_BASE)
#define GPIOA		((GPIO_TypeDef*) GPIOA_BASE)
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

		// Use toggle operator ( ^ ) to toggle pin on/off
		GPIOA->ODR ^=LED_PIN;
		// For loop that counts to 50k acts as a improvised delay function
		for(int i = 0; i<500000; i++);
	}
}


