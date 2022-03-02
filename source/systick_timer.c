/********************************************
* Title			: systick_timer.c
* Author		: Visalakshmi Chemudupati
*
* Description	: Implementing seven functions in this file:
* 				  init_systick()	- to configure the systick timer of KL25z
*				  systick_handle()	- to obtain TSI slider values
*				  now()				- to get time since startup
*				  reset_timer()		- to reset timer to 0
*				  get_timer()		- to get time since reset
*				  reset_crosswalk_timer()	- to reset crosswalk timer to 0
*				  get_crosswalk_timer()		- to get crosswalk timer value since last reset_crosswalk_timer was called
* Tools used	: MCUXpresso,FRDM-KL25Z dev board
*
* Identification of any leveraged code:
*
* Applicable Links:
* Capacitive touch logic source:
* https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
*/

#include "include_headers.h"
#define TIMER_LOAD	375000		//timer value calculated as:((48000000/16)/8)

/**
 *
 * @function	: function to set the clock and configure the Systick timer peripheral
 *
 * @parameters	: none
 * @return		: returns NULL
 */
void init_systick(){
	SysTick->LOAD = TIMER_LOAD;					//set reload to 125msec
	NVIC_SetPriority(SysTick_IRQn,3);			// set interrupt priority
	SysTick->VAL = 0;							//force load of reload value
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk|	//enable interrupt, alternate clock source
					SysTick_CTRL_ENABLE_Msk;	//enable systick timer

}

typedef uint32_t ticktime_t;
static volatile ticktime_t time_since_boot=0;
static volatile ticktime_t crosswalk_timer=0;
static volatile ticktime_t time_since_last_reset=0;

/**
 *
 * @function	: function to return the time since startup in 1/8th of a second
 *
 * @parameters	: none
 * @return		: returns time since startup
 */
ticktime_t now()
{
	return time_since_boot;
}

/**
 *
 * @function	: function to reset timer to 0; it doesn't affect
 * 					now() values
 *
 * @parameters	: none
 * @return		: returns NULL
 */
void reset_timer()
{
	time_since_last_reset=0;
}

/**
 *
 * @function	: function to return ticks since the last call
 * 					to reset_timer()
 *
 * @parameters	: none
 * @return		: returns the time since last call to reset
 */


ticktime_t get_timer()
{
	return time_since_last_reset;
}

/**
 *
 * @function	: timer interrupt called based on the timer value
 *
 * @parameters	: none
 * @return		: returns NULL
 */
void SysTick_Handler()
{
	time_since_boot+=12;
	time_since_last_reset+=12;
	crosswalk_timer+=12;
}

/**
 *
 * @function	: function to reset the timer in crosswalk state to 0
 *
 * @parameters	: none
 * @return		: returns NULL
 */
void reset_crosswalk_timer()
{
	crosswalk_timer=0;
}

/**
 *
 * @function	: function to return the timer for crosswalk state since
 * 					the last call to reset_crosswalk_timer()
 *
 * @parameters	: none
 * @return		: returns count
 */
ticktime_t get_crosswalk_timer()
{
	return crosswalk_timer;
}
