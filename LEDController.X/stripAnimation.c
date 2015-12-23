/* 
 * File:   stripAnimation.c
 *
 * Created on November 5, 2015, 11:03 AM
 * 
 * The methods in this file is only used to create animations or static LED
 * arrangements for the entire tree
 * (ring animation, random sparkle animation, etc)
 * 
 * Some animations are based off of
 * https://gist.github.com/hsiboy/f9ef711418b40e259b06
 */

#include <stdio.h>
#include <stdlib.h>
#include "WS2812.h"
#include "pic18f46k80.h"
#include "portToggle.h"
#include "math.h"
#include <xc.h>

#define baseLevel6LED 13
#define baseLevel5LED 13
#define baseLevel4LED 10
#define baseLevel3LED 8
#define baseLevel2LED 5
#define baseLevel1LED 4
//maxColorChoices should be the same number as the number of case statements
//in the colorSelection method.
//However, you can increase it if you want more ratio of green in the LED strips
int maxColorChoices = 20;
int minColorChoices =6;
/*
 * This method selects a color based on the input sets it based on position of the ledArray
 * These technically isn't random, but a limited color assortment that are pleasent
 * WARNING: arrayPosition needs to be a multiple of 3
 * 
 */
void colorSelection(unsigned char ledArray[], int randomNumber, int arrayPosition){
    //Note that the order is
    //Green, Red, Blue
    switch(randomNumber){
        //Orange
        case 0:
            ledArray[arrayPosition]=165;
            ledArray[arrayPosition+1]=255;
            ledArray[arrayPosition+2]=0;
            break;
        //Red
        case 1:
            ledArray[arrayPosition]=0;
            ledArray[arrayPosition+1]=100;
            ledArray[arrayPosition+2]=0;
            break;
        //Blue
        case 2:
            ledArray[arrayPosition]=0;
            ledArray[arrayPosition+1]=0;
            ledArray[arrayPosition+2]=100;
            break;
        //Cyan
        case 3:
            ledArray[arrayPosition]=100;
            ledArray[arrayPosition+1]=0;
            ledArray[arrayPosition+2]=100;
            break;
            
        //Yellow
        case 4:
            ledArray[arrayPosition]=100;
            ledArray[arrayPosition+1]=100;
            ledArray[arrayPosition+2]=0;
            break;
        //Dark Magenta
//        case 5:
//            ledArray[arrayPosition]=0;
//            ledArray[arrayPosition+1]=140;
//            ledArray[arrayPosition+2]=140;
//            break;
        
        //Sky Blue
        case 5:
            ledArray[arrayPosition]=191;
            ledArray[arrayPosition]=0;
            ledArray[arrayPosition]=255;
            break;
        //Crimson red
        case 6:
            ledArray[arrayPosition]=20;
            ledArray[arrayPosition]=220;
            ledArray[arrayPosition]=60;
            break;           
        //White
//        case 8:
//            ledArray[arrayPosition]=100;
//            ledArray[arrayPosition]=100;
//            ledArray[arrayPosition]=100;
//            break;
        //If no colors match previous cases, make it green
        //Green
        default:
            ledArray[arrayPosition]=100;
            ledArray[arrayPosition+1]=0;
            ledArray[arrayPosition+2]=0;
            break;
    }
    
}
/*
 * This method randomly selects LED on a strip and lights them up with different
 * Colors (colors limited to what the dictionary have in stored)
 * 
 */
