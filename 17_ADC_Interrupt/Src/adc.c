#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN			(1U<<0)
#define ADC1EN			(1U<<8)
#define ADC_CH1			(1U<<0)
#define ADC_SEQ_LEN		0x00
#define CR2_ADON		(1U<<0)
#define CR2_SWStart		(1U<<30)
#define CR2_CONT		(1U<<1)
#define CR1_EOCIE		(1U<<5)

void pa1_adc_interrupt_init(void)
{
	// Config ADC GPIO pin


	// enable clock access to GPIOA  pin port (PA1)
	RCC->AHB1ENR |= GPIOAEN;
	// set mode of PA1 to analog mode (mode register)
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);


	// enable clock access to ADC Module
	RCC->APB2ENR |= ADC1EN;

	// Enable ADC end of conversion interrupt
	ADC1->CR1 |= CR1_EOCIE;

	// Enable interrupt in NVIC
	NVIC_EnableIRQ(ADC_IRQn);

	// Conversion sequence start
	ADC1->SQR3 = ADC_CH1;

	// Conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN;

	// Enable the ADC module
	ADC1->CR2 |= CR2_ADON;
}

void pa1_adc_init(void)
{
	// Config ADC GPIO pin


	// enable clock access to GPIOA  pin port (PA1)
	RCC->AHB1ENR |= GPIOAEN;
	// set mode of PA1 to analog mode (mode register)
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);


	// enable clock access to ADC Module
	RCC->APB2ENR |= ADC1EN;

	// Conversion sequence start
	ADC1->SQR3 = ADC_CH1;
	// Conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN;
	// Enable the ADC module
	ADC1->CR2 |= CR2_ADON;
}


void start_conversion(void)
{
	// Enable continuous conversion
	ADC1->CR2 |= CR2_CONT;
	// Start ADC conversion
	ADC1->CR2 |= CR2_SWStart;
}


uint32_t adc_read(void)
{
	// Wait for conversion to complete
	while(!(ADC1->SR & SR_EOC)){}
	// Read converted result
	return (ADC1->DR);
}

