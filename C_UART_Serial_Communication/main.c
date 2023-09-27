#include "main.h"

void InitSharedReferenceModule(void)
{
	// Initialize the shared reference module
  	// By default, REFMSTR=1 => REFCTL is used to configure the internal reference
	// REFMSTR = 0 or 1 decides whether we use the shared reference module or the internal reference
	// voltage generator for generating the reference voltage. We use the shared reference if we want multiple peripherals to have access
	// to that generated voltage.
  	while (REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT

	/*
	REFVSEL_0 --> REFVSEL_0 and REFVSEL_1: These bits select the reference voltage source. 
	The reference voltage source can be the internal 1.2V reference, the internal 2.5V reference, 
	or an external reference voltage.
	REFON --> Enables the internal reference voltage generator. Enable internal 1.2V reference
	*/
	REFCTL0 |= REFVSEL_0 + REFON;
}

void InitADC12BModule(void)
{
    // Initialize ADC12_B
    ADC12CTL0 &= ~ADC12ENC;                   // Disable ADC12
    /*
     * ADCSHTx can only be modified when ADCENC = 0. Resetting ADCENC = 0 by software then changing these fields
     * immediately shows an effect when a conversion is active.
     */


}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	



	return 0;
}
