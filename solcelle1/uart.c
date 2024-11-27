// uart.c
#include "uart.h"
#include <stdlib.h>
#include <avr/interrupt.h>

volatile char uartReceivedChar;

void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char Rx_Int) {
    // Sikrer, at inputparametrene er inden for tilladte grænser
    if (BaudRate < 300 || BaudRate >= 115200 || DataBit < 5 || DataBit > 8) {
	    return;  // Returnerer og afbryder funktionen, hvis parametre er ugyldige
    }

    // Starter interrupt baseret på om Rx_Int er 0 eller 1.
    if (Rx_Int > 0) {
	    sei();
	    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	    } else {
	    // Aktiverer modtageren og transmitteren, men deaktiverer alle interrupts
	    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    }

    // Beregner værdien til UBRR0 registeret for at indstille baud raten
    unsigned int ubrrValue = (F_CPU / 16 / BaudRate) - 1;
    UBRR0H = (unsigned char)(ubrrValue >> 8);  // Sætter de højeste 8 bits af UBRR0
    UBRR0L = (unsigned char)ubrrValue;  // Sætter de laveste 8 bits af UBRR0

    // Indstiller antallet af databits per frame baseret på inputparameteren
    UCSR0C = 0;
    switch (DataBit) {
	    case 5: UCSR0C |= 0; break;  // 5 databits
	    case 6: UCSR0C |= (1 << UCSZ00); break;  // 6 databits
	    case 7: UCSR0C |= (1 << UCSZ01); break;  // 7 databits
	    case 8: UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); break;  // 8 databits
	    default: return;  // Afslutter, hvis databits er uden for tilladt omfang
    }
    }
	
	// ISR for UART modtagelse
	ISR(USART_RX_vect) {
		uartReceivedChar = UDR0;  // Læs den modtagne karakter
	}

    unsigned char CharReady() {
	    if (UCSR0A & (1 << RXC0)) {  // Tjekker RXC0-flaget for at se, om der er modtaget data
		    return 1;  // Returnerer sand, hvis der er modtaget en ny karakter
		    } else {
		    return 0;  // Returnerer falsk, hvis der ikke er modtaget data
	    }
    }

    char ReadChar() {
	    while (!(UCSR0A & (1 << RXC0))) {}  // Vent indtil der er modtaget en karakter
	    return UDR0;  // Returnerer den modtagne karakter fra dataregisteret
    }

    void SendChar(char Tegn) {
	    while (!(UCSR0A & (1 << UDRE0))) {}  // Vent indtil dataregisteret er tomt
	    UDR0 = Tegn;  // Sender karakteren
    }

    void SendString(char* Streng) {
	    while (*Streng) {  // Løkke gennem hver karakter i strengen indtil null-terminator
		    SendChar(*Streng++);  // Sender en karakter ad gangen og inkrementerer pointeren
	    }
    }

    void SendInteger(int Tal) {
	    char streng[7];  // Buffer til at holde den konverterede streng
	    itoa(Tal, streng, 10);  // Konverterer tallet til en streng i decimal
	    SendString(streng);  // Sender den konverterede streng
    }
