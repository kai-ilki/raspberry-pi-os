#ifndef	_P_UART_H
#define	_P_UART_H

#include "peripherals/base.h"

#define UART_BASE     (PBASE+0x00201000)

#define UART_DR       (UART_BASE + 0x00)
#define UART_FR       (UART_BASE + 0x18)
#define UART_IBRD     (UART_BASE + 0x24)
#define UART_FBRD     (UART_BASE + 0x28)
#define UART_LCRH     (UART_BASE + 0x2C)
#define UART_CR       (UART_BASE + 0x30)
#define UART_IMSC     (UART_BASE + 0x38)
#define UART_MIS      (UART_BASE + 0x40)


#endif  /*_P_UART_H */
