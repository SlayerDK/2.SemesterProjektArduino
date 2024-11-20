#include "Motor.h"

// Initialiser pins som output
void motor_setup() {
	// Sæt STEP_PIN1, DIR_PIN1, STEP_PIN2 og DIR_PIN2 som output
	DDRB |= (1 << STEP_PIN1) | (1 << DIR_PIN1) | (1 << STEP_PIN2) | (1 << DIR_PIN2);
}

// Skriv HIGH eller LOW til en pin
void digitalWrite(uint8_t pin, uint8_t state) {
	if (state) {
		PORTB |= (1 << pin);  // Sæt pin HIGH
		} else {
		PORTB &= ~(1 << pin); // Sæt pin LOW
	}
}

void step(int16_t number_of_steps, unsigned char motor){
	//motor = 1, vertical move
	//motor = 0, horizontal move
	if(motor){
		if(number_of_steps >= 0){
			digitalWrite(DIR_PIN1, 0); // Retning fremad
			for(int16_t i = 0; i < number_of_steps; i++){
				digitalWrite(STEP_PIN1, 1);
				_delay_us(1000);
				digitalWrite(STEP_PIN1, 0);
				_delay_us(1000);
			}
		}
		else{
			digitalWrite(DIR_PIN1, 1); // Retning baglens
			for(int16_t i = 0; i < number_of_steps * -1; i++){
				digitalWrite(STEP_PIN1, 1);
				_delay_us(1000);
				digitalWrite(STEP_PIN1, 0);
				_delay_us(1000);
			}	
		}
	}
		
		if(!motor){
			if(number_of_steps >= 0){
				digitalWrite(DIR_PIN2, 0); // Retning fremad
				for(int16_t i = 0; i < number_of_steps; i++){
					digitalWrite(STEP_PIN2, 1);
					_delay_us(1000);
					digitalWrite(STEP_PIN2, 0);
					_delay_us(1000);
				}
			}
		else{
			digitalWrite(DIR_PIN2, 1); // Retning baglens
			for(int16_t i = 0; i < number_of_steps * -1; i++){
				digitalWrite(STEP_PIN2, 1);
				_delay_us(1000);
				digitalWrite(STEP_PIN2, 0);
				_delay_us(1000);
			}
		}
	}		
}
	


// Hovedløkken
void loop() {
	while (1) {
		// Motor 1 fremad
		digitalWrite(DIR_PIN1, 0); // Retning fremad
		for (int x = 0; x < 1450; x++) {
			digitalWrite(STEP_PIN1, 1);
			_delay_us(1000);
			digitalWrite(STEP_PIN1, 0);
			_delay_us(1000);
		}

		_delay_us(5000);

		// Motor 1 baglæns
		digitalWrite(DIR_PIN1, 1); // Retning baglæns
		for (int x = 0; x < 1450; x++) {
			digitalWrite(STEP_PIN1, 1);
			_delay_us(1000);
			digitalWrite(STEP_PIN1, 0);
			_delay_us(1000);
		}

		_delay_us(5000);

		// Motor 2 fremad
		digitalWrite(DIR_PIN2, 0); // Retning fremad
		for (int x = 0; x < 1450; x++) {
			digitalWrite(STEP_PIN2, 1);
			_delay_us(1000);
			digitalWrite(STEP_PIN2, 0);
			_delay_us(1000);
		}

		_delay_us(5000);

		// Motor 2 baglæns
		digitalWrite(DIR_PIN2, 1); // Retning baglæns
		for (int x = 0; x < 1450; x++) {
			digitalWrite(STEP_PIN2, 1);
			_delay_us(1000);
			digitalWrite(STEP_PIN2, 0);
			_delay_us(1000);
		}

		// Uendelig ventetilstand
		while (1);
	}
}