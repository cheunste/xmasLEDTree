/* 
 * File:   WS2812.h
 * Author: Gary
 *
 * Created on 06 July 2014, 16:11
 */

#ifndef WS2812_H
#define	WS2812_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _XTAL_FREQ 80000000

#define RES 6000
    
//NOTE: bases with 10 or 13 LEDs need to be tired all in one at once
//13LEDs, for Base 6
unsigned char strip13B6[156]@0xDE0;
//13LEDs, for Base 5 
unsigned char strip13B5[156]@0x0d44;
//10 LED
unsigned char strip10[120]@0x0ccc;
//8 lED
unsigned char strip8[96]@0x0c6c;
//5LED
unsigned char strip5[60]@0x0c30;

//4*3=12
unsigned char strip4[48]@0x0c00;

// set the colour of a single led.
// color 0 = red,
//      85 = green
//     170 = blue
//      255 = red again

void pushToLEDArray(int stripLength,double LEDratio, double LEDonToStripRatio,int arrayStart, int arrayEnd,unsigned char ledArray[]);
void pushToLEDStrip(long input1,long input2,long input3,long input4,int LEDonStrip,double maxAmplitude,char port,int portNumber,unsigned char ledArray[]);
void SetColor(unsigned char, unsigned char);

void SetAllColor(unsigned char);
void greenStrip(unsigned char ledArray[],int LEDonStrip);
void dimmerGreenStrip(unsigned char ledArray[],int LEDonStrip);
void clearStrip(unsigned char ledData[],int LEDonStrip);
void spectrumLight(int LEDonStrip, int LEDLightup,char port,int portNumber, unsigned char ledArray[]);
void drawLED (unsigned char ledData[],char port, int portNumber,int LEDonStrip);
void sendByte( unsigned char ,char port,int portNumber );
void drawAllStrips();
#ifdef	__cplusplus
}
#endif

#endif	/* WS2812_H */

