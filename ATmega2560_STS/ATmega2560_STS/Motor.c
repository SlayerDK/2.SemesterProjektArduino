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
	uint16_t current_step;
	uint16_t max_lys = 10000;
	uint16_t lys;
	uint16_t max_step = 0;
	int16_t start_pos_vertical = 0;
	uint16_t start_pos_horizontal = 0;
	
	// Motor 0 
	for (current_step = 0; current_step < 2300; current_step++)
	{
		lys = get_light_intensity();
		
		if (lys < max_lys)
		{
			max_lys = lys;
			max_step = current_step;
		}
		
		send_new_position(1, 0);
	}

	//start_pos_horizontal = 2300 - max_step;
	send_new_position(-2300, 0);
	_delay_ms(500);
	send_new_position(max_step, 0);
	_delay_ms(2000);
	
	// Motor 1
	max_lys = 10000;
	max_step = 0;
	for (current_step = 0; current_step < 1450; current_step++)
	 {
		lys = get_light_intensity();
		
		if (lys < max_lys)
		{
			max_lys = lys;
			max_step = current_step;
		}
		
		send_new_position(1, 1);
	}

	//start_pos_vertical = 1450 - max_step;
	send_new_position(-1450, 1);
	_delay_ms(500);
	send_new_position(max_step, 1);
	_delay_ms(2000);
}
