/********************************************
 * Title		: capacitive_touch.h
 * Description	: Abstraction of two functions to configure the TSI module
 * 					and read the TSI value
 * Author		: Visalakshmi Chemudupati
 *
 */

#ifndef TSI_CONFIG_H_
#define TSI_CONFIG_H_

/**
 *
 * @function	: function to set the clock and configure TSI
 *
 * @parameters	: none
 * @return		: returns NULL
 */
void init_touch_slider();

/**
 * @function	: function to extract the touch capacitive sensor value
 *
 * @param		: NULL
 * @return		: returns the touch sensor value
 *
 */
int scan_LH_touch_slider(void);


#endif /*TSI_CONFIG_H_*/
