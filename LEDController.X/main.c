#ifndef MAIN_C
#define MAIN_C

// Global includes
#include <htc.h>
#include <stdio.h>

// Local includes
#include "hardware.h"
#include "fft.h"
#include "WS2812.h"
#include "math.h"

#pragma config FOSC=HS2
//#pragma config FOSC=INTIO2
#pragma config PLLCFG = ON
#pragma config XINST = OFF

//#define set_bits_macro(port,mask) ((port) |= (mask))
// Globals



void main(void)
{
	// PIC port set up --------------------------------------------------------

//    PLLEN=1;
	// Configure on-board ADC
	// Vss and Vdd as voltage references
    
    ADCON1 = 0b00000000;
//    ADIE=0;
	// Configure the ADC acquisition time according to the datasheet
	ADCON2 = 0b10110110; // Note: output is right justified
    /*
     * Configure ports as inputs (1) or outputs(0)
     *         76543210
     * Do not use port A since that is mostly reserved for ADC purposes
     * All Port B,C and D's 0th and 1st bit needs to be output.
     * Others are free to do something else.    
     * 
     * 
     * The following pins and their respective uses. If any of these pins are active
     * then the program will respond differently (see below)
     * B3-B7: LED On/Off, [UNUSED],Music Playing/Pause, [UNUSED], Spectrum mode
     * C4,C5: Red Green Mode each base, Red Green mode for strips
     * C6,C7: Random LED color, Ring animation
     * 
     * IMPORTANT: There are priorities that needs to be taken into consideration
     * 
     * If LED on/off (B3) is high, no lights will be on. This is the highest priority pin
     * 
     * Any animation on Port C (C4-C7) can be activated whether music is playing or not (B5 and B6).
     * 
     * Ignore the below, the pause pin (B6) is not used anymore in design.
     * 
     * Spectrum mode will only be activated if B3 is low, B5 is high,
     * B6 is low and B7 is high (aka PORTB=0b10100000) irregardless of whatever
     * pins on Port C is high
     * If B6 is low when spectrum is active, then program should cycle between
     * the other animations for 5 iterations and then moving to another animation.
     * 
     * 
    */
	TRISA = 0b00000001;
	TRISB = 0b11111000;
	TRISC = 0b11110000;
	TRISD = 0b00000000;


	// Clear all ports
	PORTA = 0b00000000;
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	PORTD = 0b00000000;


    PLLEN=1;
    //OSCCON is used for debugging. This is due to the debuggger
    //Not able to use external crystal 
//    OSCCON=111;

    //Please refer to the TRISX setup as to the logic for the while loop
	while(1)
	{
        if(PORTBbits.RB3==1){
            clearAllLEDs();
        }
        else{
            if(PORTBbits.RB7==1 && PORTBbits.RB5==1){
                fftMode();    
            }
            else{
                if (PORTCbits.RC4==1)redGreenLevels();
                if (PORTCbits.RC5==1)redGreenStrips();
                if (PORTCbits.RC6==1)randomLight();
                if (PORTCbits.RC7==1)ring();
                //You should onlly get to the else statement below if 
                //None of the above is matched
                if(PORTCbits.RC4==0 && PORTCbits.RC5==0 && PORTCbits.RC6==0 && PORTCbits.RC7==0){
                    randomLight();
//                    for (int i=0; i<10;i++) randomLight();
//                    for (int i=0; i<10;i++) ring();
//                    for (int i=0; i<10;i++) redGreenStrips();
//                    for (int i=0; i<10;i++) redGreenLevels();                    
                }
            }
        }
        

	}
}

#endif
