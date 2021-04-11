/*
 * _4x7Segm_Display.h
 *
 * Created: 04.02.2021 11:41:47
 *  Author: stani
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>



//Zmienne do przechowywania cyfr w wyswietlaczu
extern volatile uint8_t C1;
extern volatile uint8_t C2;
extern volatile uint8_t C3;
extern volatile uint8_t C4;
extern volatile uint8_t Count;

#ifndef _4X7SEGM_DISPLAY_H_
#define _4X7SEGM_DISPLAY_H_

void Disp_init();
void Set_Disp(uint8_t number1,bool on1, uint8_t number2,bool on2, uint8_t number3,bool on3, uint8_t number4,bool on4);
void Disp_num(uint8_t n);




#endif /* 4X7SEGM_DISPLAY_H_ */