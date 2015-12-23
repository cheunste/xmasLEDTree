#include "WS2812.h"
#include "pic18f46k80.h"
#include "portToggle.h"
#include "math.h"
#include <xc.h>

//Used to perform delays between LED refresh. Too short, LEDs blink
//Too long, then it would be too slow
void delayLED(){
//    for(int i=0; i<50;i++)
//        __delay_ms(1);
}

//This delay is used for animation methods. Can be as long as you want
void delayLEDLong(){
    for(int i=0; i<1000;i++)
        __delay_ms(1);
    
}
//Draw all strips at once
void drawAllStrips(){
    int LEDonStrip;
    
    GIE=0; while(GIE);
    LEDonStrip=13;
    drawLED(strip13B6,'B',0,LEDonStrip*4*3);
    drawLED(strip13B5,'B',1,LEDonStrip*4*3);
    LEDonStrip=10;
    drawLED(strip10,'C',2,LEDonStrip*4*3);
    LEDonStrip=8;
    drawLED(strip8,'C',3,LEDonStrip*4*3);
    LEDonStrip=5;
    drawLED(strip5,'D',0,LEDonStrip*4*3);
    LEDonStrip=4;
    drawLED(strip4,'D',1,LEDonStrip*4*3);
    GIE=1; while(!GIE);
        
}