void randomLight(){
    int LEDonStrip;
    int i;
    int randomNumber;
    //For Base 6
    LEDonStrip=13;
//    for(i=0; i<LEDonStrip*4*3;i+=3){
//        strip13[i] =100;
//        strip13[i-1] =0;
//        strip13[i-2] =0;
//    }
//    GIE=0; while(GIE);
//    drawLED(strip13,'B',0,LEDonStrip*4*3);
//    GIE=1; while(!GIE);
//    delayLEDLong();
    
    for(i=0; i<LEDonStrip*4*3;i+=3){
        randomNumber=floor(rand() / (RAND_MAX / (maxColorChoices+ 1) + 1));
        colorSelection(strip13B6, randomNumber,i);
    }
    
    //For base 5
    LEDonStrip=13;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        randomNumber=floor(rand() / (RAND_MAX / (maxColorChoices+ 1) + 1));
        colorSelection(strip13B5, randomNumber,i);
    }
    
    //For Base 4
    LEDonStrip=10;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        randomNumber=floor(rand() / (RAND_MAX / (maxColorChoices+ 1) + 1));
        colorSelection(strip10, randomNumber,i);
    }
    
    //For Base 3
    LEDonStrip=8;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        randomNumber=floor(rand() / (RAND_MAX / (maxColorChoices+ 1) + 1));
        colorSelection(strip8, randomNumber,i);
    }
    
    
    //For Base 2
    LEDonStrip=5;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        randomNumber=floor(rand() / (RAND_MAX / (maxColorChoices+ 1) + 1));
        colorSelection(strip5, randomNumber,i);
    }
    
    //For Base 1
    LEDonStrip=4;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        randomNumber=floor(rand() / (RAND_MAX / (maxColorChoices+ 1) + 1));
        colorSelection(strip4, randomNumber,i);
    }

    drawAllStrips();
//    delayLEDLong();
}

//This is a method used to set up LED array for the bounce method.
void bouncePrep(unsigned char ledArray[],
        int arrayStart, int arrayEnd, int bounceColor, int LEDonStrip){
    
}
//Send a colored LED from the start of a strip to the end of a strip and 
//bounce back to the start of the strip.
//Thjs animation is where the LEDs turn a different color from the center out to the edge
//It starts from the verj top of the tree and cascades to the bottom
bounce(){
	int LEDonStrip;
    int randomNumber;
	
    //These random numbers uses 8 because I do not want a case where
    //jt uses green.
    randomNumber=floor(rand() / (RAND_MAX / (minColorChoices+ 1) + 1));

	greenAllStrips();


	for( int i=0; i < 100*3; i+=3){

		int bounce = abs(((i+baseLevel1LED)%(baseLevel1LED*2))-baseLevel1LED);
		
		for (int j=0; j <6; j++){
			greenAllStrips();

			//ljght up base 1
			colorSelection(strip4, randomNumber,bounce);
			colorSelection(strip4, randomNumber,bounce+(baseLevel1LED*3));
			colorSelection(strip4, randomNumber,bounce+(baseLevel1LED*3*2));
			colorSelection(strip4, randomNumber,bounce+(baseLevel1LED*3*3));

			//base 2
			bounce = abs(((i+baseLevel2LED)%(baseLevel2LED*2))-baseLevel2LED);
			colorSelection(strip5, randomNumber,bounce);
			colorSelection(strip5, randomNumber,bounce+(baseLevel2LED*3));
			colorSelection(strip5, randomNumber,bounce+(baseLevel2LED*3*2));
			colorSelection(strip5, randomNumber,bounce+(baseLevel2LED*3*3));

			//base 3
			bounce = abs(((i+baseLevel3LED)%(baseLevel3LED*2))-baseLevel3LED);
			colorSelection(strip8, randomNumber,bounce);
			colorSelection(strip8, randomNumber,bounce+(baseLevel3LED*3));
			colorSelection(strip8, randomNumber,bounce+(baseLevel3LED*3*2));
			colorSelection(strip8, randomNumber,bounce+(baseLevel3LED*3*3));

			//base 4
			bounce = abs(((i+baseLevel4LED)%(baseLevel4LED*2))-baseLevel4LED);
			colorSelection(strip10, randomNumber,bounce);
			colorSelection(strip10, randomNumber,bounce+(baseLevel4LED*3));
			colorSelection(strip10, randomNumber,bounce+(baseLevel4LED*3*2));
			colorSelection(strip10, randomNumber,bounce+(baseLevel4LED*3*3));

			//base 5
			bounce = abs(((i+baseLevel5LED)%(baseLevel5LED*2))-baseLevel5LED);
			colorSelection(strip13B5, randomNumber,bounce);
			colorSelection(strip13B5, randomNumber,bounce+(baseLevel5LED*3));
			colorSelection(strip13B5, randomNumber,bounce+(baseLevel5LED*3*2));
			colorSelection(strip13B5, randomNumber,bounce+(baseLevel5LED*3*3));
	
			//base 6
			bounce = abs(((i+baseLevel6LED)%(baseLevel6LED*2))-baseLevel6LED);
			colorSelection(strip13B6, randomNumber,bounce);
			colorSelection(strip13B6, randomNumber,bounce+(baseLevel6LED*3));
			colorSelection(strip13B6, randomNumber,bounce+(baseLevel6LED*3*2));
			colorSelection(strip13B6, randomNumber,bounce+(baseLevel6LED*3*3));
	
			//draw all LEDs
			drawAllStrips();
//            delayLEDLong();
		}
	}
}

