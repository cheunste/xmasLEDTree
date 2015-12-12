#include <xc.h>
#include <pic18.h>
#include <stdlib.h>
#include "WS2812.h"
#include "portToggle.h"

void sendBitPA0( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATAbits.LA0 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATAbits.LA0 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATAbits.LA0 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATAbits.LA0=0;
			__delay_us(0.900);
        }
}

void sendBitPA1( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATAbits.LA1 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATAbits.LA1 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATAbits.LA1 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATAbits.LA1=0;
			__delay_us(0.900);
        }
}
void sendBitPA2( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATAbits.LA2 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATAbits.LA2 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATAbits.LA2 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATAbits.LA2=0;
			__delay_us(0.900);
        }
}
void sendBitPA3( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATAbits.LA3 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATAbits.LA3 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATAbits.LA3 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATAbits.LA3=0;
			__delay_us(0.900);
        }
}
void sendBitPA4( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATAbits.LA4 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATAbits.LA4 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATAbits.LA4 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATAbits.LA4=0;
			__delay_us(0.900);
        }
}
void sendBitPA5( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATAbits.LA5 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATAbits.LA5 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATAbits.LA5 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATAbits.LA5=0;
			__delay_us(0.900);
        }
}
void sendBitPA6( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATAbits.LA6 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATAbits.LA6 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATAbits.LA6 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATAbits.LA6=0;
			__delay_us(0.900);
        }
}
void sendBitPA7( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATAbits.LA7 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATAbits.LA7 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATAbits.LA7 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATAbits.LA7=0;
			__delay_us(0.900);
        }
}

//For Port B
void sendBitPB0( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATBbits.LB0 = 1;
            //This is where T1H is suppose to be
            __delay_us(0.9);
            LATBbits.LB0 = 0;
            __delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATBbits.LB0 = 1;
            __delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATBbits.LB0=0;
            __delay_us(0.900);
        }
}

void sendBitPB1( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATBbits.LB1 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
			LATBbits.LB1=0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATBbits.LB1 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
		   //__delay_us(0.900);
            LATBbits.LB1=0;
			__delay_us(0.900);
        }
}
void sendBitPB2( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATBbits.LB2 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATBbits.LB2 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATBbits.LB2 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATBbits.LB2=0;
			__delay_us(0.900);
        }
}
void sendBitPB3( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATBbits.LB3 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATBbits.LB3 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATBbits.LB3 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATBbits.LB3=0;
			__delay_us(0.900);
        }
}
void sendBitPB4( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATBbits.LB4 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATBbits.LB4 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATBbits.LB4 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATBbits.LB4=0;
			__delay_us(0.900);
        }
}
void sendBitPB5( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATBbits.LB5 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATBbits.LB5 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATBbits.LB5 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATBbits.LB5=0;
			__delay_us(0.900);
        }
}
void sendBitPB6( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATBbits.LB6 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATBbits.LB6 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATBbits.LB6 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATBbits.LB6=0;
			__delay_us(0.900);
        }
}
void sendBitPB7( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATBbits.LB7 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATBbits.LB7 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATBbits.LB7 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATBbits.LB7=0;
			__delay_us(0.900);
        }
}

//For Port C
void sendBitPC0( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATCbits.LC0 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATCbits.LC0 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATCbits.LC0 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATCbits.LC0=0;
			__delay_us(0.900);
        }
}

void sendBitPC1( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATCbits.LC1 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATCbits.LC1 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATCbits.LC1 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATCbits.LC1=0;
			__delay_us(0.900);
        }
}
void sendBitPC2( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATCbits.LC2 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATCbits.LC2 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATCbits.LC2 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATCbits.LC2=0;
			__delay_us(0.900);
        }
}
void sendBitPC3( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATCbits.LC3 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATCbits.LC3 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATCbits.LC3 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATCbits.LC3=0;
			__delay_us(0.900);
        }
}
void sendBitPC4( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATCbits.LC4 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATCbits.LC4 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATCbits.LC4 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATCbits.LC4=0;
			__delay_us(0.900);
        }
}
void sendBitPC5( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATCbits.LC5 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATCbits.LC5 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATCbits.LC5 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATCbits.LC5=0;
			__delay_us(0.900);
        }
}
void sendBitPC6( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATCbits.LC6 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATCbits.LC6 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATCbits.LC6 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATCbits.LC6=0;
			__delay_us(0.900);
        }
}
void sendBitPC7( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATCbits.LC7 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATCbits.LC7 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATCbits.LC7 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATCbits.LC7=0;
			__delay_us(0.900);
        }
}

//For Port D

