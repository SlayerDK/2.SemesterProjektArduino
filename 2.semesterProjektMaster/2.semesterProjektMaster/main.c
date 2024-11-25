/*
 * main.c
 *
 * Created: 11/20/2024 12:18:36 PM
 *  Author: christianwinther
 */ 

#include <xc.h>
#include "motor.h"
#include "Lys.h"
int main(void)
{
    motor_setup();
	step(5000, 1);
	step(-5000, 1);
	_delay_ms(5000);
	step(5000, 0);
	step(-5000, 0);
}
