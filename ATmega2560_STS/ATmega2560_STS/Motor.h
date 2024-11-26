/*
 * Motor.h
 *
 * Created: 26/11/2024 16.13.28
 *  Author: christianwinther
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "Master.h"

void motor_setup();
void digitalWrite(uint8_t pin, uint8_t state);
void self_testing();
void send_new_position(int16_t number_of_steps, unsigned char motor);




#endif /* MOTOR_H_ */