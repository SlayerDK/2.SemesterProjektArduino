/*
 * motortest.c
 *
 * Created: 25-11-2024 12:23:26
 * Author : bruger
 */ 
#include "motor.h"
#include <avr/io.h>


int main(void)
{
    motor_setup();
    while (1) 
    {
	
		loop();
		
    }
}

