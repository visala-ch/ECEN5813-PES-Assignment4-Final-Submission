/********************************************
 * Title		: statemachine.c
 * Author		: Visalakshmi Chemudupati
 *
 * Description	: Implementing three functions
 * 				  state_dump()		- to print the states
 *				  statemachine()	- to implement the state machine
 *				  detect_touch(void) - to detect if the capacitive sldier has been touched
 * Tools used	: MCUXpresso,FRDM-KL25Z dev board
 *
 * Identification of any leveraged code:
 *
 * Applicable Links:
 * Howdy Pierces lecture slides
 * Elevator.c example
 * Textbook by Dean
 *
 */
#include "include_headers.h"
#define TSI_INITIAL_TOUCH_VAL 	250

//declaring global variables
int red_start_val;
int red_end_val;
int green_start_val;
int green_end_val;
int blue_start_val;
int blue_end_val;

int button_status_flag;

volatile state_t state = STOP;

/**
 * @function	:  Function to detect if the capacitive slider has been touched
 *					or not, to decide which state to shift to
 *
 * @param		: NULL
 * @return		: returns the touch sensor value
 *
 */
uint32_t TSI_val=0;

int detect_touch(void){
	TSI_val = scan_LH_touch_slider();
	if((TSI_val > TSI_INITIAL_TOUCH_VAL)||button_status_flag==1){
		button_status_flag=0;
		return 1;
	}
	return 0;
}

#ifdef DEBUG

/**
 * @function	: function is used to get the string value corresponding to the state
 * 				  to print the diagnostic output in the terminal window of MCUXpresso.
 *
 * @parameters	: takes enum state_t as a parameter
 *
 * @return		: returns the string corresponding to the state
 */
