/*
 * solcelle.h
 *
 * Created: 18-11-2024 10:40:53
 *  Author: frederikpost
 */ 


#ifndef SOLCELLE_H
#define SOLCELLE_H

#include <stdint.h>

void setup_sensors();
int analogRead(uint8_t channel);
void measure_and_print();

#endif