//This turns the entire tree green. Used for certain animations.
void greenAllStrips(){
    //greenStrip(unsigned char ledArray[],int LEDonStrip);
    int base6Strip=13*4;
    int base5Strip=13*4;
    int base4Strip=10*4;
    int base3Strip=8*4;
    int base2Strip=5*4;
    int base1Strip=4*4;
    
    greenStrip(strip13B6,base6Strip);
    greenStrip(strip13B5,base5Strip);
    greenStrip(strip10,base4Strip);
    greenStrip(strip8,base3Strip);
    greenStrip(strip5,base2Strip);
    greenStrip(strip4,base1Strip);
    drawAllStrips();
}
//pushToLEDArray(LEDratio1,onToStripRatio1,0,secondStart,ledArray[], ledIndex);
void pushToLEDArray(int LEDonStrip,double LEDratio, double LEDonToStripRatio,
        int arrayStart, int arrayEnd,
        unsigned char ledArray[]){

	int i=0;
    int cyanUpperBorder;
    int yellowUpperBorder;
    int redEnd;
    
    //used to cast LEDratio and translate it to RGB. Couldn't do this before
    //due to LEDRatio being used for LEDonToStripRatio in an earlier funciton
    int correctedLEDRatio=((int)LEDratio)*3;
    
    //Make entire strip green. Used as a way of "clearing" the LEDs by filling it with green
//    for(i=arrayStart; i<arrayEnd;i+=3){
//        ledArray[i] =25;
//        ledArray[i+1] =0;
//        ledArray[i+2] =0;
//    }
    //Make entire strip green. Used as a way of "clearing" the LEDs by filling it with green
    //This clears an array strip in decending order from the end of a strip to the start of the strip.
    //Note that this is in reverse order, so instead of GRB, it will be BRG
    for(i=arrayEnd; i>=arrayStart;i-=3){
        ledArray[i] =100;
        ledArray[i-1] =0;
        ledArray[i-2] =0;
    }
    
	if(LEDonToStripRatio <=0.3){
		//Make make LEDs cyan
		for(i=arrayStart;i<arrayStart+correctedLEDRatio;i+=3){
			ledArray[i] =100;
			ledArray[i+1] =0;
			ledArray[i+2] =100;
		}

		//Make rest of strip green
		for(i=arrayStart+correctedLEDRatio; i<arrayEnd;i+=3){
			ledArray[i] =100;
			ledArray[i+1] =0;
			ledArray[i+2] =0;
		}
        
        delayLED();

	}
	else if (LEDonToStripRatio >0.3 && LEDonToStripRatio<0.5){

//        cyanUpperBorder=(floor(LEDonStrip/2)+arrayStart)*3;
//        yellowUpperBorder=(floor(LEDonStrip/2)+floor(LEDonStrip/4)+arrayStart+LEDratio)*3;
        cyanUpperBorder=(floor(LEDonStrip/3)*3)+arrayStart;
        yellowUpperBorder=arrayStart+correctedLEDRatio;
		//Make make LEDs cyan
		for(i=arrayStart;i<cyanUpperBorder;i+=3){
			ledArray[i] =100;
			ledArray[i+1] =0;
			ledArray[i+2] =100;
		}

		//make LEDs yellow
		for(i=cyanUpperBorder;i<yellowUpperBorder;i+=3){
			ledArray[i] =100;
			ledArray[i+1] =100;
			ledArray[i+2] =0;
		}
		//Make rest of strip green
		for(i=yellowUpperBorder; i<arrayEnd;i+=3){
			ledArray[i] =100;
			ledArray[i+1] =0;
			ledArray[i+2] =0;
		}

        delayLED();
	}
	else if(LEDonToStripRatio>=0.5){

//        cyanUpperBorder=(floor(LEDonStrip/2)+arrayStart)*3;
//        yellowUpperBorder=(floor(LEDonStrip/2)+floor(LEDonStrip/4)+arrayStart)*3;
        cyanUpperBorder=(floor(LEDonStrip/3)*3)+arrayStart;
        yellowUpperBorder=cyanUpperBorder+(floor(LEDonStrip/3)*3);
        redEnd=yellowUpperBorder+correctedLEDRatio;
		//Make make LEDs cyan
		for(i=arrayStart;i<cyanUpperBorder;i+=3){
			ledArray[i] =100;
			ledArray[i+1] = 0;
			ledArray[i+2] =100;
		}
		//make LEDs yellow
		for(i=cyanUpperBorder;i<yellowUpperBorder;i+=3){
			ledArray[i] =100;
			ledArray[i+1] =100;
			ledArray[i+2] =0;
		}
		//Make make LEDs red
		for(i=yellowUpperBorder;i<redEnd;i+=3){
			ledArray[i] =0;
			ledArray[i+1] =100;
			ledArray[i+2] =0;
		}

        //Make rest green, if applicable
		for(i=redEnd;i<arrayEnd;i+=3){
			ledArray[i] =100;
			ledArray[i+1] = 0;
			ledArray[i+2] = 0;
		}
        
        delayLED();
	}
    else{
        //Nothing to do here
        
    }

}
void pushToLEDStrip(long input1,long input2,long input3,long input4,
        int LEDonStrip,double maxAmplitude,
        unsigned char ledArray[]){

	//This is the maxAmplitude gotten after taking abolute value of FFT. This is only gotten from experimental
	//results of looking at the aboluste value of fft at various frequencies. Really should be a parameter

	//These are ratios for each of the inputs compared to max Amplitude.
    //This determines how many LEDs are going to be on. 
	double LEDratio1=ceil((((double)input1)/maxAmplitude)*LEDonStrip);
	double LEDratio2=ceil((((double)input2)/maxAmplitude)*LEDonStrip);
	double LEDratio3=ceil((((double)input3)/maxAmplitude)*LEDonStrip);
	double LEDratio4=ceil((((double)input4)/maxAmplitude)*LEDonStrip);

	//Actual ratio of LED on to LED total on strip
	double onToStripRatio1=LEDratio1/LEDonStrip;
	double onToStripRatio2=LEDratio2/LEDonStrip;
	double onToStripRatio3=LEDratio3/LEDonStrip;
	double onToStripRatio4=LEDratio4/LEDonStrip;
    
	//These variables are used to keep track of when the next strip Starts
	int secondStart = (LEDonStrip*3);
	int thirdStart = (LEDonStrip*3*2);
	int fourthStart = (LEDonStrip*3*3);
	int fourthEnd=(LEDonStrip*3*4);
	//vars used for counting
	int i =0;
	int j=0;
    
    //Format
    //void pushToLEDArray(int LEDonStrip,int LEDratio, double LEDonToStripRatio,
//        int arrayStart, int arrayEnd,
//        unsigned char ledArray[],int ledIndex) 
    
	//Push data for the first strip to the array
	pushToLEDArray(LEDonStrip,LEDratio1,onToStripRatio1,
            0,secondStart,
            ledArray);
    
    //Push data for the  second strip to the array
	pushToLEDArray(LEDonStrip,LEDratio2,onToStripRatio2,
            secondStart,thirdStart,
            ledArray);
    
    //Push data for the third strip to the array
	pushToLEDArray(LEDonStrip,LEDratio3,onToStripRatio3,
            thirdStart,fourthStart,
            ledArray);
    
    //Push data for the  fourth  strip to the array
	pushToLEDArray(LEDonStrip,LEDratio4,onToStripRatio4,
            fourthStart,fourthEnd,
            ledArray);

}


