/*
 * Lys.h
 *
 * Created: 26/11/2024 16.13.53
 *  Author: christianwinther
 */ 


#ifndef LYS_H_
#define LYS_H_

#include "Master.h"

// Funktionsprototyper

void adc_init(void);                         // Initialiser ADC
uint16_t read_analog(uint8_t channel);       // Læs analog værdi fra en given kanal
void getSteps(); // Beregn motorbevægelser
uint16_t calculate_sun_position(uint16_t sensor1, uint16_t sensor2, uint16_t correctionSize); // Beregn trin
int get_light_intensity();




#endif /* LYS_H_ */