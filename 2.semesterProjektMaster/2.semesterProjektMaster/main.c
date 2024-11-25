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
    int sensor1 = 0;  // Værdi fra første sensor
    int sensor2 = 0;  // Værdi fra anden sensor

    while (1) {
        // Aflæser lysintensitet og bestemmer, hvor meget motorerne skal flytte sig med
        getSteps(&moveVertical, &moveHorizontal);

        // Bevæg motorer baseret på sensorens feedback
        if (moveVertical != 0) 
        {
            step(moveVertical, 1); // Vertikal motor (1)
        }

        if (moveHorizontal != 0)
        {
            step(moveHorizontal, 0); // Horisontal motor (0)
        }

        // Måler værdier fra lysfølsomme sensorer
        sensor1 = read_analog(0); // Læs værdi fra første sensor
        sensor2 = read_analog(1); // Læs værdi fra anden sensor

        // Send værdier via UART
        ConvertAndSendValues(sensor1, sensor2);

        _delay_ms(1000);
    }

    return 0;
}

