/********************************************
 * Title		: gpio.h
 * Author		: Visalakshmi Chemudupati
 *
 * Description	: Implementing two functions
 * 				  init_interrupt()	- to configure the gpio interrupt
 * 				  PORTD_IRQHandler()- to call the gpio interrupt
 *
 * Tools used	: MCUXpresso,FRDM-KL25Z dev board
 *
 * Identification of any leveraged code:
 *
 * Applicable Links:
 * Howdy Pierce's elevator example
 *
 */

#ifndef GPIO_SWITCH_H_
#define GPIO_SWITCH_H_

/**
 * @function	: function to configure the interrupt for a GPIO
 * 					switch. PORTD Pin 6 is used to connect the external
 * 					switch. PortD is configured to generate an interrupt
 * 					on the falling edge of input signal.
 *
 * @parameters	: NULL
 * @return		: returns NULL
 */
void init_interrupt();



#endif // GPIO_SWITCH_H_
