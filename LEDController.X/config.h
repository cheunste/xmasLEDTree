/* 
 * File:   config.h
 * Author: Author: mhibbett. mike.hibbett@gmail.com, mjhdesigns.com
 *
 * Created on 25 February 2014, 14:20
 */

#ifndef CONFIG_H
#define	CONFIG_H
#include "pic18f46k80.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define TESTPIN_W4			RA1
#define TESTPIN_W5			RA2
#define TESTPIN_W6			RA3

#pragma config PLLCFG = ON
    //Disable FOSC ONLY if you want to debug this thing.
//#pragma config FOSC = HS2    // Oscillator (HS oscillator (High power, 16 MHz - 25 MHz))
//#pragma config WDTEN = OFF
#pragma config XINST = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF

#pragma config CP0 = OFF
#pragma config WDTPS = 1
    
//#pragma config OSCCON
//#pragma config DSWDTEN = OFF
//#pragma config OSC = INTOSCPLL
//#pragma config CFGPLLEN = ON
//#pragma config PLLDIV = 2
//#pragma config PLLSEL = PLL96
 
#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

