#include <xc.h>
#include "motor.h"
#include "Lys.h"
#include "kommunikation.h"

int main(void) {
    // Initialisering
    motor_setup();       // Initialiser motorer
    uart_init(MYUBRR);   // Initialiser UART
    adc_init();          // Initialiser ADC

    // Variabler til motorbevægelser og sensorværdier
    int16_t moveVertical = 0, moveHorizontal = 0;
    int watt = 0;        // Lysintensitet fra første sensor
    int sol = 0;         // Lysintensitet fra anden sensor

    while (1) {
        // Beregn, hvor meget motorerne skal flytte sig
        getSteps(&moveVertical, &moveHorizontal);

        // Bevæg motorerne baseret på feedback fra sensorerne
        if (moveVertical != 0) {
            step(moveVertical, 1); // Flyt vertikalt (motor 1)
        }

        if (moveHorizontal != 0) {
            step(moveHorizontal, 0); // Flyt horisontalt (motor 0)
        }

        // Læs værdier fra lysfølsomme sensorer
        watt = read_analog(0); // Måling fra første sensor
        sol = read_analog(1);  // Måling fra anden sensor

        // Send sensorværdier via UART
        ConvertAndSendValues(watt, sol);

        _delay_ms(1000);
    }

    return 0;
}
