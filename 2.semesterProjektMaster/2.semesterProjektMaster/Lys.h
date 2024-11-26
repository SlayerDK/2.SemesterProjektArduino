#ifndef LYS_H_
#define LYS_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// Konstanter og makroer
#define F_CPU 16000000UL       // 16 MHz clock frequency
#define BAUD 9600              // Baud rate til UART
#define MYUBRR F_CPU/16/BAUD-1 // Beregning af UBRR-værdi
#define steps_per_degree (1/0.12) // Antal trin pr. grad (afhængig af motor)

#define MAX_ADC_VALUE 1023 // Maksimal ADC-værdi (10-bit ADC)

// Funktionsprototyper
void uart_init(unsigned int ubrr);           // Initialiser UART
void uart_transmit(unsigned char data);      // Transmitér én byte via UART
void uart_send_string(const char* str);      // Send en streng via UART
void adc_init(void);                         // Initialiser ADC
uint16_t read_analog(uint8_t channel);       // Læs analog værdi fra en given kanal

void getSteps(); // Beregn motorbevægelser
uint16_t calculate_sun_position(uint16_t sensor1, uint16_t sensor2, uint16_t correctionSize); // Beregn trin

#endif /* LYS_H_ */
