#include "Lys.h"
#include "motor.h"

// Initialiser UART med den ?nskede baud rate
void uart_init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8);  // S?t ?vre byte af baud rate
	UBRR0L = (unsigned char)ubrr;        // S?t nedre byte af baud rate
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Aktiv?r transmitter og receiver
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit
}

// Send en karakter via UART
void uart_transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));  // Vent p?, at bufferen er klar
	UDR0 = data;  // Send data
}

// Send en streng via UART
void uart_send_string(const char* str) {
	while (*str) {
		uart_transmit(*str++);
	}
}

// Initialiser ADC med AVcc som reference og prescaler til 128
void adc_init(void) {
	ADMUX = (1 << REFS0);  // Brug AVcc som reference
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Aktiv?r ADC og prescaler 128
}

// Generel funktion til at l?se analog v?rdi fra en specificeret kanal (0-7)
uint16_t read_analog(uint8_t channel) {
	//channel 0 = top, 1 = bottom, 2 = left, 3 = right
	channel &= 0x07;  // Begr?ns kanalen til 0-7
	ADMUX = (ADMUX & 0xF0) | channel;  // V?lg den ?nskede kanal
	ADCSRA |= (1 << ADSC);  // Start konvertering
	while (ADCSRA & (1 << ADSC));  // Vent p? afslutning
	return ADC;  // Return?r ADC v?rdi
}
void getSteps() {
	// Initialiser UART og ADC
	uart_init(MYUBRR);
	adc_init();

	// Læs sensorværdier
	uint16_t top = read_analog(0);
	uint16_t bottom = read_analog(1);
	uint16_t left = read_analog(2);
	uint16_t right = read_analog(3);

	// Justeringsparameter
	const uint16_t correctionSize = 8;

	// Beregn trin for hver retning
	int16_t moveVertical = calculate_sun_position(top, bottom, correctionSize);
	int16_t moveHorizontal = calculate_sun_position(left, right, correctionSize);

	// Udfør motorbevægelser
	if (moveVertical != 0) 
	{
		if(moveVertical<0)
		{
			//send_new_position(moveVertical, 1); // Vertikal bevægelse (motor = 1)
			uart_send_string("Moving down\n\r");
		}
		else if (moveVertical>0)
		{
			//send_new_position(moveVertical, 1); // Vertikal bevægelse (motor = 1)
			uart_send_string("Moving up\n\r");
		}
	}
	else
	{
		//send_new_position(moveVertical, 0); // Horisontal bevægelse (motor = 0)uart_send_string("Not moving\n\r");
	}
	
				
	if (moveHorizontal != 0) 
	{
		if(moveHorizontal<0)
		{
			send_new_position(moveHorizontal, 0); // Horisontal bevægelse (motor = 0)
			uart_send_string("Moving left\n\r");
		}
		else if (moveHorizontal>0)
		{
			send_new_position(moveHorizontal, 0); // Horisontal bevægelse (motor = 0)
			uart_send_string("Moving right\n\r");
		}
		
	}
	else
	{
		uart_send_string("Not moving\n\r");
		send_new_position(moveVertical, 0); // Horisontal bevægelse (motor = 0)uart_send_string("Not moving\n\r");
	}
}


// Hjælpefunktion til at beregne trin
uint16_t calculate_sun_position(uint16_t sensor1, uint16_t sensor2, uint16_t correctionSize) {
	const int16_t stepsPerDegree = 5;  // Trin per grad, kan justeres
	if (sensor1 < sensor2) 
	{
		if(sensor2-sensor1>10)
		{
			return stepsPerDegree * correctionSize;  // Positiv bevægelse
		}
		else
		{
			return 0;
		}
		
	} 
		
	else if (sensor2 < sensor1) 
	{
			if(sensor1-sensor2>10)
			{
				return -(stepsPerDegree * correctionSize);  // Negativ bevægelse
			}
			else
			{
				return 0;
			}
		
	}
	return 0;  // Ingen bevægelse, hvis de er lige
}