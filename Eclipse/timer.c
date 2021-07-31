/*
 * Module: TIMER
 *
 * Description: SOURCE FILE FOR THE TIMER DRIVERS
 *
 *  Created on: Mar 28, 2021
 *      Author: Shams Elgohary
 *******************************************************************************/
#include "timer.h"

							// GLOBAL VARIABLES //



						       // ISR DEFINITIONS //

ISR (TIMER0_OVF_vect)   {}

ISR (TIMER0_COMP_vect)  {}

ISR (TIMER1_OVF_vect)   {}

ISR (TIMER1_COMPA_vect) {}





							// FUNCTIONS DEFINITION //

void Timer0_init(const TimerConfig *configuration)
{
	TCCR0 = (TCCR0 & ~0x07) | configuration->clock;  //ADJUSTS PRESCALAR BITS

	TCCR0 = (TCCR0 & ~0xC8) | configuration->mode;  //ADJUSTS MODE (FOC0,WGM00,WGM01 bits)

	TCNT0=configuration->initial_value; 			// START COUNTING FROM INPUT INITIAL VALUE

	if (configuration->mode == NORMAL)
	{
		TIMSK|=(1<<TOIE0);							//TIMER OVERFLOW INTERRUPT ENABLE
	}

	if (configuration->mode == CTC)
	{
		TIMSK|=(1<<OCIE0);
		OCR0= configuration->compare_value;        //SET COMPARE VALUE
	}
}

void Timer0_deinit()
{
	TCCR0=0; TCNT0=0; TIMSK &=~(1<<TOIE0) & ~(1<<OCIE0);
}

void Timer0_stop()
{
	TCCR0 = (TCCR0 & ~0x07);							//CLEAR PRESCALE BITS
}

void Timer1_init(const TimerConfig *configuration)
{
	TCCR1B = (TCCR1B & ~0x07) | configuration->clock; //ADJUSTS PRESACALAR BITS

	TCCR1B = (TCCR1B & ~0x08) | (0x08 & configuration->mode); //FOR WGM12 IF CTC MODE 1 / NORMAL MODE 0

	TCCR1A = (1<<FOC1A);  							  //TIMER1 ONLY SUPPORTS CTC MODE AND NORMAL MODE

    TCNT1 = configuration->initial_value;

	if (configuration->mode == NORMAL)
	{
		TIMSK|=(1<<TOIE1);							//TIMER OVERFLOW INTERRUPT ENABLE
	}

	if (configuration->mode == CTC)
	{
		OCR1A= configuration->compare_value;        //SET COMPARE VALUE
		TIMSK|=(1<<OCIE1A);
	}
}

void Timer1_deinit()
{
	TCCR1B=0; TCCR1A=0; TCNT0=0; TIMSK &=~(1<<TOIE1) & ~(1<<OCIE1A);
}

void Timer1_stop()
{
	TCCR1B = (TCCR1B & ~0x07);
}

