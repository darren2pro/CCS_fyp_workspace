#include "main.h"

int i = 1;

void terminateGPIOPortA_B(void)
{
    // Port A consists of P1 and P2
	P1DIR = 0xFF;
	P1OUT = 0x00;

	P2DIR = 0xFF;
    P2OUT = 0x00;

    // Port B consists of P3 and P4
    P3DIR = 0xFF;
    P3OUT = 0x00;

    P4DIR = 0xFF;
    P4OUT = 0x00;
}

void configureGPIOForExternalLogicAnalyzer(void) {
    // Configure GPIO for external logic analyzer P1.5

    // Set the direction of P1.5 to output.
    P1DIR |= BIT5;

    // Set the output value of P1.5 to high.
    P1OUT |= BIT5;
}

void setActiveMode(void)
{
	__bic_SR_register(CPUOFF);
	__bic_SR_register(SCG0);
	__bic_SR_register(SCG1);
	__bic_SR_register(OSCOFF);
	__no_operation();
}

void setLpm0(void)
{
	__bis_SR_register(LPM0_bits);
	__no_operation();
}

void setLpm1(void)
{
	__bis_SR_register(LPM1_bits);
	__no_operation();
}

void setLpm2(void)
{
	__bis_SR_register(LPM2_bits);
	__no_operation();
}

void setLpm3(void)
{
	__bis_SR_register(LPM3_bits);
	__no_operation();
}

void setLpm3_5(void)
{
	// Open PMM registers for write
    PMMCTL0_H = PMMPW_H;

    // Set PMMREGOFF bit in PMMCTL0_L to turn off regulator
    PMMCTL0_L |= PMMREGOFF;
	__bis_SR_register(LPM3_bits + GIE);
	__no_operation();
}

void setLpm4(void)
{
	__bis_SR_register(LPM4_bits);
	__no_operation();
}

void setLpm4_5(void)
{
	// Open PMM registers for write
    PMMCTL0_H = PMMPW_H;

    // Set PMMREGOFF bit in PMMCTL0_L to turn off regulator
    PMMCTL0_L |= PMMREGOFF;
	__bis_SR_register(LPM4_bits + GIE);
	__no_operation();
}

void setFrequencyOfMCLK(int frequency)
{
	/*// Open PMM registers for write
    PMMCTL0_H = PMMPW_H;

    // Set frequency of MCLK
    switch (frequency)
    {
        case 1:
            PMMCTL2 = SELM__LFXTCLK;
            break;
        case 2:
            PMMCTL2 = SELM__VLOCLK;
            break;
        case 3:
            PMMCTL2 = SELM__DCOCLK;
            break;
        case 4:
            PMMCTL2 = SELM__XT1CLK;
            break;
        case 5:
            PMMCTL2 = SELM__REFOCLK;
            break;
        case 6:
            PMMCTL2 = SELM__DCOCLKDIV;
            break;
        case 7:
            PMMCTL2 = SELM__XT2CLK;
            break;
        default:
            PMMCTL2 = SELM__DCOCLK;
            break;
    }

    // Lock PMM registers for write access
    PMMCTL0_H = 0x00;*/
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
    configureGPIOForExternalLogicAnalyzer();

	while (1)
	{
		i++;
		i--;
	}
	
    return 0;
}