char* state_dump(state_t state) {
	char *state_str;
	switch (state) {
	case STOP:
		state_str = "STOP";
		break;
	case GO:
		state_str = "GO";
		break;
	case WARNING:
		state_str = "WARNING";
		break;
	case TRANSITION:
		state_str = "TRANSITION";
		break;
	case CROSSWALK_TRANSITION:
		state_str = "CROSSWALK_TRANSITION";
		break;
	case CROSSWALK:
		state_str = "CROSSWALK";
		break;
	case CROSSWALK_GO_TRANSITION:
		state_str = "CROSSWALK_GO_TRANSITION";
		break;
	}
	return state_str;
}
#endif


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
void Statemachine(void) {
	int TSI_touch = 0;
	state_t cur_state;
	state_t prev_state = state;

	while (1) {

		if ((int) (get_timer()) % 10 == 0)	//polls slider every 100sec
			TSI_touch = detect_touch();

		if ((TSI_touch || button_status_flag==1) && state != CROSSWALK && state != CROSSWALK_TRANSITION) {
			LOG("TSI press is detected at: %u sec \n\r", now() * 10);
			button_status_flag=0;
			LOG("button status flag:%d",button_status_flag);
			state = CROSSWALK_TRANSITION;
			reset_timer();
		}

		if (state != prev_state) {
			LOG("Transitioning from %s state to %s state at %u msec\n\r",
					state_dump(prev_state), state_dump(state), now() * 10);
			prev_state = state;
			reset_timer();
		}

		switch (state) {
		case STOP:
			if (get_timer() >= DELAY_FOR_STOP_GO_STATES) {
				cur_state = STOP;
				state = TRANSITION;
				reset_timer();
			}
			red_start_val = RED_IN_STOP_STATE;
			green_start_val = GREEN_IN_STOP_STATE;
			blue_start_val = BLUE_IN_STOP_STATE;

			set_color(RED_IN_STOP_STATE, GREEN_IN_STOP_STATE,
			BLUE_IN_STOP_STATE);

			break;

		case GO:
			if (get_timer() > DELAY_FOR_STOP_GO_STATES) {
				cur_state = GO;
				state = TRANSITION;
				reset_timer();

			}
			red_start_val = RED_IN_GO_STATE;
			green_start_val = GREEN_IN_GO_STATE;
			blue_start_val = BLUE_IN_GO_STATE;

			set_color(RED_IN_GO_STATE, GREEN_IN_GO_STATE, BLUE_IN_GO_STATE);
			break;

		case WARNING:
			if (get_timer() > DELAY_FOR_WARNING_STATE) {
				cur_state = WARNING;
				state = TRANSITION;
				reset_timer();

			}
			red_start_val = RED_IN_WARNING_STATE;
			green_start_val = GREEN_IN_WARNING_STATE;
			blue_start_val = BLUE_IN_WARNING_STATE;

			set_color(RED_IN_WARNING_STATE, GREEN_IN_WARNING_STATE,
			BLUE_IN_WARNING_STATE);
			break;

		case TRANSITION:
			if (cur_state == STOP) {
				if (get_timer() > DELAY_IN_TRANSITION) {
					state = GO;
				}
				red_start_val = RED_IN_STOP_STATE;
				red_end_val = RED_IN_GO_STATE;
				green_start_val = GREEN_IN_STOP_STATE;
				green_end_val = GREEN_IN_GO_STATE;
				blue_start_val = BLUE_IN_STOP_STATE;
				blue_end_val = BLUE_IN_GO_STATE;

				color_transition();
			} else if (cur_state == GO) {
				if (get_timer() > DELAY_IN_TRANSITION) {
					state = WARNING;

				}
				red_start_val = RED_IN_GO_STATE;
				red_end_val = RED_IN_WARNING_STATE;
				green_start_val = GREEN_IN_GO_STATE;
				green_end_val = GREEN_IN_WARNING_STATE;
				blue_start_val = BLUE_IN_GO_STATE;
				blue_end_val = BLUE_IN_WARNING_STATE;

				color_transition();
			} else if (cur_state == WARNING) {
				if (get_timer() > DELAY_IN_TRANSITION) {
					state = STOP;

				}
				red_start_val = RED_IN_WARNING_STATE;
				red_end_val = RED_IN_STOP_STATE;
				green_start_val = GREEN_IN_WARNING_STATE;
				green_end_val = GREEN_IN_STOP_STATE;
				blue_start_val = BLUE_IN_WARNING_STATE;
				blue_end_val = BLUE_IN_STOP_STATE;

				color_transition();
			}
			break;

		case CROSSWALK_TRANSITION:
			if (get_timer() > DELAY_IN_TRANSITION) {
				state = CROSSWALK;
				reset_crosswalk_timer();
			}
			red_end_val = RED_IN_CROSSWALK_STATE;
			green_end_val = GREEN_IN_CROSSWALK_STATE;
			blue_end_val = BLUE_IN_CROSSWALK_STATE;

			color_transition();

		case CROSSWALK:
			if (get_timer() > DELAY_IN_CROSSWALK) {
				state = CROSSWALK_GO_TRANSITION;
			}

			if (get_crosswalk_timer() <= LED_ON_DELAY_CROSSWALK) {
				set_color(RED_IN_CROSSWALK_STATE, GREEN_IN_CROSSWALK_STATE,
				BLUE_IN_CROSSWALK_STATE);
			} else if ((get_crosswalk_timer() > LED_ON_DELAY_CROSSWALK)
					&& (get_crosswalk_timer() <= LED_OFF_DELAY_CROSSWALK))
				set_color(0, 0, 0);
			else
				reset_crosswalk_timer();

			break;

		case CROSSWALK_GO_TRANSITION:
			if (get_timer() > DELAY_IN_TRANSITION) {
				state = GO;
				reset_crosswalk_timer();
			}
			red_start_val = RED_IN_CROSSWALK_STATE;
			red_end_val = RED_IN_GO_STATE;
			green_start_val = GREEN_IN_CROSSWALK_STATE;
			green_end_val = GREEN_IN_GO_STATE;
			blue_start_val = BLUE_IN_CROSSWALK_STATE;
			blue_end_val = BLUE_IN_GO_STATE;

			color_transition();
			break;
		}
	}
}
