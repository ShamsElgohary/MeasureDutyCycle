#include "lcd.h"
#include "timer.h"

static void (*global_callBackPtr)(void) = NULL_PTR;

uint8 click = 0;
uint16 T1 = 0;
uint16 T2 = 0;
uint16 T3 = 0;

void getTime_Application(void)
{
	click++;
	if(click == 2) 		  TCNT1 = 0;
	else if(click == 3)	  T1 = TCNT1;
	else if(click == 4)   T2 = TCNT1;
	else if(click == 5)  T3 = TCNT1;

}

ISR (INT0_vect)
{
		if(global_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*global_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}



void INT0_init() {
	SREG  &= ~(1<<7);
	GICR |= (1 << INT0); // ENABLE INT0 INTERRUPT
	MCUCR |= (1 << ISC00); //ANY LOGICAL CHANGE ON INT0 GENERATES INT REQ.
}

void INT0_callBack( void (*ptr_fn) (void) )
{
	/* Save the address of the Call back function in a global variable */
		global_callBackPtr = ptr_fn;
}


int main(void)
{
	uint32 DUTY_CYCLE;
	DDRD &= ~(1<<PD2); // PIND2 INPUT

	/* Set the Call back function pointer in the Timer driver */
	INT0_callBack(getTime_Application);

	TimerConfig T1_Configuration={NORMAL,F_CPU_CLOCK,0};  // TIMER1 CONFIGURATIONS
	Timer1_init(&T1_Configuration); 			 //Initialize timer1

	LCD_init();
	INT0_init();

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);


	while(1)
{


		if(click == 5)
		{

			GICR &= ~(1 << INT0); 	// DISABLE INT0 INTERRUPT
			Timer1_deinit(); 		//SHUTDOWN TIMER1
			click = 0;
			LCD_displayString("Duty = ");
			/* calculate the dutyCycle */
			DUTY_CYCLE = ((float)(T3-T2) / (T3 - T1)) * 100;
			/* display the dutyCycle on LCD screen */
			LCD_intgerToString(DUTY_CYCLE);
			LCD_displayCharacter('%');

		}
	}
}




