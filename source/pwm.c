/********************************************
 * Title		: pwm.c
 * Author		: Visalakshmi Chemudupati
 *
 * Description	: implementing three functions:
 * 					init_PWM_LED(period)- to configure and initialize the TPM module
 * 					set_color(r, g, b)	- to compute the LED values and set the colors
 * 					color_transition()	- to compute values of LEDs for color transition
 * 											from one state to next
 * Tools used	: MCUXpresso,FRDM-KL25Z dev board
 *
 * Identification of any leveraged code:
 *
 * Applicable Links:
 * https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 *
 * Howdy Pierce's lecture slides and notes
 *
 */
#include <include_headers.h>

#define RED_LED_PIN		(18)
#define RED_LED_PIN_CTL_REG 	PORTB->PCR[RED_LED_PIN]

#define GREEN_LED_PIN	(19)
#define GREEN_LED_PIN_CTL_REG 	PORTB->PCR[GREEN_LED_PIN]

#define BLUE_LED_PIN	(1)
#define BLUE_LED_PIN_CTL_REG 	PORTD->PCR[BLUE_LED_PIN]

#define RGB_MAX_VALUE 255

/**
 * @function	: function to configure the TPM for RGB LEDs
 * 					and control the LEDs using PWM. Clock source
 * 					set as 48MHz.
 *
 * @parameters	: NULL
 * @return		: NULL
 */
void init_PWM_LED(uint16_t period) {

	//enabling clock for PORTS B, D for red, green, blue LEDs
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

	//enabling clock for TPM0, TPM2
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

	//setting pins to FTM
	RED_LED_PIN_CTL_REG&= ~PORT_PCR_MUX_MASK;
	RED_LED_PIN_CTL_REG|= PORT_PCR_MUX(3);

	GREEN_LED_PIN_CTL_REG&= ~PORT_PCR_MUX_MASK;
	GREEN_LED_PIN_CTL_REG|= PORT_PCR_MUX(3);

	BLUE_LED_PIN_CTL_REG&= ~PORT_PCR_MUX_MASK;
	BLUE_LED_PIN_CTL_REG|= PORT_PCR_MUX(4);

	//set clock for TPM to 48Mhz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1));

	//configure TPM2
	TPM2->MOD = period - 1;						//loading the counter
	TPM2->SC = TPM_SC_PS(1);						//set the TPM counter direction to up with the prescaler of 2
	TPM2->CONF |= TPM_CONF_DBGMODE(3);				//continue operation in DEBUG mode

	//configure TPM0
	TPM0->MOD = period - 1;						//loading the counter
	TPM0->SC = TPM_SC_PS(1);						//set the TPM counter direction to up with the prescaler of 2
	TPM0->CONF |= TPM_CONF_DBGMODE(3);				//continue operation in DEBUG mode

	//setting TPM control register for RED LED
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK |	//set channel 0 to edge aligned low-true PWM
							 TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[0].CnV = 0;						//set initial duty cycle as 0
	TPM2->SC |= TPM_SC_CMOD(1);						//start TPM

	//setting TPM control register for GREEN LED
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | 	//set channel 1 to edge aligned low-true PWM
							 TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[1].CnV = 0;						//set initial duty cycle as 0
	TPM2->SC |= TPM_SC_CMOD(1);						//start TPM

	//setting TPM control register for BLUE LED
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK |	//set channel 1 to edge aligned low-true PWM
							 TPM_CnSC_ELSA_MASK;
	TPM0->CONTROLS[1].CnV = 0;						//set initial duty cycle as 0
	TPM0->SC |= TPM_SC_CMOD(1);						//start TPM
}

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
void set_color(int r, int g, int b) {
	int red = (r * CLK_PERIOD) / RGB_MAX_VALUE;
	int green = (g * CLK_PERIOD) / RGB_MAX_VALUE;
	int blue = (b * CLK_PERIOD) / RGB_MAX_VALUE;

	TPM2->CONTROLS[0].CnV = red;
	TPM2->CONTROLS[1].CnV = green;
	TPM0->CONTROLS[1].CnV = blue;
}

/**
 * @function	: function to compute  and set the values of RGB for the color
 * 					transition between different states with a period
 * 					of 1sec using the given mathematical equation and
 * 					starting and ending values of RGB for each state.
 *
 * @parameters	: NULL
 * @return		: NULL
 */
extern int red_start_val;
extern int red_end_val;
extern int green_start_val;
extern int green_end_val;
extern int blue_start_val;
extern int blue_end_val;
int r = 0, g = 0, b = 0, timer = 0;

void color_transition(void) {
	timer = get_timer();
	r = ((red_end_val - red_start_val) * 0.01 * timer) + red_start_val;
	g = ((green_end_val - green_start_val) * 0.01 * timer) + green_start_val;
	b = ((blue_end_val - blue_start_val) * 0.01 * timer) + blue_start_val;
	set_color(r, g, b);
}
