/*
 * Motor.h
 *
 * Created: 26/11/2024 14.02.26
 *  Author: christianwinther
 */ 
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define STEP_PIN1 0
#define DIR_PIN1 1

#define STEP_PIN2 2
#define DIR_PIN2 3
#define F_CPU 16000000UL

#ifndef MOTOR_H_
#define MOTOR_H_

void motor_setup();
void digitalWrite(uint8_t pin, uint8_t state);
void send_new_position(int16_t number_of_steps, unsigned char motor);
void loop();



#endif /* MOTOR_H_ */