//Force ledArray to be all greens. Used often since this is a LED Tree
void greenStrip(unsigned char ledArray[],int LEDonStrip){
    for (int i=0; i<LEDonStrip; i+=3)
    {
        ledArray[i] =100;
        ledArray[i+1] =0;
        ledArray[i+2] =0;
    }    
}

//SImilar to Greenstrip only with a dimmer green. Used for debugging
void dimmerGreenStrip(unsigned char ledArray[],int LEDonStrip){
    for (int i=0; i<LEDonStrip; i+=3)
    {
        ledArray[i] =25;
        ledArray[i+1] =0;
        ledArray[i+2] =0;
    }    
}

void clearStrip(unsigned char ledArray[],int LEDonStrip)
{
    for (int i=0; i<LEDonStrip*3; i+=3)
    {
        ledArray[i] =0;
        ledArray[i+1] =0;
        ledArray[i+2] =0;
    }

}

//Clears all LEDs on the entire tree
void clearAllLEDs(){
    
    int LEDonStrip;
    //Base 6 and Base 5
    LEDonStrip=13;
    clearStrip(strip13B6,13*4);
    clearStrip(strip13B5,13*4);

    //Base 4
    LEDonStrip=10;
    clearStrip(strip10,10*4);

    //Base 3
    LEDonStrip=8;
    clearStrip(strip8,8*4);

    //Base 2
    LEDonStrip=5;
    clearStrip(strip5,5*4);
    
    //Base 1
    LEDonStrip=4;
    clearStrip(strip4,4*4);
    
    drawAllStrips();
    delayLEDLong(); 
}

void drawLED (unsigned char ledArray[],char port, int portNumber,int LEDonStrip)
{
   //Remember, the LED are being pushed to the strip in a FIFO order
    
    for (unsigned int i = 0; i <LEDonStrip; i+=3)
    {    
        sendByte(ledArray[i],port,portNumber);
//           __delay_us( (RES / 1000UL)+1);
//        __delay_us(0.5);
        sendByte(ledArray[i+1],port,portNumber);
//           __delay_us( (RES / 1000UL)+1);
//        __delay_us(0.5);
        sendByte(ledArray[i+2],port,portNumber);      
//           __delay_us( (RES / 1000UL)+1);
//        __delay_us(0.5);
    }
//    __delay_us(0.5);
   __delay_us( (RES / 1000UL)+1);

}

//This function does a bitwise AND with the 7th most bit and toggles a pin
// on a port based on port parameters 
void sendByte( unsigned char byte ,char port,int portNumber ) {
    

    for( unsigned char i= 0 ; i < 8 ; i++ ) {
        //Perform a logical and with the 7th bit. This is because the ws2812 reads in the 
        //most significant bit first, which is the 7th bit (or 128 in decimal)
        
        //This is also right shifted by 7 since doing a X & 0b10000000 gives 0b10000000
        //So right shift by 7 gives you a 1, which is needed in the protSwitch function.
        unsigned char bitSend = ((byte) & (unsigned char)128)>>7;
        portSwitch(bitSend,port,portNumber);
        
        // so send highest bit (bit #7 in an 8-bit byte since they start at 0)
        // and then shift left so bit 6 moves into 7, 5 moves into 6, etc
        byte <<= 1;   
    }
} 
