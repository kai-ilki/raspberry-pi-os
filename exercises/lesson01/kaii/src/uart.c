#include "utils.h"
#include "peripherals/uart.h"
#include "peripherals/gpio.h"

#define UART_DR_DATA_MASK 0xFF

void uart_send(char c)
{
	const unsigned int TXFF = 1 << 7;
	while (1)
	{
		if (get32(UART_FR) & TXFF)
			break;
	}
	put32(UART_DR, c);
}

char uart_recv(void)
{
	const unsigned int RXFF = 1 << 6;
	while (1)
	{
		if (get32(UART_FR) & RXFF)
			break;
	}
	return (get32(UART_DR) & UART_DR_DATA_MASK);
}

void uart_send_string(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		uart_send((char)str[i]);
	}
}

// try to put bit!
void uart_control_init(void){
	/*
	Program the control registers as follows:
	1. Disable the UART.
	2. Wait for the end of transmission or reception of the current character.
	3. Flush the transmit FIFO by setting the FEN bit to 0 in the Line Control Register, UART_LCRH.
	4. Reprogram the Control Register, UART_CR.
	5. Enable the UART.
	*/
	put32(UART_CR, 0); // disable UART

	unsigned int control = 1;  // enable UART
	control |= (1 << 8);	   // enable TXE
	control |= (1 << 9);	   // enable RXE
	put32(UART_CR, control);
}

void uart_init(void)
{
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7 << 12); // clean gpio14
	selector |= 2 << 12;	// set alt5 for gpio14
	selector &= ~(7 << 15); // clean gpio15
	selector |= 2 << 15;	// set alt5 for gpio15
	put32(GPFSEL1, selector);

    put32(GPPUD, 0);
    delay(150);
    put32(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    put32(GPPUDCLK0, 0);

    put32(UART_LCRH, 0b11 << 5); // Set Word length to 8 bit

	uart_control_init();
}