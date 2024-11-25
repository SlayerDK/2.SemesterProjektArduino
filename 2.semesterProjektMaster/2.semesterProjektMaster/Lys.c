#include "Lys.h"

// Initialiser UART med den �nskede baud rate
void uart_init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8);  // S�t �vre byte af baud rate
	UBRR0L = (unsigned char)ubrr;        // S�t nedre byte af baud rate
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Aktiv�r transmitter og receiver
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit
}

// Send en karakter via UART
void uart_transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));  // Vent p�, at bufferen er klar
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
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Aktiv�r ADC og prescaler 128
}

// Generel funktion til at l�se analog v�rdi fra en specificeret kanal (0-7)
uint16_t read_analog(uint8_t channel) {
	//channel 0 = top, 1 = bottom, 2 = left, 3 = right
	channel &= 0x07;  // Begr�ns kanalen til 0-7
	ADMUX = (ADMUX & 0xF0) | channel;  // V�lg den �nskede kanal
	ADCSRA |= (1 << ADSC);  // Start konvertering
	while (ADCSRA & (1 << ADSC));  // Vent p� afslutning
	return ADC;  // Return�r ADC v�rdi
}

void getSteps(int16_t *moveVertical, int16_t *moveHorizontal) {
	//vertical negative = move down, vertical positive = move up
	//horizontal negative = move left, horizontal positive = move right
	//Jo mere lys jo lavere værdi
	uart_init(MYUBRR);  // Initialiser UART
	adc_init();  // Initialiser ADC

	uint16_t top, bottom, left, right;
	uint16_t const correctionSize = 10;
	//L�ser alle sensors
	top = read_analog(0);
	bottom = read_analog(1);
	left = read_analog(2);
	right = read_analog(3);
	
	if(top < bottom){
		*moveVertical = (uint16_t)(steps_per_degree * correctionSize);
		}
	if(bottom < top){
		*moveVertical = (uint16_t)(steps_per_degree * -correctionSize);
		}
	if(right < left){
		*moveHorizontal = (uint16_t)(steps_per_degree * correctionSize);
		}
	if(left < right){
		*moveHorizontal = (uint16_t)(steps_per_degree * -correctionSize);
		}
}
