#include "Kommunikation.h"

// Funktion til konvertering og afsendelse af værdier
void send_data_to_webserver(int16_t watt, int16_t sol) {
	char watt_str[BUFFER_SIZE];  // Buffer til watt-værdi som tekst
	char sol_str[BUFFER_SIZE];   // Buffer til sol-værdi som tekst

	// Konverter værdier til tekst
	itoa(watt, watt_str, 10);
	itoa(sol, sol_str, 10);
	
	// Send værdier via UART
	uart_send_string("watt ");
	uart_send_string(watt_str);
	uart_send_string("\r\n");
	
	uart_send_string("Sol ");
	uart_send_string(sol_str);
	uart_send_string("\r\n");
}

void kommunikation_test(){
	uart_send_string("test");
	_delay_ms(100);
	uart_send_string("\r\n");

	uart_send_string("test");
	_delay_ms(100);
	uart_send_string("\r\n");
	_delay_ms(5000);
}