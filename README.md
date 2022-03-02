# PES-Assignment 4 BUFFAHITI TRAFFIC LIGHTS
File name: Buffahiti_Traffic_Lights

### State Machine Logic:
A finite state machine is used to implement the application. 6 states are used :
1. STOP
2. GO
3. WARNING
4. TRANSITION
5. CROSSWALK
6. CROSSWALK_TRANSITION
7. CROSSWALK_GO_TRANSITION

The STOP, GO, WARNING are considered solid states representing the traffic lights colors and CROSSWALK state is for when the Buffahiti residents want to cross the street representing a blinking LED patter.  A TRANSITION state is used for color transitioning between all states. The CROSSWALK_TRANSITION is used for color transition from any state to the CROSSWALK_STATE.  Each time the state machine enters CROSSWALK state, it has to next go to the GO state, so a CROSSWALK_GO_TRANSITION state is used for this.

Each of the solid states and CROSSWALK state have predefined starting color codes. The start color code for GO is the end color code for STOP state and so on. 

The state machine runs forever, with each state moving to the TRANSITION state first to allow gradual transition between the colors to the next state, unless the capacitive touch slider is touched or a button press event occurs. In such a case, the state transitions from any state to the CROSSWALK state, except when the state is already in either the CROSSWALK state or the CROSSWALK transition state. So the movement between states takes place as below: <br/>
If no button press or TSI is not touched:<br/>
STOP -> TRANSITION -> GO -> TRANSITION ->WARNING->TRANSITION->STOP so on.

When TSI touch detected or button pressed:<br/>
Current_State ->CROSSWALK_TRANSITION->CROSSWALK->CROSSWALK_GO_TRANSITION->GO->TRANSITION->WARNING->TRANSITION->STOP and so on.<br/>
Here, Current_State can be any of the: STOP, GO, WARNING, TRANSITION states

The traffic light should transition from one state to other in a period of 1sec, no more or no less. <br/>
In DEBUG mode, each of the STOP and GO states should hold the color for 5 sec and WARNING state should hold the color for 3 seconds with a transition period of 1 sec between all states. <br/>
In PRODUCTION (Release) mode, the STOP and GO states hold the LED color for 20 seconds each and WARNING state for 5 seconds. <br/>
In the CROSSWALK state the light blinks 250 msec off, 750 msec on. In all other states, the light is solid (not blinking). <vr/>

### Approach:
A Systick timer module is configured at 125 msec to maintain the time between each transition. After each transition, the timer is reset.<br/> 
A separate timer is maintained for the CROSSWALK states to not interfere with the timer for the rest of the states. <br/>
A PWM module is configured to maintain and control the LED colors and the transitions between each color.<br/>

### Builds:
Two builds were used: DEBUG and PRODUCTION(Release). The debug mode prints the diagnostic output while PRODUCTION mode does not. The CROSSWALK functionality remains the same in both modes while Solid States functionality changes as mentioned above.<br/>
To build the project:<br/>
In the Projects tab on the left, go to the current project and right click on it. -> Build Configurations -> Set Active-> choose DEBUG to build in debug mode.<br/>
Set Active ->choose Release to build in Release mode. <br/>
Then click on the blue bug on the menu bar to start debug session.

### Terminal:
To see the serial output: select baud rate as 115200

### Extra Credit1: Peer Review
Partner name: Akshay Kapse<br/>
Date and Time:  3-March-2022 1PM <br/>
Changes made: 1. Created another state CROSSWALK_TRANSITION to make the transition between the states smoother.<br/>
              2. Added () to the #defines which have numerical values<br/>

### Extra Credit 2: GPIO Switch
GPIO Pin is used as an external interrupt to move from any state to crosswalk state. The GPIO pin is defined at PORT D Pin6.

