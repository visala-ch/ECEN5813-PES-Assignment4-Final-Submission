/********************************************
 * Title		: capacitive_touch.c
 * Author		: Visalakshmi Chemudupati
 *
 * Description	: Implementing two functions
 * 				  init_touch_slider()		 - to configure TSI
 *				  scan_LH_touch_slider(void) - to obtain TSI slider values
 *
 * Tools used	: MCUXpresso,FRDM-KL25Z dev board
 *
 * Identification of any leveraged code:
 *
 * Applicable Links:
 * Capacitive touch logic source:
 * https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 * Howdy Pierce Lecture notes and slides
 *
 */
#include "include_headers.h"
#define TSI_OFFSET 430
#define TSI0_DATA TSI0->DATA


/**
 *
 * @function	: function to set the clock and configure TSI
 *
 * @parameters	: none
 * @return		: returns NULL
 */
void init_touch_slider()
{
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;		//setting the clock for TSI

	TSI0->GENCS = TSI_GENCS_MODE(0u) | 		//operating in non-noise mode
					TSI_GENCS_REFCHRG(0u) | //reference oscillator charge and discharge value 500nA
					TSI_GENCS_DVOLT(0u) | 	//oscillator voltage rails set to default
					TSI_GENCS_EXTCHRG(0u) | //electrode oscillator charge and discharge value 500nA
					TSI_GENCS_PS(0u) |  	// frequency clcok divided by one
					TSI_GENCS_NSCN(31u) | 	//scanning the electrode 32 times
					TSI_GENCS_TSIEN_MASK | //enabling the TSI module
					TSI_GENCS_EOSF_MASK; 	// writing one to clear the end of scan flag
}

/**
 * @function	: Function to read touch sensor value
 *
 * @param		: NULL
 * @return		: returns the touch sensor value
 *
 */
int scan_LH_touch_slider(void)
{
	unsigned int ch_10 = 0;
	TSI0_DATA = 	TSI_DATA_TSICH(10u);
	TSI0_DATA |= TSI_DATA_SWTS_MASK; 					//software trigger to start the ch_10
	while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK )); 		// waiting for the scan to complete 32 times
	for(int i=0;i<2500;i++);
	ch_10 = TSI0_DATA & 0xFFFF;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; 				//writing one to clear the end of ch_10 flag

	return (ch_10-TSI_OFFSET);
}


