/* simple uart library */

#ifndef __UART_H_
#define __UART_H_

int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);

void uart_init(void);

#endif
