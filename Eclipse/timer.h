/*
 * Module: TIMER
 *
 * Description: HEADER FILE FOR THE AVR TIMER DRIVERS
 *
 *  Created on: Mar 28, 2021
 *      Author: Shams Elgohary
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_
								// LIBRARIES //
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

							// 	TYPE DECLARTION	 //
	 						// CONFIGURABLE TIMER //

typedef enum
{
	NORMAL=0x80, PWM=0x40 ,CTC=0x88 , FAST_PWM=0x48     //Bit 7 FOC0 Bit 6 3 WGM00 WGM01 -> 1100 1000
}Timer_Mode;


typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_Clock;


typedef struct
{
	Timer_Mode mode;
	Timer_Clock clock;
	uint16 initial_value;
	uint16 compare_value;
}TimerConfig;

								// GLOBAL VARIABLES //

extern  uint32 SECONDS_T0;
extern  uint32 SECONDS_T1_MC1;
extern  uint32 SECONDS_T1_MC2;


								// FUNCTION PROTOTYPES //

void Timer0_init(const TimerConfig *configuration);
void Timer0_deinit();
void Timer0_stop();


void Timer1_init(const TimerConfig *configuration);
void Timer1_deinit();
void Timer1_stop();

#endif /* TIMER_H_ */