//Thjs animation is where the LEDs turn a different color from the center out to the edge
//It starts from the verj top of the tree and cascades to the bottom
ring(){
	int LEDonStrip;
    int randomNumber;
	
    //These random numbers uses 8 because I do not want a case where
    //jt uses green.
    randomNumber=floor(rand() / (RAND_MAX / (minColorChoices+ 1) + 1));

	greenAllStrips();

	for( int i=0; i < 13*3; i+=3){
	
		for (int j=0; j <6; j++){
			if(i <=10*3){
				if(i<=8*3){
					if(i<=5*3){
						if(i<=4*3){
							//ljght up base 1
							colorSelection(strip4, randomNumber,i);
							colorSelection(strip4, randomNumber,i+(baseLevel1LED*3));
							colorSelection(strip4, randomNumber,i+(baseLevel1LED*3*2));
							colorSelection(strip4, randomNumber,i+(baseLevel1LED*3*3));

						}
						//base 2
						colorSelection(strip5, randomNumber,i);
						colorSelection(strip5, randomNumber,i+(baseLevel2LED*3));
						colorSelection(strip5, randomNumber,i+(baseLevel2LED*3*2));
						colorSelection(strip5, randomNumber,i+(baseLevel2LED*3*3));

					}
					//base 3
					colorSelection(strip8, randomNumber,i);
					colorSelection(strip8, randomNumber,i+(baseLevel3LED*3));
					colorSelection(strip8, randomNumber,i+(baseLevel3LED*3*2));
					colorSelection(strip8, randomNumber,i+(baseLevel3LED*3*3));

				}
				//base 4
				colorSelection(strip10, randomNumber,i);
				colorSelection(strip10, randomNumber,i+(baseLevel4LED*3));
				colorSelection(strip10, randomNumber,i+(baseLevel4LED*3*2));
				colorSelection(strip10, randomNumber,i+(baseLevel4LED*3*3));

			}

			//base 
			colorSelection(strip13B5, randomNumber,i);
			colorSelection(strip13B5, randomNumber,i+(baseLevel5LED*3));
			colorSelection(strip13B5, randomNumber,i+(baseLevel5LED*3*2));
			colorSelection(strip13B5, randomNumber,i+(baseLevel5LED*3*3));
	
			//base 6
			colorSelection(strip13B6, randomNumber,i);
			colorSelection(strip13B6, randomNumber,i+(baseLevel6LED*3));
			colorSelection(strip13B6, randomNumber,i+(baseLevel6LED*3*2));
			colorSelection(strip13B6, randomNumber,i+(baseLevel6LED*3*3));
	
			//draw all LEDs
			drawAllStrips();
		}
	}
}
/*
 * redGreenLevels is a static LED arrangment that
 * sets the bottom most level to be either green or red and then alternates for
 * each level upward  
 */

