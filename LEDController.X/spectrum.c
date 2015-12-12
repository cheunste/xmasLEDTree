
/* 
 * File:   spectrum.c
 * Author: stephen
 *
 * Created on July 8, 2015, 4:19 PM
 */

#include <xc.h>
#include "pic18f46k80.h"
//#include "config.h"
#include "WS2812.h"
#include "spectrum.h"
#include "fft.h"
#include "math.h"


short imaginaryNumbers[64];
short realNumbers[64];
float lowEndFreq[]={312.5 , 625, 937.5 , 12, 1562.5, 1875,
    2187.5, 2500, 2812.5, 3125, 3437.5, 3750,
    4062.5, 4375, 4687.5, 5000, 5312.5, 5625,
    5937.5, 6250, 6562.5, 6875, 7187.5, 7500,
    7812.5, 8125, 8437.5, 8750, 9062.5, 9375,
    9687.5
};
float highEndFreq[]={625, 937.5, 1250, 1562.5, 1875, 2187.5,
    2500, 2812.5, 3125, 3437.5, 3750, 4062.5,
    4375, 4687.5, 5000, 5312.5, 5625, 5937.5,
    6250, 6562.5, 6875, 7187.5, 7500, 7812.5,
    8125, 8437.5, 8750, 9062.5, 9375, 9687.5,
    10000};

void spectrum(void){
    
    
		// Perform the FFT

		// Get 64 samples at 50uS intervals
		// 50uS means our sampling rate is 20KHz which gives us
		// Nyquist limit of 10Khz
        short int i = 0;
		unsigned short result;
		for (i = 0; i < 64; i++)
		{
			// Perform the ADC conversion
			// Select the desired ADC and start the conversion
			ADCON0 = 0b00000011; 	// Start the ADC conversion on AN0
		
			// Wait for the ADC conversion to complete
			TESTPIN_W4 = 1; // Don't remove this... it will affect the sample timing
			while(GODONE);
			TESTPIN_W4 = 0; // Don't remove this... it will affect the sample timing
			
			// Get the 10-bit ADC result and adjust the virtual ground of 2.5V
			// back to 0Vs to make the input wave centered correctly around 0
			// (i.e. -512 to +512)
//			realNumbers[i] = ((short)(ADRESH << 8) + (short)ADRESL) - 2048;
			realNumbers[i] = ((short)(ADRESH << 8) + (short)ADRESL)-512;
			
			// Set the imaginary number to zero
			imaginaryNumbers[i] = 0;
			
			// This delay is calibrated using an oscilloscope according to the 
			// output on RA1 to ensure that the sampling periods are correct
			// given the overhead of the rest of the code and the ADC sampling
			// time.
			//
			// If you change anything in this loop or use the professional 
			// (optimised) version of Hi-Tech PICC18, you will need to re-
			// calibrate this to achieve an accurate sampling rate.
			__delay_us(7);
		}

		// Perform the (forward) FFT calculation

		// Note: the FFT result length is half of the input data length
		// so if we put 64 samples in we get 32 buckets out.  The first bucket
		// cannot be used so in reality our result is 31 buckets.
		//
		// The maximum frequency we can measure is half of the sampling rate
		// so if we sample at 20Khz our maximum is 10Khz (this is called the 
		// Nyquist frequency).  So if we have 32 buckets divided over 10Khz,
		// each bucket represents 312.5Khz of range, so our lowest bucket is
		// (bucket 1) 312.5Hz - 625Hz and so on up to our 32nd bucket which
		// is 9687.5Hz - 10,000Hz
		
		//  1 : 312.5 - 625
		//  2 : 625 - 937.5
		//  3 : 937.5 - 1250
		//  4 : 1250 - 1562.5
		//  5 : 1562.5 - 1875
		//  6 : 1875 - 2187.5
		//  7 : 2187.5 - 2500
		//  8 : 2500 - 2812.5
		//  9 : 2812.5 - 3125
		// 10 : 3125 - 3437.5
		// 11 : 3437.5 - 3750
		// 12 : 3750 - 4062.5
		// 13 : 4062.5 - 4375
		// 14 : 4375 - 4687.5
		// 15 : 4687.5 - 5000
		// 16 : 5000 - 5312.5
		// 17 : 5312.5 - 5625
		// 18 : 5625 - 5937.5
		// 19 : 5937.5 - 6250
		// 20 : 6250 - 6562.5
		// 21 : 6562.5 - 6875
		// 22 : 6875 - 7187.5
		// 23 : 7187.5 - 7500
		// 24 : 7500 - 7812.5
		// 25 : 7812.5 - 8125
		// 26 : 8125 - 8437.5
		// 27 : 8437.5 - 8750
		// 28 : 8750 - 9062.5
		// 29 : 9062.5 - 9375
		// 30 : 9375 - 9687.5
		// 31 : 9687.5 - 10000
		
		// Note: the '6' is the size of the input data (2 to the power of 6 = 64)
		TESTPIN_W5 = 1;
		fix_fft(realNumbers, imaginaryNumbers, 6);
		
		// Take the absolute value of the FFT results
		
		// Note: The FFT routine returns 'complex' numbers which consist of
		// both a real and imaginary part.  To find the 'absolute' value
		// of the returned data we have to calculate the complex number's
		// distance from zero which requires a little pythagoras and therefore
		// a square-root calculation too.  Since the PIC has multiplication
		// hardware, only the square-root needs to be optimised.          
		long place, root;
        for (int k=0; k < 32; k++)
        {
	        realNumbers[k] = (realNumbers[k] * realNumbers[k] + 
                   imaginaryNumbers[k] * imaginaryNumbers[k]);
                   
            // Now we find the square root of realNumbers[k] using a very
            // fast (but compiler dependent) integer approximation:
            // (adapted from: http://www.codecodex.com/wiki/Calculate_an_integer_square_root)
            place = 0x40000000;
			root = 0;
			
			if (realNumbers[k] >= 0) // Ensure we don't have a negative number
			{
				while (place > realNumbers[k]) place = place >> 2; 
				
				while (place)  
				{  
					if (realNumbers[k] >= root + place)  
					{  
						realNumbers[k] -= root + place;  
						root += place * 2;  
					}  
					root = root >> 1;  
					place = place >> 2;  
				}
			}
			realNumbers[k] = root;
	    }
	    TESTPIN_W5 = 0;
	    
	    // Now we have 32 buckets of audio frequency data represented as
	    // linear intensity in realNumbers[]
	    //
	    // Since the maximum input value (in theory) to the SQRT function is
	    // 32767, the peak output at this stage is SQRT(32767) = 181.
	    
	    // Draw a bar graph of the FFT output data
	    TESTPIN_W6 = 1;
        LATCbits.LATC4=1;
        for(int m=0; m<1000;m++){
        __delay_ms(5);            
        }
	    writeLED(realNumbers);
        LATCbits.LATC4=0;
        for(int m=0; m<1000;m++){
        __delay_ms(5);            
        }
}

