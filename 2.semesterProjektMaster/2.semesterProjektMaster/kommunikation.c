#include "uart_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // Til sprintf, hvis nødvendigt

// Buffer-størrelse
#define BUFFER_SIZE 10

// Funktion til konvertering og afsendelse af værdier
void ConvertAndSendValues(int watt, int sol) {
    char watt_str[BUFFER_SIZE];  // Buffer til watt-værdi som tekst
    char sol_str[BUFFER_SIZE];   // Buffer til sol-værdi som tekst

    // Konverter værdier til tekst
    itoa(watt, watt_str, 10);
    itoa(sol, sol_str, 10);
    
    // Send værdier via UART
    SendString("watt ");
    SendString(watt_str);
    SendString("\r\n");
    
    SendString("Sol ");
    SendString(sol_str);
    SendString("\r\n");
}