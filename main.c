#include <msp430f5438a.h>


/**
 * main.c
 */
unsigned int timer_ctr;
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	// SET UP CORE VOLTAGE TO ALLOW 25 MHz CLOCK
	PMMCTL0 = PMMPW | PMMCOREV_3;                               // Unlock core voltage control with password, set core voltage to level 3 (1.85 V)
    SVSMLCTL = SVSLRVL_3 | SVSMLRRL_3;                          // Set low side voltage supervisor levels based on user guide chapter 2.2.2.1.1
	SVSMHCTL = SVSHRVL_3 | SVSMHRRL_3 | SVSHPE;                 // Set high side voltage supervisor levels based on user guide chapter 2.2.2.1.2

	// SET UP 25 MHz CLOCK
	UCSCTL1 = DCORSEL_5;                                        // Set to range of 5 (2.5 to 54.1 MHz)
	UCSCTL3 = SELREF_2;                                         // Select REFOCLK (Internal 32 kHz clk) as the DCO reference clock
	UCSCTL2 = FLLD2 | FLLN5 | FLLN3 | FLLN2 | FLLN1 | FLLN0;    // Set FLL divisor to 16 (0b100) and the multiplier to 47 (0b101111) because f_dco = FLLD*(FLLN+1)*(32kHz)
	UCSCTL4 = SELS_3 | SELM_3;                                  // Set Submaster and Master clocks to be sourced from DCO
	
	// SET UP TIMER A
	TA1CTL = TASSEL_2 | MC_2;                                   // Select DCO as clock source, continuous count mode
	TA1CCTL0 = CCIE | CM_1 | CAP;                               // Capture-Compare Interrupt Enable, capture rising edge, capture mode

	// SET UP GPIO TO HAVE A 25 MHz OUTPUT ON OSC-OUT PIN
	P1SEL = BIT6;                                               // Pin special function (Output SMCLK)
	P1DIR = BIT6;                                               // Pin set to output

	//TODO: SET UP GPIO TO START TIMER A ON FIRST BUTTON PRESS


	//TODO: SET UP GPIO TO STOP TIMER AND MEASURE NUMBER OF CYCLES BETWEEN PRESSES
	return 0;
}

//TODO: SETUP TIMER A1 ISR
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void){
    if(TA1IV==0x02){                                            // If capture-compare interrupt is triggered

    }
    if(TA1CTL&TAIFG==0x0001){                                   // If timer maxes out

    }
}

//TODO: SETUP GPIO ISR
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void){

}



