/********************************************
 * Title		: statemachine.h
 * Author		: Visalakshmi Chemudupati
 *
 * Description	: Implementing three functions to print the states, implement state machine
 * 				  and detect if the TSI sensor has been touched or not
 *
 * Tools used	: MCUXpresso,FRDM-KL25Z dev board
 *
 * Identification of any leveraged code:
 *
 * Applicable Links:
 * Howdy Pierce's elevator example
 *
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#define RED_IN_STOP_STATE 			(0x61)  //starting value of RED at STOP state
#define GREEN_IN_STOP_STATE 		(0x1E)	//starting value of GREEN at STOP state
#define BLUE_IN_STOP_STATE 			(0x3C)	//starting value of BLUE at STOP state

#define RED_IN_GO_STATE				(0x22)	//starting value of RED at GO state
#define GREEN_IN_GO_STATE 			(0x96)	//starting value of GREEN at GO state
#define BLUE_IN_GO_STATE 			(0x22)	//starting value of BLUE at GO state

#define RED_IN_WARNING_STATE 		(0xFF)	//starting value of RED at WARNING state
#define GREEN_IN_WARNING_STATE 		(0xB2)	//starting value of GREEN at WARNING state
#define BLUE_IN_WARNING_STATE 		(0x00)	//starting value of BLUE at WARNING state

#define RED_IN_CROSSWALK_STATE 		(0x00)	//starting value of RED at CROSSWALK state
#define GREEN_IN_CROSSWALK_STATE	(0x10)	//starting value of GREEN at CROSSWALK state
#define BLUE_IN_CROSSWALK_STATE 	(0x30)	//starting value of BLUE at CROSSWALK state

#define DELAY_IN_TRANSITION  		(100)	//1msec while transition
#define DELAY_IN_CROSSWALK 	  		(1000)	//10sec while in CROSSWALK state

#define LED_ON_DELAY_CROSSWALK 		(75)	//750msec for toggling the LED in CROSSWALK state
#define LED_OFF_DELAY_CROSSWALK 	(100)	//1000msec for toggling the LED in CROSSWALK state

#ifdef DEBUG
#define DELAY_FOR_STOP_GO_STATES 	(500)	//5sec stay in STOP and GO state in DEBUG mode
#define DELAY_FOR_WARNING_STATE 	(300)	//3sec stay in WARNING state in DEBUG mode
#else
#define DELAY_FOR_STOP_GO_STATES 	(2000)	//20sec stay in STOP and GO state in PRODUCTION mode
#define DELAY_FOR_WARNING_STATE 	(500)	//5sec stay in WARNING state in PRODUCTION mode
#endif

typedef enum
{
	STOP,
	GO,
	WARNING,
	TRANSITION,
	CROSSWALK,
	CROSSWALK_TRANSITION,
	CROSSWALK_GO_TRANSITION
}state_t;

/**
 * @function	:  Function to detect if the capacitive slider has been touched
 *					or not to decide which state to shift to
 *
 * @param		: NULL
 * @return		: returns the touch sensor value
 *
 */
int detect_touch(void);

/**
 * @function	: function is used to get the string value corresponding to the state
 * 				  to print the diagnostic output in the terminal window of MCUXpresso.
 *
 * @parameters	: takes enum state_t as a parameter
 *
 * @return		: returns the string corresponding to the state
 */
char* state_dump(state_t state);

/**
 * @function	: state machine function with total of 6 states. It firsts checks
 * 				  if the capacitive slider has been touched by polling the slider
 * 				  every 100 sec to avoid the TSI getting stuck in an infinite loop.
 * 				  If the slider is touched
 * 				  based on the above condition. Whenever the slider is touched,
 * 				  state changes as:
 * 				  Current_state->TRANSITION->CROSSWALK_TRANSITION->CROSSWALK->
 * 				  CORSSWALK_GO_TRANSITION->GO.
 *
 * 				  If the slider has not been touched, a while loop runs from
 * 				  STOP->TRANSITION->GO->TRANSITION->WARNING->TRANSITION->STOP forever.
 * 				  Each state has a color code and the gradual color transition for
 * 				  different states happens over a delay of 1 sec for the STOP, GO,
 * 				  WARNING states. The color transition values at a particular time are
 * 				  computed using the mathematical equation:
 * 				  (start_val - end_val)*time + end_val
 *
 * 				  In DEBUG mode, the LED is ON for 5sec in STOP and GO states and
 * 				  for 3sec in the WARNING state. In PRODUCTION(Release) mode, the
 * 				  LED is ON for 20sec in STOP and GO states and 5sec in WARNING state.
 * 				  LED is ON for 10sec in CROSSWALK state (toggling between 750msec
 * 				  and 250msec)in both DEBUG and PRODUCTION. Transition happens for only 1sec.
 *
 * @parameteras	: NULL
 * @return		: NULL
 */
void Statemachine(void);




#endif /* STATE_MACHINE_H_ */
