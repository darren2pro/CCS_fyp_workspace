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

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;
	terminateGPIOPortA_B();
	setLpm1();

	while (1)
	{
		i++;
		i--;
	}
	
    return 0;
}
