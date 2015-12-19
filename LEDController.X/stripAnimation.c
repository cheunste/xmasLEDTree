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
int minColorChoices =7;

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
        case 6:
            ledArray[arrayPosition]=191;
            ledArray[arrayPosition]=0;
            ledArray[arrayPosition]=255;
            break;
        //Crimson red
        case 7:
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
        colorSelection(strip13, randomNumber,i);
    }
    GIE=0; while(GIE);
    drawLED(strip13,'B',0,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    
    //For base 5
    LEDonStrip=13;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        randomNumber=floor(rand() / (RAND_MAX / (maxColorChoices+ 1) + 1));
        colorSelection(strip13, randomNumber,i);
    }
    GIE=0; while(GIE);
    drawLED(strip13,'B',1,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();        
    
    //For Base 4
    LEDonStrip=10;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        randomNumber=floor(rand() / (RAND_MAX / (maxColorChoices+ 1) + 1));
        colorSelection(strip10, randomNumber,i);
    }
    GIE=0; while(GIE);
    drawLED(strip10,'C',2,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    
    //For Base 3
    LEDonStrip=8;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        randomNumber=floor(rand() / (RAND_MAX / (maxColorChoices+ 1) + 1));
        colorSelection(strip8, randomNumber,i);
    }
    GIE=0; while(GIE);
    drawLED(strip8,'C',3,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    
    //For Base 2
    LEDonStrip=5;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        randomNumber=floor(rand() / (RAND_MAX / (maxColorChoices+ 1) + 1));
        colorSelection(strip5, randomNumber,i);
    }
    GIE=0; while(GIE);
    drawLED(strip5,'D',0,LEDonStrip*4*3);
    GIE=1; while(!GIE);    
    delayLEDLong();
    
    //For Base 1
    LEDonStrip=4;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        randomNumber=floor(rand() / (RAND_MAX / (maxColorChoices+ 1) + 1));
        colorSelection(strip4, randomNumber,i);
    }
    GIE=0; while(GIE);
    drawLED(strip4,'D',1,LEDonStrip*4*3);
    GIE=1; while(!GIE);    
    delayLEDLong();
}

