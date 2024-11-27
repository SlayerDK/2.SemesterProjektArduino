#include "Motor.h"

void motor_setup() {
	// S?t STEP_PIN1, DIR_PIN1, STEP_PIN2 og DIR_PIN2 som output
	DDRB |= (1 << STEP_PIN1) | (1 << DIR_PIN1) | (1 << STEP_PIN2) | (1 << DIR_PIN2);
}

// Skriv HIGH eller LOW til en pin
void digitalWrite(uint8_t pin, uint8_t state) {
	if (state) {
		PORTB |= (1 << pin);  // S?t pin HIGH
		} else {
		PORTB &= ~(1 << pin); // S?t pin LOW
	}
}

void send_new_position(int16_t number_of_steps, unsigned char motor){
	//motor = 1, vertical move
	//negative steps = down
	//positive steps = up
	
	//motor = 0, horizontal move
	//negative steps = left
	//positive steps = right
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


void self_testing() {
	uint16_t current_step = 0;
	uint16_t max_lys = 10000;
	uint16_t lys;
	uint16_t max_step = 0;
	uint16_t start_pos_vertical = 0;
	uint16_t start_pos_horizontal = 0;
	
	// Motor 1 fremad
	for (current_step; current_step < 1450; current_step++) {
		lys = get_light_intensity();
		if (lys < max_lys){
			max_step = current_step;
		}
		send_new_position(1, 1);
	}

	start_pos_vertical = max_step - 1450;
	send_new_position(start_pos_vertical, 1);
	_delay_us(5000);

	// Motor 2 fremad
	for (current_step; current_step < 1450; current_step++) {
		lys = get_light_intensity();
		if (lys < max_lys){
			max_step = current_step;
		}
		send_new_position(1, 0);
	}

	start_pos_horizontal = max_step - 1450;
	send_new_position(start_pos_horizontal, 0);
	_delay_us(5000);
}
