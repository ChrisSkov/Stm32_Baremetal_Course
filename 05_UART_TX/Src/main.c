#include "stm32f4xx.h"

#define GPIOAEN				(1U<<0)
#define UART2EN				(1U<<17)

#define CR1_TE				(1U<<3)
#define CR1_UE				(1U<<13)

#define SYS_FREQ			16000000
#define APB1_CLK			SYS_FREQ

#define UART_BAUDRATE		115200



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate );
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate);


int main(void)
{


	while(1)
	{

	}
}


void uar2_tx_init(void)
{
	// Config uart GPIO pin
	// Enable clock access to gpioa
	RCC->AHB1ENR |=GPIOAEN;
	// Set PA2 mode to alternate function mode
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |=(1U<<5);
	// Set PA2 alternate function type to UART_TX (AF07)
	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	// Enable clock access to uart2
	RCC->AHB1ENR |= UART2EN;

	// Config baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// config the transfer direction
	USART2->CR1 = CR1_TE;

	// enable the uart module
	USART2->CR1 |= CR1_UE;

}


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate )
{
	USARTx->BRR = compute_uart_bd(PeriphClk, Baudrate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate)
{
	return ((PeriphClk + (Baudrate/2U))/Baudrate);
}

