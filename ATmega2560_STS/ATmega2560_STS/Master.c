#include "Master.h"

// Initialiser UART med den ?nskede baud rate
void uart_init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8);  // S?t ?vre byte af baud rate
	UBRR0L = (unsigned char)ubrr;        // S?t nedre byte af baud rate
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Aktiv?r transmitter og receiver
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit
}

// Send en karakter via UART
void uart_send_char(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));  // Vent p?, at bufferen er klar
	UDR0 = data;  // Send data
}

// Send en streng via UART
void uart_send_string(const char* str) {
	while (*str) {
		uart_send_char(*str++);
	}
}

// Generel funktion til at l?se analog v?rdi fra en specificeret kanal (0-7)
uint16_t read_analog(uint8_t channel) {
	//channel A0 = top, A1 = bottom, A2 = left, A3 = right
	channel &= 0x07;  // Begr?ns kanalen til 0-7
	ADMUX = (ADMUX & 0xF0) | channel;  // sætter A0-A7 til LOW, og vælger den valgte pin
	ADCSRA |= (1 << ADSC);  // Start konvertering
	while (ADCSRA & (1 << ADSC));  // Vent p? afslutning
	return ADC;  // Return?r ADC v?rdi
}

void getSteps() {
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
		send_new_position(moveVertical, 1);
	}
	
	
	if (moveHorizontal != 0)
	{
		send_new_position(moveHorizontal, 0);
	}
}

