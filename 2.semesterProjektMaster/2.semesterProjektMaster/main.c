#define F_CPU 16000000UL  // 16 MHz clock speed
#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>
#include <stdlib.h>  // Tilføj til at bruge itoa()

int watt = 0;
int sol = 0;

int main(void) {
	
	while(1)
	{
		getSteps();
		_delay_ms(1000);
	}
	return 0;
}
