/********************************************
 * Title		: main.c
 * Author		: Visalakshmi Chemudupati
 *
 * Description	: implementing the Bufahiti traffic lights logic
 * Tools used	: MCUXpresso,FRDM-KL25Z dev board
 *
 * Identification of any leveraged code:
 *
 * Applicable Links:
 * intialising board hardware source:
 * https://forum.digikey.com/t/getting-started-with-nxps-mcuxpresso-with-the-frdm-kl46z/13242
 * https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 *
 * Howdy Pierce's lecture slides and notes
 *
 */
#include "include_headers.h"

/*
 *
 */
int main(void) {
	//initialising board hardware
	BOARD_InitBootPins();
	BOARD_InitBootClocks();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL

	BOARD_InitDebugConsole();	// Init FSL debug console

#endif

	init_interrupt();
	init_systick();
	init_touch_slider();
	init_PWM_LED(CLK_PERIOD);

	LOG("Commencing State machine\n\r");
	Statemachine();

	return 0;
}
