/********	************************************
* Title			: systick_timer.h
* Author		: Visalakshmi Chemudupati
*
* Description	: abstraction of 7 functions to configure the systick timer
* 					reset the timer values and get the timer values as required
*
*
* Identification of any leveraged code:
* Howdy Pierces' lecture slides
*
* Textbook by Dean
*/
#ifndef SYSTICK_TIMER_H_
#define SYSTICK_TIMER_H_

typedef uint32_t ticktime_t; // time since boot, in 1/8th of a second

/**
 *
 * @function	: function to set the clock and configure the Systick timer peripheral
 *
 * @parameters	: none
 * @return		: returns NULL
 */
void init_systick();

/**
 *
 * @function	: function to return the time since startup, in 1/8th of a second
 *
 * @parameters	: none
 * @return		: returns time since startup
 */
ticktime_t now();

/**
 *
 * @function	: function to reset timer to 0; it doesn't affect now() values
 *
 * @parameters	: none
 * @return		: returns NULL
 */
void reset_timer();

/**
 *
 * @function	: function to return ticks since the last call to reset_timer()
 *
 * @parameters	: none
 * @return		: returns the time since last call to reset
 */
ticktime_t get_timer();

/**
 *
 * @function	: function to reset the timer in crosswalk state to 0
 *
 * @parameters	: none
 * @return		: returns NULL
 */
void reset_crosswalk_timer();

/**
 *
 * @function	: function to return the timer for crosswalk state since the last call
 * 					to reset_crosswalk_timer()
 *
 * @parameters	: none
 * @return		: returns count
 */
ticktime_t get_crosswalk_timer();

#endif /*SYSTICK_TIMER_H_ */
