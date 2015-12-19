// Global includes
#include <htc.h>
#include <stdio.h>
#include "hardware.h"
#include "fft.h"
#include "WS2812.h"
#include "math.h"

short imaginaryNumbers[64];
short realNumbers[64];
long magnitudeArray[64];

//This method translate the FFT array to write to an LED Strip. 
//There might be a chance I will not use half of the 32 buckets given
//due to I/O constrict
//The scaling is from the original drawFftGraph() code
void writeLED(long inputData[]){
    
	int inputValue;
    int portNumber;
    double maxAmplitude=0;
    char port='B';
    int LEDonStrip=3;

 	for (unsigned char counter = 1; counter < 24; counter++)
	{
        inputValue = inputData[counter];
        //port and portNumber are used to inform what port pin to send 
        //the led data array to in the ws2812.c file

        //The following if statements decide on how many LEDs each strip
        //will be using since each strip represents a frequency bucket.
        //This is also the function where each strip will be mapped to a specific
        //port on the microcontroller. The portNumber will be decided based
        //on the frequency bucket number.
		//
		//This takes care of counters 1 to 4 as they all need to be on one array
        if(counter ==1){
            port='B';
            portNumber=0;
            LEDonStrip=13;
            maxAmplitude = 300.0;
			pushToLEDStrip(inputData[counter],inputData[counter+1],inputData[counter+2],inputData[counter+3],
                    LEDonStrip,maxAmplitude,port,portNumber,strip13);
        }

		//This takes care of coutners 5 to 8 as they all need to be on one array
        else if(counter ==5){
            port='B';
            portNumber=1;
            LEDonStrip=13;
            maxAmplitude = 300.0;
            pushToLEDStrip(inputData[counter],inputData[counter+1],inputData[counter+2],inputData[counter+3],
                    LEDonStrip,maxAmplitude,port,portNumber,strip13);
        }

		//This takes care of counters 13 to 16
        else if(counter ==9){
            port='C';
            portNumber=2;
            LEDonStrip=10;
            maxAmplitude =230.0;
            pushToLEDStrip(inputData[counter],inputData[counter+1],inputData[counter+2],inputData[counter+3],
                    LEDonStrip,maxAmplitude,port,portNumber,strip10);
        }

		//This takes care of counters 13 to 16
        else if(counter ==13){
            port='C';
            portNumber=3;
            LEDonStrip=8;
            maxAmplitude = 185;
            pushToLEDStrip(inputData[counter],inputData[counter+1],inputData[counter+2],inputData[counter+3],
                    LEDonStrip,maxAmplitude,port,portNumber,strip8);
        }

		//This takes care of counters 17 to 20
        else if(counter ==17){
            port='D';
            portNumber=0;
            LEDonStrip=5;
            maxAmplitude = 115;
            pushToLEDStrip(inputData[counter],inputData[counter+1],inputData[counter+2],inputData[counter+3],
            LEDonStrip,maxAmplitude,port,portNumber,strip5);
        }
		//This takes care of counters 21 to 24
        else if(counter ==21){
            port='D';
            portNumber=1;
            LEDonStrip=4;
            maxAmplitude = 95;
            pushToLEDStrip(inputData[counter],inputData[counter+1],inputData[counter+2],inputData[counter+3],
            LEDonStrip,maxAmplitude,port,portNumber,strip4);
        }

	}
}

void fftMode(){
    		// Perform the FFT
		// Get 64 samples at 50uS intervals
		// 50uS means our sampling rate is 20KHz which gives us
		// Nyquist limit of 10Khz
		short i = 0;
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
//			realNumbers[i] = ((short)(ADRESH << 8) + (short)ADRESL) - 512;
			realNumbers[i] = ((short)(ADRESH << 8) + (short)ADRESL)-1861;
			
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
//			__delay_us(7);
		}
        
        //This is only used for debugging purposes. it is an array
        //of values that was sampled from a 100Hz sine wave....I think.
        //    int realNumbers[64]={
        //1345, 475, -1230, 1586, -766, -1224, 1623, -612,
        //-1213, 1634, -978, -462, 1642, -1204, 220, 1656,
        //-1226, 987, -938, -1229, 1468, -93, -1229, 1597,
        //193, -1226, 1626, -942, -1212, 1635, -1149, -249,
        //1642, -1208, 359, 1694, -1226, 927, -981, -1230,
        //1522, 835, -1230, 1603, -124, -1225, 1625, -563,
        //-1206, 1636, -1158, -372, 1642, -1212, 459, 1665,
        //-1226, 1084, -914, -1229, 1448, 539, -1230, 1609,
        //};
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
		
		// Note: the '6' is the size of the input data (2 to the power of 7 = 64)

 		TESTPIN_W5 = 1;
		fix_fft(realNumbers, imaginaryNumbers, 6);

//		
		// Take the absolute value of the FFT results
		
		// Note: The FFT routine returns 'complex' numbers which consist of
		// both a real and imaginary part.  To find the 'absolute' value
		// of the returned data we have to calculate the complex number's
		// distance from zero which requires a little pythagoras and therefore
		// a square-root calculation too.  Since the PIC has multiplication
		// hardware, only the square-root needs to be optimised.          
        
        long place, root;
        long res=0;
        unsigned long z;
        
        for (char k=1; k<32; k++){
            long img=((long)imaginaryNumbers[k]*(long)imaginaryNumbers[k]);
            unsigned long real= ((long)realNumbers[k]*(long)realNumbers[k]);
            z= img+real;
            long tempBit = 0x40000000;
            while (tempBit > z){
                tempBit >>=2;
            }
            
            while(tempBit){
                if(z>=res+tempBit){
                    z-=res+tempBit;
                    res=(res)+(tempBit*2);
                }
                
                res >>=1;
                
                tempBit>>=2;
            }
            magnitudeArray[k]=res;
        }
	    TESTPIN_W5 = 0;
	    
	    // Now we have 32 buckets of audio frequency data represented as
	    // linear intensity in realNumbers[]
	    //
	    // Since the maximum input value (in theory) to the SQRT function is
	    // 32767, the peak output at this stage is SQRT(32767) = 181.
	    
	    // Draw a bar graph of the FFT output data
	    TESTPIN_W6 = 1;
        writeLED(magnitudeArray);
        __delay_ms(5);
	    TESTPIN_W6 = 0;
}