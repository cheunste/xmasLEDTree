/* 
 * File:   spectrum.h
 * Author: stephen
 *
 * Created on July 8, 2015, 4:20 PM
 */

#ifndef SPECTRUM_H
#define	SPECTRUM_H

#ifdef	__cplusplus
extern "C" {
#endif



void spectrum(void);
void writeLED(short inputData[]);
int ratioSquare(float freq);
int calcLEDLightup(int LEDonStrip, int inputValue);
#ifdef	__cplusplus
}
#endif

#endif	/* SPECTRUM_H */

