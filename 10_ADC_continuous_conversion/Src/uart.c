#include "uart.h"


#define GPIOAEN				(1U<<0)
#define UART2EN				(1U<<17)

// CR1 = control register. Reference manual page839. USART_CR1
#define CR1_TE				(1U<<3)  // Control Register1 Transmit Enable
#define CR1_RE				(1U<<2)  // Control Register1 Reciever Enable ( Reference manual page 838/839)

#define CR1_UE				(1U<<13) // Control Register1 USART Enable
#define SR_TXE				(1U<<7)  // USART status register
#define SR_RXNE				(1U<<5)  // USART status register

#define SYS_FREQ			16000000
#define APB1_CLK			SYS_FREQ // APB1_Clock

#define UART_BAUDRATE		115200


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_write(int ch);


int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void uart2_tx_init(void)
{
	/****************Configure uart gpio pin***************/
	/*Enable clock access to gpioa */
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*Set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);


	/****************Configure uart module ***************/
	/*Enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/*Configure baudrate*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

	/*Configure the transfer direction*/
	 USART2->CR1 =  CR1_TE;

	/*Enable uart module*/
	 USART2->CR1 |= CR1_UE;


}
void uart2_rxtx_init(void)
{
	/****************Configure uart gpio pin***************/
	/*Enable clock access to gpioa */
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*Set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/*Set PA3 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);
	/*Set PA3 alternate function type to UART_RX (AF07)*/
	GPIOA->AFR[0] |= (1U<<12); // Set bit 12
	GPIOA->AFR[0] |= (1U<<13); // Set bit 13
	GPIOA->AFR[0] |= (1U<<14); // Set bit 14
	GPIOA->AFR[0] &= ~(1U<<15); // REset bit 15

	/****************Configure uart module ***************/
	/*Enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/*Configure baudrate*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

	/*Configure the transfer direction*/
	 USART2->CR1 =  (CR1_TE | CR1_RE);

	/*Enable uart module*/
	 USART2->CR1 |= CR1_UE;


}


char uart2_read(void)
{

	// Make sure the receive data register is NOT empty
	// Reference manual page 835. RXNE
	while(!(USART2->SR & SR_RXNE)){}

	// Return the data
	return USART2->DR; // USART data registry


}


void uart2_write(int ch)
{
	while(!(USART2->SR & SR_TXE)){}

	 /*Write to transmit data register*/
		USART2->DR	=  (ch & 0xFF);
}




static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate)
{
	USARTx->BRR =  compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