void sendBitPD0( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATDbits.LD0 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATDbits.LD0 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATDbits.LD0 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATDbits.LD0=0;
			__delay_us(0.900);
        }
}

void sendBitPD1( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATDbits.LD1 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATDbits.LD1 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATDbits.LD1 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATDbits.LD1=0;
			__delay_us(0.900);
        }
}
void sendBitPD2( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATDbits.LD2 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATDbits.LD2 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATDbits.LD2 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATDbits.LD2=0;
			__delay_us(0.900);
        }
}
void sendBitPD3( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATDbits.LD3 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATDbits.LD3 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATDbits.LD3 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATDbits.LD3=0;
			__delay_us(0.900);
        }
}
void sendBitPD4( int bitVal){
        if (bitVal==1) {
        // if it is a 1, let it stay higher a bit longer
            LATDbits.LD4 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATDbits.LD4 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATDbits.LD4 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATDbits.LD4=0;
			__delay_us(0.900);
        }
}
void sendBitPD5( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATDbits.LD5 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATDbits.LD5 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATDbits.LD5 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATDbits.LD5=0;
			__delay_us(0.900);
        }
}
void sendBitPD6( int bitVal){
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATDbits.LD6 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATDbits.LD6 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATDbits.LD6 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATDbits.LD6=0;
			__delay_us(0.900);
        }
}
void sendBitPD7( int bitVal){
    
    
        if (bitVal == 1) {
        // if it is a 1, let it stay higher a bit longer
            LATDbits.LD7 = 1;
            //This is where T1H is suppose to be
			__delay_us(0.9);
            LATDbits.LD7 = 0;
			__delay_us(0.6);
        }
        else {
            // but a 0 should go high and then low as fast as possible
            LATDbits.LD7 = 1;
			__delay_us(0.400);
           //This is where T0H is suppose to be Oscope shows only 1 is needed.
            LATDbits.LD7=0;
			__delay_us(0.900);
        }
}

void portSwitch(int bitVal,char port, int portNumber){
    
    
//    if (port =='A'){
//           if (portNumber==0) sendBitPA0( bitVal); 
//		   else if (portNumber==1) sendBitPA1( bitVal); 
//           else if (portNumber==2) sendBitPA2( bitVal); 
//           else if (portNumber==3) sendBitPA3( bitVal); 
//           else if (portNumber==4) sendBitPA4( bitVal); 
//           else if (portNumber==5) sendBitPA5( bitVal); 
//           else if (portNumber==6) sendBitPA6( bitVal); 
//           else if (portNumber==7) sendBitPA7( bitVal); 
//           //default: sendBitPA0( bitVal); break;
//   }
    if(port=='B'){
           if(portNumber ==0) sendBitPB0( bitVal); 
           else{
               sendBitPB1(bitVal);
           }
//		   else if(portNumber ==1) sendBitPB1( bitVal); 
//           else if(portNumber ==2) sendBitPB2( bitVal); 
//           else if(portNumber ==3) sendBitPB3( bitVal); 
//           else if(portNumber ==4) sendBitPB4( bitVal); 
//           else if(portNumber ==5) sendBitPB5( bitVal); 
//           else if(portNumber ==6) sendBitPB6( bitVal); 
//           else if(portNumber ==7) sendBitPB7( bitVal); 
   }
    else if(port=='C'){
           if(portNumber ==0) sendBitPC0( bitVal); 
           else{
               sendBitPC1(bitVal);
           }
//		   else if(portNumber ==1) sendBitPC1( bitVal); 
//           else if(portNumber ==2) sendBitPC2( bitVal); 
//           else if(portNumber ==3) sendBitPC3( bitVal); 
//           else if(portNumber ==4) sendBitPC4( bitVal); 
//           else if(portNumber ==5) sendBitPC5( bitVal); 
//           else if(portNumber ==6) sendBitPC6( bitVal); 
//           else if(portNumber ==7) sendBitPC7( bitVal); 
   }
    else if(port=='D'){
           if(portNumber==0) sendBitPD0( bitVal); 
           else{
               sendBitPD1(bitVal);
           }
//		   else if(portNumber==1) sendBitPD1( bitVal); 
//           else if(portNumber==2) sendBitPD2( bitVal); 
//           else if(portNumber==3) sendBitPD3( bitVal); 
//           else if(portNumber==4) sendBitPD4( bitVal); 
//		   else if(portNumber==5) sendBitPD5( bitVal); 
//           else if(portNumber==6) sendBitPD6( bitVal); 
//           else if(portNumber==7) sendBitPD7( bitVal); 
    }
    else if (port=='X'){
           if(portNumber==4) sendBitPB4( bitVal); 
		   else if(portNumber==5) sendBitPB5( bitVal); 
//           else if(portNumber==6) sendBitPB6( bitVal); 
//           else if(portNumber==7) sendBitPB7( bitVal); 
    }    
}