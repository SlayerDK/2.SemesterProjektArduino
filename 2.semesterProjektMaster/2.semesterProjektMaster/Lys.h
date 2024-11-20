#define F_CPU 16000000UL  // 16 MHz clock frequency
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUD 9600         // Baud rate til UART
#define MYUBRR F_CPU/16/BAUD-1  // Beregning af UBRR-værdi
#define steps_per_degree 1/0.12


#ifndef LYS_H_
#define LYS_H_
void uart_init(unsigned int ubrr);
void uart_transmit(unsigned char data);
void uart_send_string(const char* str);
void adc_init(void);
uint16_t read_analog(uint8_t channel);





#endif /* LYS_H_ */