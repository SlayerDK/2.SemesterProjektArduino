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
    motor_setup(); // Sætter motorernes pins som output. 
    uart_init(MYUBRR); // nitialiserer UART til at sende data
    adc_init();   //Initialiserer ADC for at læse analoge værdier fra sensorer.

    int16_t moveVertical = 0, moveHorizontal = 0;
    int watt = 0;  // Eksempelværdi for watt
    int sol = 0;   // Eksempelværdi for sol

    while (1) {
        
// Aflæser lysintensitet og bestemmer, hvor meget motorerne skal flytte sig med
        getSteps(&moveVertical, &moveHorizontal);

        // Bevæg motorer baseret på sensorens feedback
        // step motor flytter motorerne op/ned og venstre/højre baseret på sensordata. 
        if (moveVertical != 0) 
        {
            step(moveVertical, 1); // Vertikal motor (1)
        }

        if (moveHorizontal != 0)
        {
            step(moveHorizontal, 0); // Horisontal motor (0)
        }
// Måler værdier fra lysfølsomme sensorer og gemmer dem som watt og sol. 
        watt = read_analog(0); // Læs værdi fra sensor for watt
        sol = read_analog(1);  // Læs værdi fra sensor for sol

    
        // Send værdier via UART
        ConvertAndSendValues(watt, sol);

        _delay_ms(1000);
    }

    return 0;
}