//This is a method used to set up LED array for the bounce method.
void bouncePrep(unsigned char ledArray[],
        int arrayStart, int arrayEnd, int bounceColor, int LEDonStrip){
    
}
//Send a colored LED from the start of a strip to the end of a strip and 
//bounce back to the start of the strip.
void bounce(){
    int LEDonStrip;
    int i;
    int randomNumber;
    int base6Tracker;
    int base5Tracker;
    int base4Tracker;
    int base3Tracker;
    int base2Tracker;
    int base1Tracker;
    
    //These random numbers uses 8 because I do not want a case where
    //it uses green.
    randomNumber=floor(rand() / (RAND_MAX / (8+ 1) + 1));
    LEDonStrip=13;
    
    while(base6Tracker<LEDonStrip*3){
        if(base6Tracker>LEDonStrip*3){
            
        }
        base6Tracker+=3;
    }
    
    greenStrip(strip13,LEDonStrip*3);
//    greenStrip(strip10,);
    while(base6Tracker<LEDonStrip*3){
        colorSelection(strip13, 0,base6Tracker);
        colorSelection(strip13, 0,base6Tracker+(baseLevel6LED*3));
        colorSelection(strip13, 3,base6Tracker+(baseLevel6LED*3*2));
        colorSelection(strip13, 2,base6Tracker+(baseLevel6LED*3*3));
        base6Tracker+=3;
        GIE=0; while(GIE);
        drawLED(strip13,'B',0,LEDonStrip*4*3);
        for(i=0; i<150; i++)
            __delay_ms(1);
        GIE=1; while(!GIE);
        greenStrip(strip13,LEDonStrip*3*4);
    }
    GIE=0; while(GIE);
    drawLED(strip13,'B',0,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    
}

void ring(){
    int LEDonStrip;
    int i;
    int tracker=0;
    int randomNumber;
    //base 6
    //These random numbers uses 8 because I do not want a case where
    //it uses green.
    randomNumber=floor(rand() / (RAND_MAX / (8+ 1) + 1));
    LEDonStrip=13;
    greenStrip(strip13,LEDonStrip*3);
    while(tracker<LEDonStrip*3){
        colorSelection(strip13, randomNumber,tracker);
        colorSelection(strip13, randomNumber,tracker+(LEDonStrip*3));
        colorSelection(strip13, randomNumber,tracker+(LEDonStrip*3*2));
        colorSelection(strip13, randomNumber,tracker+(LEDonStrip*3*3));
        tracker+=3;
        GIE=0; while(GIE);
        drawLED(strip13,'B',0,LEDonStrip*4*3);
        for(i=0; i<150; i++)
            __delay_ms(1);
        GIE=1; while(!GIE);
//        greenStrip(strip13,LEDonStrip*3*4);
    }
    greenStrip(strip13,LEDonStrip*3*4);
    GIE=0; while(GIE);
    drawLED(strip13,'B',0,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    
    //base 5
    randomNumber=floor(rand() / (RAND_MAX / (8+ 1) + 1));
    LEDonStrip=13;
    greenStrip(strip13,LEDonStrip*3);
    tracker=0;
    while(tracker<LEDonStrip*3){
        colorSelection(strip13, randomNumber,tracker);
        colorSelection(strip13, randomNumber,tracker+(LEDonStrip*3));
        colorSelection(strip13, randomNumber,tracker+(LEDonStrip*3*2));
        colorSelection(strip13, randomNumber,tracker+(LEDonStrip*3*3));
        tracker+=3;
        GIE=0; while(GIE);
        drawLED(strip13,'B',1,LEDonStrip*4*3);
        for(i=0; i<150; i++)
            __delay_ms(1);
        GIE=1; while(!GIE);
//        greenStrip(strip13,LEDonStrip*3*4);
    }
    greenStrip(strip13,LEDonStrip*3*4);
    GIE=0; while(GIE);
    drawLED(strip13,'B',1,LEDonStrip*4*3);
    GIE=1; while(!GIE);  
    
    //base 4
    randomNumber=floor(rand() / (RAND_MAX / (8+ 1) + 1));
    LEDonStrip=10;
    greenStrip(strip10,LEDonStrip*3);
    tracker=0;
    while(tracker<LEDonStrip*3){
        colorSelection(strip10, randomNumber,tracker);
        colorSelection(strip10, randomNumber,tracker+(LEDonStrip*3));
        colorSelection(strip10, randomNumber,tracker+(LEDonStrip*3*2));
        colorSelection(strip10, randomNumber,tracker+(LEDonStrip*3*3));
        tracker+=3;
        GIE=0; while(GIE);
        drawLED(strip10,'C',2,LEDonStrip*4*3);
        for(i=0; i<150; i++)
            __delay_ms(1);
        GIE=1; while(!GIE);
//        greenStrip(strip10,LEDonStrip*3*4);
    }
    greenStrip(strip10,LEDonStrip*3*4);
    GIE=0; while(GIE);
    drawLED(strip10,'C',2,LEDonStrip*4*3);
    GIE=1; while(!GIE);    
    
    //base 3
    randomNumber=floor(rand() / (RAND_MAX / (8+ 1) + 1));
    LEDonStrip=8;
    greenStrip(strip8,LEDonStrip*3);
    tracker=0;
    while(tracker<LEDonStrip*3){
        colorSelection(strip8, randomNumber,tracker);
        colorSelection(strip8, randomNumber,tracker+(LEDonStrip*3));
        colorSelection(strip8, randomNumber,tracker+(LEDonStrip*3*2));
        colorSelection(strip8, randomNumber,tracker+(LEDonStrip*3*3));
        tracker+=3;
        GIE=0; while(GIE);
        drawLED(strip8,'C',3,LEDonStrip*4*3);
        for(i=0; i<150; i++)
            __delay_ms(1);
        GIE=1; while(!GIE);
//        greenStrip(strip8,LEDonStrip*3*4);
    }
    greenStrip(strip8,LEDonStrip*3*4);
    GIE=0; while(GIE);
    drawLED(strip8,'C',3,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    
    //base 2
    randomNumber=floor(rand() / (RAND_MAX / (8+ 1) + 1));
    LEDonStrip=5;
    greenStrip(strip5,LEDonStrip*3);
    tracker=0;
    while(tracker<LEDonStrip*3){
        colorSelection(strip5, randomNumber,tracker);
        colorSelection(strip5, randomNumber,tracker+(LEDonStrip*3));
        colorSelection(strip5, randomNumber,tracker+(LEDonStrip*3*2));
        colorSelection(strip5, randomNumber,tracker+(LEDonStrip*3*3));
        tracker+=3;
        GIE=0; while(GIE);
        drawLED(strip5,'D',0,LEDonStrip*4*3);
        for(i=0; i<150; i++)
            __delay_ms(1);
        GIE=1; while(!GIE);
//        greenStrip(strip5,LEDonStrip*3*4);
    }
    greenStrip(strip5,LEDonStrip*3*4);
    GIE=0; while(GIE);
    drawLED(strip5,'D',0,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    
    //base 1
    randomNumber=floor(rand() / (RAND_MAX / (8+ 1) + 1));
    LEDonStrip=4;
    greenStrip(strip4,LEDonStrip*3);
    tracker=0;
    while(tracker<LEDonStrip*3){
        colorSelection(strip4, randomNumber,tracker);
        colorSelection(strip4, randomNumber,tracker+(LEDonStrip*3));
        colorSelection(strip4, randomNumber,tracker+(LEDonStrip*3*2));
        colorSelection(strip4, randomNumber,tracker+(LEDonStrip*3*3));
        tracker+=3;
        GIE=0; while(GIE);
        drawLED(strip4,'D',1,LEDonStrip*4*3);
        for(i=0; i<150; i++)
            __delay_ms(1);
        GIE=1; while(!GIE);
//        greenStrip(strip4,LEDonStrip*3*4);
    }
    greenStrip(strip4,LEDonStrip*3*4);
    GIE=0; while(GIE);
    drawLED(strip4,'D',1,LEDonStrip*4*3);
    GIE=1; while(!GIE);    
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
        colorSelection(strip13, alt1,i);
    }
    GIE=0; while(GIE);
    drawLED(strip13,'B',0,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    
    //For base 5
    LEDonStrip=13;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        colorSelection(strip13, alt2,i);
    }
    GIE=0; while(GIE);
    drawLED(strip13,'B',1,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    //For Base 4
    LEDonStrip=10;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        colorSelection(strip10, alt1,i);
    }
    GIE=0; while(GIE);
    drawLED(strip10,'C',2,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    
    //For Base 3
    LEDonStrip=8;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        colorSelection(strip8, alt2,i);
    }    
    GIE=0; while(GIE);
    drawLED(strip8,'C',3,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    
    //For Base 2
    LEDonStrip=5;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        colorSelection(strip5, alt1,i);
    }
    GIE=0; while(GIE);
    drawLED(strip5,'D',0,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    
    //For Base 1
    LEDonStrip=4;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        colorSelection(strip4, alt2,i);
    }    
    GIE=0; while(GIE);
    drawLED(strip4,'D',1,LEDonStrip*4*3);
    GIE=1; while(!GIE);
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
        if(i<LEDonStrip) colorSelection(strip13, alt1,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip13, alt2,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip13, alt3,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip13, alt4,i);
    }
    GIE=0; while(GIE);
    drawLED(strip13,'B',0,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    
    //For base 5
    LEDonStrip=13;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        if(i<LEDonStrip) colorSelection(strip13, alt2,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip13, alt3,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip13, alt4,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip13, alt1,i);
    }
    GIE=0; while(GIE);
    drawLED(strip13,'B',1,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    //For Base 4
    LEDonStrip=10;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        if(i<LEDonStrip) colorSelection(strip10, alt1,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip10, alt2,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip10, alt3,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip10, alt4,i);
    }
    GIE=0; while(GIE);
    drawLED(strip10,'C',2,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    
    //For Base 3
    LEDonStrip=8;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        if(i<LEDonStrip) colorSelection(strip8, alt2,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip8, alt3,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip8, alt4,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip8, alt1,i);
    }    
    GIE=0; while(GIE);
    drawLED(strip8,'C',3,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    
    //For Base 2
    LEDonStrip=5;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        if(i<LEDonStrip) colorSelection(strip5, alt1,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip5, alt2,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip5, alt3,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip5, alt4,i);
    }
    GIE=0; while(GIE);
    drawLED(strip5,'D',0,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();
    
    //For Base 1
    LEDonStrip=4;
    for(i=0; i<LEDonStrip*4*3;i+=3){
        if(i<LEDonStrip) colorSelection(strip4, alt2,i);
        else if(i>=LEDonStrip && i<LEDonStrip*2)colorSelection(strip4, alt3,i);
        else if(i>=LEDonStrip*2 && i<LEDonStrip*3)colorSelection(strip4, alt4,i);
        else if(i>=LEDonStrip*3 && i<LEDonStrip*4)colorSelection(strip4, alt1,i);
    }    
    GIE=0; while(GIE);
    drawLED(strip4,'D',1,LEDonStrip*4*3);
    GIE=1; while(!GIE);
    delayLEDLong();    
}