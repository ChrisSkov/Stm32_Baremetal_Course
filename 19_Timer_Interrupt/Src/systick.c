#include "stm32f4xx.h"


#define SYSTICK_LOAD_VAL			16000 //
#define CTRL_ENABLE					(1U<<0) //Enable control register
#define CTRL_CLKSRC					(1U<<2) // Clock source is set to internal (system clock)
#define CTRL_COUNTFLAG				(1U<<16)

void systickDelayMs(int delay)
{
	// Configure systick
	// reload with number of clocks per miliseconds
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	// Clear systick current value register
	SysTick->VAL = 0;

	// Enable systick and select internal clock src
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i=0; i<delay ; i++){
		//Wait until the COUNTFLAG is set

		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0) {}
	}
	SysTick->CTRL = 0;

}
