#include "Effekt.h"


float R1 = 13000.0;
float R2 = 5100.0;
float sensitivity = 0.185;
float offset = 2.5;

extern volatile char uartReceivedChar;

int16_t measure_watt() {
	int sensorValue = read_analog(VOLTAGE_PIN);

	// Konverterer den rå value til en spænding (0-5V)
	float vOut = sensorValue * (5.0 / 1023.0);
	float inputVoltage = vOut * ((R1 + R2) / R2);
	
	// Læs strøm fra strømsensor (A0)
	int currentValue = read_analog(CURRENT_PIN);

	// Konverter rå value til spænding(0-5V)
	float vShunt = currentValue * (5.0 / 1023.0);

	// Omregn til strøm i ampere
	float current = (vShunt - offset) / sensitivity;

	// Beregn effekt
	float power = vOut * current * 1000;

	// Print effekt
	int16_t power_in_miliWatts = (int16_t)power;
	return power_in_miliWatts;
}