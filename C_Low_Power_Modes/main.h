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

void setFrequencyOfMCLK(int frequency);