//This calculates how many LEDs are suppose to be lit up based on the 
//parameters passed to it. The maximum number of LED on a strip,
//the inputValue (the value from the FFT array).
//This also uses a max value of 181, which is  the theoritical maximum input value
//of the peak output from the spectrum function
int calcLEDLightup(int LEDonStrip, int inputValue){
    
    float maxInputValue=181.0;
    int ledLightUp=(int)floor(((float)inputValue/maxInputValue)*(float)LEDonStrip);
    
    //In case returnValue is 0, just make it light up one LED.
    if(ledLightUp <=1){
        ledLightUp=1;
    }
    return ledLightUp;
//    return 1.0;
};

//Need to be deleted
int ratioSquare(float freq){
    return 1;
}
//This method translate the FFT array to write to an LED Strip. 
//There might be a chance I will not use half of the 32 buckets given
//due to I/O constrict
//The scaling is from the original drawFftGraph() code
void writeLED(short inputData[]){
    
	int inputValue;
	int LEDonStrip=3;
	// Scale the input data to 0-63 and perform the dampening of the display
    // 13 : 4062.5 - 4375
 	for (unsigned char counter = 5; counter < 28; counter++)
	{
        inputValue = inputData[counter];
        
        //If value that came from FFT is over 181, then most likely there is
        //a calculation or an overflow issue with the code. If input value is over 181,
        //just let inputValue be 181. Same logic applies with negative numbers
        if (inputValue >181){
            inputValue = 181;
        }
        if (inputValue <0){
            inputValue =0;
        }
//        int lowEndTemp=ratioSquare(lowEndFreq[counter-5]);
//        int highEndTemp=ratioSquare(highEndFreq[counter-5]);
        
        //port and portNumber are used to inform what port pin to send 
        //the led data array to in the ws2812.c file
        char port='B';
        int portNumber;
        int LEDLightup;
        
        //The following if statements decide on how many LEDs each strip
        //will be using since each strip represents a frequency bucket.
        //This is also the function where each strip will be mapped to a specific
        //port on the microcontroller. The portNumber will be decided based
        //on the frequency bucket number.
        if(counter >=5 && counter<=8){
            port='B';
            portNumber=(int)(counter-5);
            LEDonStrip=13;
            LEDLightup = calcLEDLightup(LEDonStrip,inputValue);
//            spectrumLight(LEDonStrip,LEDLightup,port,portNumber,strip13);
        }
        if(counter >=9 && counter<=12){
            port='B';
            portNumber=(int)(counter-5);
            LEDonStrip=13;
            LEDLightup = calcLEDLightup(LEDonStrip,inputValue);
//            spectrumLight(LEDonStrip,LEDLightup,port,portNumber,strip13);
        }
        if(counter >=13 && counter <=16){
            port='C';
            portNumber=(int)(counter-13);
            LEDonStrip=10;
            LEDLightup = calcLEDLightup(LEDonStrip,inputValue);
//            spectrumLight(LEDonStrip,LEDLightup,port,portNumber,strip10);
        }
        if(counter >=17 && counter <=20){
            port='C';
            portNumber=(int)(counter-13);
            LEDonStrip=8;
            LEDLightup = calcLEDLightup(LEDonStrip,inputValue);
//            spectrumLight(LEDonStrip,LEDLightup,port,portNumber,strip8);
        }
        if(counter >=21 && counter <=24){
            port='D';
            portNumber=(int)(counter-21);
            LEDonStrip=5;
            LEDLightup = calcLEDLightup(LEDonStrip,inputValue);
//            spectrumLight(LEDonStrip,LEDLightup,port,portNumber,strip5);
        }
        if(counter >=25 && counter <=28){
            port='D';
            portNumber=(int)(counter-21);
            LEDonStrip=4;
            LEDLightup = calcLEDLightup(LEDonStrip,inputValue);
            spectrumLight(LEDonStrip,LEDLightup,port,portNumber,strip4);
        }

	}
}

