/*
 * solcelle1.c
 *
 * Created: 18-11-2024 10:39:56
 * Author : frederikpost
 */ 

#include "solcelle.h"
#include "uart.h"
#include <avr/io.h>

int main(void) {
	setup_sensors();  // Setup UART and ADC

	while (1) {
		measure_and_print();  // Measure values and print via UART
	}

	return 0;
}