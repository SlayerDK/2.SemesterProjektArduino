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

