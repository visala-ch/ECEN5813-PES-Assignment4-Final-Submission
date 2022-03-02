/********************************************
 * Title		: pwm.h
 * Description	: Abstraction of three functions that configure the
 * 					TPM and compute LED colors
 *
 * Author		: Visalakshmi Chemudupati
 *
 */


#ifndef PWM_LED_H_
#define PWM_LED_H_
#define CLK_PERIOD 48000
/**
 * @function	: function to configure the TPM for RGB LEDs
 * 					and control the LEDs using PWM. Clock source
 * 					set as 48MHz.
 *
 * @parameters	: clock period
 * @return		: NULL
 */
void init_PWM_LED(uint16_t period);

/**
 * @function	: function to toggle the LED on and off using
 * 					Control registers of red, green and blue color.
 * 					Values of RGB are computed using CLK_PERIOD and
 * 					RGB_MAX_VAL which give the maximum values that can
 * 					be set for the brightest level of LEDs.
 *
 * @parameters	: RGB colors are given as parameters
 * @return		: NULL
 */
void set_color(int r, int g, int b);

/**
 * @function	: function to compute the values of RGB for the color
 * 					transition between different states with a period
 * 					of 1sec using the given mathematical equation and
 * 					starting and ending values of RGB for each state.
 *
 * @parameters	: NULL
 * @return		: NULL
 */
void color_transition();

#endif /* PWM_LED_H_ */
