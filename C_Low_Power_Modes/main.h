/*******************************************************************************
 *
 * main.h
 *
 * Different LPMs for taking readings
 *
 * Darren
 *
 ******************************************************************************/
 
#include <msp430.h>

/**
 * Terminate GPIO Port A and B to save power. I do this before entering any of the low power modes.
 */
void terminateGPIOPortA_B(void);
void configureGPIOForExternalLogicAnalyzer(void);

void setActiveMode(void);
void setLpm0(void);
void setLpm1(void);
void setLpm2(void);
void setLpm3(void);
void setLpm3_5(void);
void setLpm4(void);
void setLpm4_5(void);

/**
 * Set MCLK to 8MHz. This is the master clock. This is the clock that drives the CPU.
 * Description: Configure SMCLK = MCLK = xMHz.
 * The range goes even up to
 */
void setMCLK1MHz(void);
void setMCLK4MHz(void);
void setMCLK7MHz(void);
void setMCLK8MHz(void);
void setMCLK16MHz(void);
