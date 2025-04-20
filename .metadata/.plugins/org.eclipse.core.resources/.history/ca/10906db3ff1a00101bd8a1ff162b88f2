// Where is LED connected?
// Port:	 A
// Pin: 	 5

#define PERIPH_BASE 			(0x40000000UL)
#define AHB1PERIPH_OFFSET 		(0x00020000UL)
#define AHB1PERIPH_BASE 		(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET			(0x0000UL)
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET			(0x30UL)
#define RCC_AHB1EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET			(0x00UL)
#define GPIOA_MODE_R_			(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET)) // MODE register

#define OD_R_OFFSET				(0x14UL)
#define GPIOA_OD_R				(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET)) // output register

#define GPIOAEN					(1U<<0) // GPIOA ENable

#define PIN5					(1U<<5)
#define LED_PIN					PIN5

/* (1U<<10)
 * &=~(1U<<11)
0x4002 0000


*/




int main(void)
{
	// 1. Enable clock access to GPIOA
	// Bitwise OR ( | ). will set the bit to 1 if at least one of the bits are 1. otherwise 0
	RCC_AHB1EN_R |= GPIOAEN;

	// 2. Set PA5 as output pin
	GPIOA_MODE_R_ |= (1U<<10); // set GPIOA mode register bit 10 to the value of 1
	GPIOA_MODE_R_ &=~(1U<<11); // set GPIOA mode register bit 11 to the value of 0

	while(1)
	{
		// set PA5 high
		//GPIOA_OD_R |= LED_PIN;
		// Use toggle operator ( ^ ) to toggle pin on/off
		GPIOA_OD_R ^= LED_PIN;
		// For loop that counts to 50k acts as a improvised delay function
		for(int i = 0; i<500000; i++);
	}
}


