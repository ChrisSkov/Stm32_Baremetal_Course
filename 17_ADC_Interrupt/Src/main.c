#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"


static void adc_callback(void);

uint32_t sensor_value;
float temp;
int main(void)
{



	uart2_tx_init();
	pa1_adc_interrupt_init();
	//adc_read();
	start_conversion();

	while(1)
	{



	}

}

static void adc_callback(void)
{
	sensor_value = ADC1->DR;
	temp = (sensor_value * 3.3 / 4096) * 100; // Calculate the temperature
	printf("Sensor value: %f \n\r", temp );

}

void ADC_IRQHandler(void)
{
	// Check for eoc in status register (SR)
	if((ADC1->SR & SR_EOC) != 0)
	{
		// Clear EOC
		ADC1->SR &=~SR_EOC;
		// Do something
		adc_callback();
	}
}




