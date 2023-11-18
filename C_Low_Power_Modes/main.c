#include "main.h"
#include "driverlib.h"

void terminateGPIOPortA_B(void) {
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

void setActiveMode(void) {
    __bic_SR_register(CPUOFF);
    __bic_SR_register(SCG0);
    __bic_SR_register(SCG1);
    __bic_SR_register(OSCOFF);
    __no_operation();
}

void setLpm0(void) {
    __bis_SR_register(LPM0_bits);
    __no_operation();
}

void setLpm1(void) {
    __bis_SR_register(LPM1_bits);
    __no_operation();
}

void setLpm2(void) {
    __bis_SR_register(LPM2_bits);
    __no_operation();
}

void setLpm3(void) {
    __bis_SR_register(LPM3_bits);
    __no_operation();
}

void setLpm3_5(void) {
    // Open PMM registers for write
    PMMCTL0_H = PMMPW_H;

    // Set PMMREGOFF bit in PMMCTL0_L to turn off regulator
    PMMCTL0_L |= PMMREGOFF;
    __bis_SR_register(LPM3_bits + GIE);
    __no_operation();
}

void setLpm4(void) {
    __bis_SR_register(LPM4_bits);
    __no_operation();
}

void setLpm4_5(void) {
    // Open PMM registers for write
    PMMCTL0_H = PMMPW_H;

    // Set PMMREGOFF bit in PMMCTL0_L to turn off regulator
    PMMCTL0_L |= PMMREGOFF;
    __bis_SR_register(LPM4_bits + GIE);
    __no_operation();
}

void setMCLK1MHz(void) {
    /** Set Digitally Controlled Oscillator (DCO) Frequency to 1MHz */
    CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_0);

    /** Configure MCLK, SMCLK to source from DCOCLK */
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /** set P3.4 as output and to low */
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P3,
            GPIO_PIN4
    );

    /** set P3.4 to output SM as an analog signal */
    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P3,
            GPIO_PIN4,
            GPIO_TERNARY_MODULE_FUNCTION
    );
}

void setMCLK4MHz(void) {
    /** Set Digitally Controlled Oscillator (DCO) Frequency to 4MHz */
    CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_3);

    /** Configure MCLK, SMCLK to source from DCOCLK */
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /** set P3.4 as output and to low */
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P3,
            GPIO_PIN4
    );

    /** set P3.4 to output SM as an analog signal */
    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P3,
            GPIO_PIN4,
            GPIO_TERNARY_MODULE_FUNCTION
    );
}

void setMCLK7MHz(void) {
    /** Set Digitally Controlled Oscillator (DCO) Frequency to 7MHz */
    CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_5);

    /** Configure MCLK, SMCLK to source from DCOCLK */
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /** set P3.4 as output and to low */
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P3,
            GPIO_PIN4
    );

    /** set P3.4 to output SM as an analog signal */
    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P3,
            GPIO_PIN4,
            GPIO_TERNARY_MODULE_FUNCTION
    );
}

void setMCLK8MHz(void) {
    /**
     * Set Digitally Controlled Oscillator (DCO) Frequency to 8MHz. This information is derived from the datasheet
     * section on the DCO (titled `Table 5-6. DCO`). The DCO stands for digitally controlled oscillator.
     */
    CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_6);

    /** Configure MCLK, SMCLK to source from DCOCLK */
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /**
     * This part I had to look into the datasheet section titled `Port P3 (P3.4 to P3.7) Pin Functions` to figure out.
     * This is setting P3.4 to output SMCLK as an analog signal.
     * Enabling a GPIO pin to output the SMCLK allows flexibility in using this clock signal for external purposes
     * or interfacing with other devices that need synchronization or clocking based on the MSP430's clock system.
     * Some possible reasons that we would want to do this:
     * 1. We want to measure the frequency of SMCLK with an oscilloscope.
     * 2. We want to use SMCLK to drive an external peripheral.
     * 3. We want to use SMCLK to drive an external logic analyzer.
     * 4. We want to use SMCLK to drive an external timer.
     * 5. We want to use SMCLK to drive an external counter.
     * 6. We want to use SMCLK to drive an external ADC.
     * 7. We want to use SMCLK to drive an external DAC.
     * 8. We want to use SMCLK to drive an external PWM.
     * 9. We want to use SMCLK to drive an external interrupt.
     * 10. We want to use SMCLK to drive an external clock.
     * 11. We want to use SMCLK to drive an external watchdog timer.
     * 12. We want to use SMCLK to drive an external timer interrupt.
     * 13. We want to use SMCLK to drive an external counter interrupt.
     * 14. and many more...
     */
    /** set P3.4 as output and to low */
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P3,
            GPIO_PIN4
    );
    /** set P3.4 to output SMCLK. Had to refer to the datasheet to learn this */
    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P3,
            GPIO_PIN4,
            GPIO_TERNARY_MODULE_FUNCTION
    );

    /* This part is not used, but I keep for reference
    // Open PMM registers for write
    PMMCTL0_H = PMMPW_H;

    // Lock PMM registers for write access
    PMMCTL0_H = 0x00;
     */
}

void setMCLK16MHz(void) {
    /** Set Digitally Controlled Oscillator (DCO) Frequency to 16MHz */
    CS_setDCOFreq(CS_DCORSEL_1, CS_DCOFSEL_4);

    /** Configure MCLK, SMCLK to source from DCOCLK */
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /**
     * Set wait state form FRAM to 1 because read and write to FRAM takes longer than 1 cycle at frequencies higher
     * than 8MHz. This information is derived from the datasheet. Hence wait states are needed. This is how wait states
     * work:
     *
     * The CPU will wait for the number of cycles specified by the wait state before executing the next instruction.
     * "wait states" refer to additional clock cycles inserted to accommodate the timing requirements of certain
     * operations, particularly when accessing memory.
     *
     * When the CPU interacts with memory (like reading or writing data), the time taken for the data to be accessed
     * might not align perfectly with the CPU's speed. For instance, if the CPU runs at a certain clock frequency but
     * the memory needs more time to respond to a request due to its inherent speed limitations, wait states are
     * introduced to synchronize these operations.
     *
     * The configure wait state only takes either value 0 or 1.
     */
    FRAMCtl_configureWaitStateControl(FRAMCTL_ACCESS_TIME_CYCLES_1);

    /** set P3.4 as output and to low */
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P3,
            GPIO_PIN4
    );

    /** set P3.4 to output SM as an analog signal */
    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P3,
            GPIO_PIN4,
            GPIO_TERNARY_MODULE_FUNCTION
    );
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;    // stop watchdog timer
    setMCLK1MHz();
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    while (1);
    return 0;
}
