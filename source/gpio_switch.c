/********************************************
 * Title		: gpio_switch.c
 * Author		: Visalakshmi Chemudupati
 *
 * Description	: Implementing three functions
 * 				  init_interrupt(void)		- configure interrupt
 * 				  gpiod_IRQhandler(void)	-	to call the gpio interrupt
 *
 * Tools used	: MCUXpresso,FRDM-KL25Z dev board
 *
 * Identification of any leveraged code:
 *
 * Applicable Links:
 * Howdy Pierce's lecture slides
 * Alexander  Dean github and textbook
 *
 */

#include <stdio.h>
#include "board.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "log.h"
#include "pwm.h"
#include "pin_mux.h"
#include "core_cm0plus.h"
#include "capacitive_touch_sensor.h"
#include "statemachine.h"
#include "gpio_switch.h"
#include "peripherals.h"

#define GPIO_SWITCH		(6)
#define GPIO_SWITCH_MUX (1)
#define GPIO_SWITCH_IRQ (0x0a)

extern int button_status_flag; //flag to identify if button is pressed
/**
 * @function	: function to configure the interrupt for a GPIO
 * 					switch. PORTD Pin 7 is used to connect the external
 * 					switch. PortD is configured to generate an interrupt
 * 					on the falling edge of input signal.
 *
 * @parameters	: NULL
 * @return		: returns NULL
 */
void init_interrupt()
{
	// enable clock to PORT D
	SIM->SCGC5 |=SIM_SCGC5_PORTD_MASK;

	//configure GPIO switch
	PORTD->PCR[ GPIO_SWITCH] |= PORT_PCR_MUX(GPIO_SWITCH_MUX);
	PORTD->PCR[ GPIO_SWITCH] |= PORT_PCR_PS_MASK;
	PORTD->PCR[ GPIO_SWITCH] |= PORT_PCR_PE_MASK;
	PORTD->PCR[ GPIO_SWITCH] |= PORT_PCR_IRQC(GPIO_SWITCH_IRQ); // configuring falling edge interrupt

	PTD->PDDR &= ~(1 <<  GPIO_SWITCH);; //Setting switch as input

	//configuring NVIC
	NVIC_SetPriority(PORTD_IRQn,2);
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	NVIC_EnableIRQ(PORTD_IRQn);

}

/**
 * @function	: function to change to the CROSSWALK state
 * 					and print the change in states when interrupt
 * 					is detected.
 *
 * @parameters	: NULL
 * @return		: returns NULL
 */

void PORTD_IRQHandler()
{
	//Clearing pending IRQ
	NVIC_ClearPendingIRQ(PORTD_IRQn);

	button_status_flag=1; //Setting switch_pressed

	//Clear Int flag
	PORTD->ISFR |= (1 << GPIO_SWITCH);
}
