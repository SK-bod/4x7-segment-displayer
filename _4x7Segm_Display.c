/*
 * 4x7Segm_Display.c
 *
 * Created: 03.02.2021 20:34:10
 * Author : stani
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>

/********************** POD£¥CZENIE ************************************
		 a-PC0
	f-PC5	  b-PC1
		 g-PD0	
	e-PC4	  c-PC2	 
		 d-PC3		DP-PD1

Disp1-PB2 | Disp2-PB3 | Disp3-PB4 | Disp4-PB5
************************************************************************/


#define a (1<<PC0)
#define b (1<<PC1)
#define c (1<<PC2)
#define d (1<<PC3)
#define e (1<<PC4)
#define f (1<<PC5)
#define g (1<<PD0)
#define DP (1<<PD1)
#define Disp1 (1<<PB2)
#define Disp2 (1<<PB3)
#define Disp3 (1<<PB4)
#define Disp4 (1<<PB5)
#define Reg_Disp_1 DDRC
#define Reg_Disp_2 DDRD
#define Reg_Segm DDRB
#define Port_Disp_1 PORTC
#define Port_Disp_2 PORTD
#define Port_Segm PORTB

volatile unsigned int  C1=10;
volatile unsigned int  C2=10;
volatile unsigned int  C3=10;
volatile unsigned int  C4=10;
volatile uint8_t Count=0;

//Inicjalizacja 
void Disp_init(){
	//Ustawienia licznika
	//Timer2
	TCCR2 |=(1<<WGM21); //tryb CTC
	TCCR2 |=(1<<CS22)|(1<<CS21); //prescaler 256
	TIMSK |=(1<<OCIE2);//przerwanie od Compare Mode
	OCR2 = 156; //	
	
	//Ustawienia Rejestrów i Portów
	Reg_Segm |= (Disp1|Disp2|Disp3|Disp4); //rejestr wyswietlaczy
	Reg_Disp_2 |= (g|DP); //rejestr segmentów spoza Port_Segm
	Reg_Disp_1 |= (a|b|c|d|e|f); //rejestr segmentów a-f
	
	Port_Segm |= (Disp1|Disp2|Disp3|Disp4); //wy³¹czam wyœwietlacz
    Port_Disp_2 |= (g|DP); //wy³¹czam segmenty g i DP
	Port_Disp_1 |= (a|b|c|d|e|f); //wy³¹czam segmenty a-f
}

//Funkcja do ustawiania liczb 
void Set_Disp(uint8_t number1,bool on1, uint8_t number2,bool on2, uint8_t number3,bool on3, uint8_t number4,bool on4)
{
	if (on1)
	C1 = number1;
	if (on2)
	C2 = number2;
	if (on3)
	C3 = number3;
	if (on4)
	C4 = number4;
}

void Disp_num(uint8_t n)
{
	Port_Disp_1=0xFF;
	Port_Disp_2=g|DP;
	switch(n)
	{
		case 0:
			Port_Disp_1 =~(a|b|c|d|e|f);
			Port_Disp_2 =g|DP;
			break;
		case 1:
			Port_Disp_1 =~(b|c);
			Port_Disp_2 =g|DP;
			break;
		case 2:
			Port_Disp_1 =~(a|b|d|e);
			Port_Disp_2 =~g;
			break;
		case 3:
			Port_Disp_1 =~(a|b|c|d);
			Port_Disp_2 =~g;
			break;
		case 4:
			Port_Disp_1 =~(b|c|f);
			Port_Disp_2 =~g;
			break;
		case 5:
			Port_Disp_1 =~(a|c|d|f);
			Port_Disp_2 =~g;
			break;
		case 6:
			Port_Disp_1 =~(a|c|d|e|f);
			Port_Disp_2 =~g;
			break;
		case 7:
			Port_Disp_1 =~(a|b|c);
			Port_Disp_2 =g|DP;
			break;
		case 8:
			Port_Disp_1 =~(a|b|c|d|e|f);
			Port_Disp_2 =~g;
			break;
		case 9:
			Port_Disp_1 =~(a|b|c|d|f);
			Port_Disp_2 =~g;
			break;
		default:
			break;
	}
}


//Procedura przerwania od Compare Licznika Timer2
ISR(TIMER2_COMP_vect)
{
	switch(Count)
	{
		case 0:
			Disp_num(C1);
			Port_Segm =~Disp1;
			break;
		case 1:
			Disp_num(C2);
			Port_Segm =~Disp2;
			break;
		case 2:
			Disp_num(C3);
			Port_Segm =~Disp3;
			break;
		case 3:
			Disp_num(C4);
			Port_Segm =~Disp4;
			break; 
		default:
			break;
	}	
	
	Count>3 ? Count=0:Count++;
}
