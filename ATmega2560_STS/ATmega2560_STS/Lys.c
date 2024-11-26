#include "Lys.h"

// Initialiser ADC med AVcc som reference og prescaler til 128
void adc_init(void) {
	ADMUX = (1 << REFS0);  // Brug AVcc som reference
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Aktiv?r ADC og prescaler 128
}

// Generel funktion til at l?se analog v?rdi fra en specificeret kanal (0-7)
uint16_t read_analog(uint8_t channel) {
	//channel A0 = top, A1 = bottom, A2 = left, A3 = right
	channel &= 0x07;  // Begr?ns kanalen til 0-7
	ADMUX = (ADMUX & 0xF0) | channel;  // sætter A0-A7 til LOW, og vælger den valgte pin
	ADCSRA |= (1 << ADSC);  // Start konvertering
	while (ADCSRA & (1 << ADSC));  // Vent p? afslutning
	return ADC;  // Return?r ADC v?rdi
}

void getSteps() {
	// Initialiser UART og ADC
	uart_init(MYUBRR);
	adc_init();

	// Læs sensorværdier
	uint16_t top = read_analog(0);
	uint16_t bottom = read_analog(1);
	uint16_t left = read_analog(2);
	uint16_t right = read_analog(3);

	// Justeringsparameter
	const uint16_t correctionSize = 8;

	// Beregn trin for hver retning
	int16_t moveVertical = calculate_sun_position(top, bottom, correctionSize);
	int16_t moveHorizontal = calculate_sun_position(left, right, correctionSize);
							
														//*** Kan alle if statements ikke fjernes? ***\\
	// Udfør motorbevægelser
	if (moveVertical != 0)
	{
		if(moveVertical<0)
		{
			send_new_position(moveVertical, 1); // Vertikal bevægelse (motor = 1)
		}
		else if (moveVertical>0)
		{
			send_new_position(moveVertical, 1); // Vertikal bevægelse (motor = 1)
		}
	}
	else
	{
		send_new_position(moveVertical, 0); // Horisontal bevægelse (motor = 0)uart_send_string("Not moving\n\r");
	}
	
	
	if (moveHorizontal != 0)
	{
		if(moveHorizontal<0)
		{
			send_new_position(moveHorizontal, 0); // Horisontal bevægelse (motor = 0)
		}
		else if (moveHorizontal>0)
		{
			send_new_position(moveHorizontal, 0); // Horisontal bevægelse (motor = 0)
		}
		
	}
	else
	{
		send_new_position(moveVertical, 0); // Horisontal bevægelse (motor = 0)uart_send_string("Not moving\n\r");
	}
}

// Hjælpefunktion til at beregne trin
uint16_t calculate_sun_position(uint16_t sensor1, uint16_t sensor2, uint16_t correctionSize) {
	if (sensor1 < sensor2)
	{
		if(sensor2-sensor1>10)
		{
			return steps_per_degree * correctionSize;  // Positiv bevægelse
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
			return -(steps_per_degree * correctionSize);  // Negativ bevægelse
		}
		else
		{
			return 0;
		}
		
	}
	return 0;  // Ingen bevægelse, hvis de er lige
}

int get_light_intensity(){
	// Læs sensorværdier
	uint16_t top = read_analog(0);
	uint16_t bottom = read_analog(1);
	uint16_t left = read_analog(2);
	uint16_t right = read_analog(3);
	
	int16_t average_light = (int16_t)((top + bottom + left + right) / 4);
	return average_light;
}