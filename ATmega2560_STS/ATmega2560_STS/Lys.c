#include "Lys.h"

// Initialiser ADC med AVcc som reference og prescaler til 128
void adc_init(void) {
	ADMUX = (1 << REFS0);  // Brug AVcc som reference
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Aktiv?r ADC og prescaler 128
}

// Hjælpefunktion til at beregne trin
uint16_t calculate_sun_position(uint16_t sensor1, uint16_t sensor2, uint16_t correctionSize) {
	if (sensor1 < sensor2)
	{
		if(sensor2-sensor1>10)
		{
			return (uint16_t)(steps_per_degree * correctionSize);  // Positiv bevægelse
		}
		else
		{
			return 0;
		}
		
	}
	
	else if (sensor2 < sensor1)
	{
		if(sensor1-sensor2>10)
		{
			return (uint16_t)(-steps_per_degree * correctionSize);  // Negativ bevægelse
		}
		else
		{
			return 0;
		}
		
	}
	return 0;  // Ingen bevægelse, hvis de er lige
}

int16_t get_light_intensity(){
	// Læs sensorværdier
	uint16_t top = read_analog(0);
	uint16_t bottom = read_analog(1);
	uint16_t left = read_analog(2);
	uint16_t right = read_analog(3);
	
	int16_t average_light = (int16_t)((top + bottom + left + right) / 4);
	return average_light;
}