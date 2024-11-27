

#ifndef MASTER_H_
#define MASTER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>  // Tilføj til at bruge itoa()

#include "Lys.h"
#include "Motor.h"
#include "Effekt.h"
#include "Kommunikation.h"

#define BAUD 9600              // Baud rate til UART
#define MYUBRR F_CPU/16/BAUD-1 // Beregning af UBRR-værdi
#define MAX_ADC_VALUE 1023 // Maksimal ADC-værdi (10-bit ADC)
#define steps_per_degree 10 // Antal trin pr. grad (afhængig af motor)


// Definer motor pins
#define STEP_PIN1 0
#define DIR_PIN1 1
#define STEP_PIN2 2
#define DIR_PIN2 3

//definer pins til effektmåler
#define VOLTAGE_PIN 5
#define CURRENT_PIN 4

void uart_init(unsigned int ubrr);           // Initialiser UART
void uart_send_char(unsigned char data);      // Transmitér én byte via UART
void uart_send_string(const char* str);      // Send en streng via UART
uint16_t read_analog(uint8_t channel);
void getSteps();


#endif /* MASTER_H_ */