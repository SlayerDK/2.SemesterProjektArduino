/*
 * main.c
 *
 * Created: 11/20/2024 12:18:36 PM
 *  Author: christianwinther
 */ 

#include <xc.h>
#include "motor.h"
#include "Lys.h"
#include "kommunikation.h"

int main(void) {
    // Initialiser motorer, sensorer og UART-kommunikation
    motor_setup();
    uart_init(MYUBRR);
    adc_init();

    int16_t moveVertical = 0, moveHorizontal = 0;
    int watt = 0;  // Eksempelværdi for watt
    int sol = 0;   // Eksempelværdi for sol

    while (1) {
        // Hent de nødvendige trin til korrektion baseret på sensoraflæsninger
        getSteps(&moveVertical, &moveHorizontal);

        // Bevæg motorer baseret på sensorfeedback
        if (moveVertical != 0) {
            step(moveVertical, 1); // Vertikal motor (1)
        }

        if (moveHorizontal != 0) {
            step(moveHorizontal, 0); // Horisontal motor (0)
        }

        // Eksempel på læsning af watt og solværdi fra sensorer
        watt = read_analog(0); // Læs værdi fra sensor (f.eks. kanal 0 for watt)
        sol = read_analog(1);  // Læs værdi fra sensor (f.eks. kanal 1 for sol)

        // Send værdier via UART
        ConvertAndSendValues(watt, sol);

        _delay_ms(1000);
    }

    return 0;
}
