/*
 * uart.h
 *
 * Created: 18-11-2024 10:41:15
 *  Author: frederikpost
 */ 
#define F_CPU 16000000UL

// uart.h
#ifndef UART_H
#define UART_H

#include <avr/io.h>



void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char Rx_Int);
unsigned char CharReady(void);
char ReadChar(void);
void SendChar(char Tegn);
void SendString(char* Streng);
void SendInteger(int Tal);
#endif