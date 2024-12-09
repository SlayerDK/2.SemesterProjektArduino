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
void adc_init();                         // Initialiser ADC
uint16_t calculate_sun_position(uint16_t sensor1, uint16_t sensor2, uint16_t correctionSize); // Beregn trin
int16_t get_light_intensity();




#endif /* LYS_H_ */
