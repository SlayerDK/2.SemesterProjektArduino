/*
 * Kommunikation.h
 *
 * Created: 26/11/2024 22.32.23
 *  Author: christianwinther
 */ 


#ifndef KOMMUNIKATION_H_
#define KOMMUNIKATION_H_

#include "Master.h"

// Buffer-størrelse
#define BUFFER_SIZE 10

// Funktionsprototyper
void send_data_to_webserver(int16_t watt, int16_t sol);
void kommunikatio_test();


#endif /* KOMMUNIKATION_H_ */