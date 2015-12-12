/* 
 * File:   portToggle.h
 * Author: work
 *
 * Created on October 7, 2015, 3:59 PM
 */

#ifndef PORTTOGGLE_H
#define	PORTTOGGLE_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif
void portSwitch(int bitVal,char port, int portNumber);

void sendBitPA0(int bitVal);
void sendBitPA1(int bitVal);
void sendBitPA2(int bitVal);
void sendBitPA3(int bitVal);
void sendBitPA4(int bitVal);
void sendBitPA5(int bitVal);
void sendBitPA6(int bitVal);
void sendBitPA7(int bitVal);

void sendBitPB0 (int bitVal);
void sendBitPB1(int bitVal);
void sendBitPB2(int bitVal);
void sendBitPB3(int bitVal);
void sendBitPB4(int bitVal);
void sendBitPB5(int bitVal);
void sendBitPB6(int bitVal);
void sendBitPB7(int bitVal);

void sendBitPC0 (int bitVal);
void sendBitPC1(int bitVal);
void sendBitPC2(int bitVal);
void sendBitPC3(int bitVal);
void sendBitPC4(int bitVal);
void sendBitPC5(int bitVal);
void sendBitPC6(int bitVal);
void sendBitPC7(int bitVal);

void sendBitPD0 (int bitVal);
void sendBitPD1(int bitVal);
void sendBitPD2(int bitVal);
void sendBitPD3(int bitVal);
void sendBitPD4(int bitVal);
void sendBitPD5(int bitVal);
void sendBitPD6(int bitVal);
void sendBitPD7(int bitVal);
#endif	/* PORTTOGGLE_H */

