#include "main.h"


/**
 * main.c
 *
 * This is to use Interrupt Requests (IRQs), and utilize the interrupt service routines in MSP430.
 */

void activateGPIO(void) {
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode to activate configured port settings
}

/**
 * This is to clear the interrupt flag for P4.5. We usually do this after handling the IRQ.
 */
void clearP4_5_IFG() {
    P4IFG &= ~BIT5; // P4.5 IFG cleared
}

void configureLED1(void) {
    P4DIR |= BIT6;        // Set P4.6 to output direction
    P4OUT &= ~BIT6;       // Initialize P4.6 to 0 to make it off
}

void configureSwitch1(void) {
    P4DIR &= ~BIT5;       // Set P4.5 to input direction
    P4REN |= BIT5;        // Enable P4.5 internal resistance
    P4OUT |= BIT5;        // Set P4.5 as pull-Up resistance

    // Since we are doing interrupts, we need to set these to enable interrupts
    /**
     * P4.5 Hi/Lo edge. Makes interrupt edge fire when there's a transition from high to low. When I press, it turns
     * to zero, and when I am not pressing the switch, the pull-UP resistor sets it to 1.
     */
    P4IES |= BIT5;
    P4IE |= BIT5;         // Enable P4.5 interrupt (local)
    __enable_interrupt(); // Enable maskable interrupt requests (global)
    clearP4_5_IFG();      // Clear P4.5 interrupt flag
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	configureLED1();
    configureSwitch1();
    activateGPIO();
    while (1);
	return 0;
}

//--- ISRs ----//
/**
 * This is the interrupt service routine for Port 4. It is called when there is a transition from high to low on
 * P4.5. This is because we set P4IES |= BIT1; in configureSwitch1() to make it fire on a high to low transition.
 *
 * Basically this pragma is telling the compiler that this is the interrupt service routine for Port 4.
 * Pragma basically is used if you want to talk to the compiler real quick. Here we are telling the compiler that
 * the address of the next routine right here, we want to put it in the interrupt vector table at the location of
 * port 4.
 */
#pragma vector=PORT4_VECTOR
__interrupt void ISR_Port_4_Switch_1(void) {
    P4OUT ^= BIT6; // Toggle P4.6
    // P4IFG &= ~BIT5; // P4.5 IFG cleared
    clearP4_5_IFG();
}
