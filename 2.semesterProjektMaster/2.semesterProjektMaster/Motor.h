/*
 * Motor.h
 *
 * Created: 20/11/2024 14.13.47
 *  Author: christianwinther
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Definer pin-mapping til ATmega25
#define STEP_PIN1 0
#define DIR_PIN1 1

#define STEP_PIN2 2
#define DIR_PIN2 3



#ifndef MOTOR_H_
#define MOTOR_H_
void motor_setup();
void digitalWrite(uint8_t pin, uint8_t state);
void loop();
void send_new_position(int16_t number_of_steps, unsigned char motor);




#endif /* MOTOR_H_ */