void redGreenLevels(){
    int LEDonStrip;
    int i;
    int randomNumber;
    
    //alt1 and alt2 are local variables used assign either Red or Green based on
    //a random number
    //alt1 is used for Base 6, 4, 2 and alt2 is used for base 5,3,1
    int alt1;
    int alt2;
    
    //Red = 1 comes from the colorSelection function. 1 is the case number for red
    int RED =1; 
    
    //Anything else that ISN'T in the maxColorChoices is green, so maxColorChoices +1
    //should always give me green
    
    int GREEN = maxColorChoices +1;
    
    //Randomly generate a 0 or a 1 (by bitwise ANDing to see if something is odd or even)
    randomNumber = rand() & 1;
    if (randomNumber ==1){
        alt1=GREEN;
        alt2=RED;
    }
    else{
        alt1=RED;
        alt2=GREEN;
        
    }
    
    //For Base 6
    LEDonStrip=13;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        colorSelection(strip13B6, alt1,i);
    }
        
    //For base 5
    LEDonStrip=13;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        colorSelection(strip13B5, alt2,i);
    }
        //For Base 4
    LEDonStrip=10;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        colorSelection(strip10, alt1,i);
    }
        
    //For Base 3
    LEDonStrip=8;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        colorSelection(strip8, alt2,i);
    }    
        
    //For Base 2
    LEDonStrip=5;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        colorSelection(strip5, alt1,i);
    }
        
    //For Base 1
    LEDonStrip=4;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        colorSelection(strip4, alt2,i);
    }    
    
	drawAllStrips();
    delayLEDLong();
}

/*
 * redGreenStrips is a static LED arrangement where each strip on a base
 * alternates between red and green
 * 
 */ 
void redGreenStrips(){
    int LEDonStrip;
    int i;
    int randomNumber;
    
    //alt1 and alt2 are local variables used assign either Red or Green based on
    //a random number
    //alt1 is used for Base 6, 4, 2 and alt2 is used for base 5,3,1
    int alt1;
    int alt2;
    int alt3;
    int alt4;
    //Red = 1 comes from the colorSelection function. 1 is the case number for red
    int RED =1; 
    
    //Anything else that ISN'T in the maxColorChoices is green, so maxColorChoices +1
    //should always give me green
    
    int GREEN = maxColorChoices +1;
    
    //Randomly generate a 0 or a 1 (by bitwise ANDing to see if something is odd or even)
    randomNumber = rand() & 1;
    if (randomNumber ==1){
        alt1=GREEN;
        alt2=RED;
        alt3=GREEN;
        alt4=RED;
    }
    else{
        alt1=RED;
        alt2=GREEN;
        alt3=RED;
        alt4=GREEN;
    }
    
    //For Base 6
    LEDonStrip=13;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        if(i<LEDonStrip) colorSelection(strip13B6, alt1,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip13B6, alt2,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip13B6, alt3,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip13B6, alt4,i);
    }
    
    //For base 5
    LEDonStrip=13;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        if(i<LEDonStrip) colorSelection(strip13B5, alt2,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip13B5, alt3,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip13B5, alt4,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip13B5, alt1,i);
    }
    //For Base 4
    LEDonStrip=10;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        if(i<LEDonStrip) colorSelection(strip10, alt1,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip10, alt2,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip10, alt3,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip10, alt4,i);
    }
    
    //For Base 3
    LEDonStrip=8;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        if(i<LEDonStrip) colorSelection(strip8, alt2,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip8, alt3,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip8, alt4,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip8, alt1,i);
    }    
    //For Base 2
    LEDonStrip=5;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        if(i<LEDonStrip) colorSelection(strip5, alt1,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip5, alt2,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip5, alt3,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip5, alt4,i);
    }
    
    //For Base 1
    LEDonStrip=4;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        if(i<LEDonStrip) colorSelection(strip4, alt2,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip4, alt3,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip4, alt4,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip4, alt1,i);
    }    

	drawAllStrips();
    delayLEDLong();
}