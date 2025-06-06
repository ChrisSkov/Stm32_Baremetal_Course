#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

uint32_t sensor_value;
float temp;
int main(void)
{



	uart2_tx_init();
	pa1_adc_init();
	//adc_read();
	start_conversion();

	while(1)
	{
		sensor_value = adc_read();
		temp = (sensor_value * 3.3 / 4096) * 100; // Calculate the temperature
		printf("Sensor value : %d ", (int)((sensor_value * 3 / 4096) * 100) );
		printf("eow");
		for(int i = 0; i < 30000; i++);

	}

}






