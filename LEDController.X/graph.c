/************************************************************************
	graph.c

    FFT Audio Analysis
    Copyright (C) 2011 Simon Inns

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Email: simon.inns@gmail.com

************************************************************************/

#ifndef GRAPH_C
#define GRAPH_C

// Global includes
#include <htc.h>

// Local includes
#include "hardware.h"
#include "graph.h"

// Write a byte directly to the screen hardware (quick version)
void fLcdWrite(unsigned char cmdType, unsigned char bank, unsigned char byte)
{

}

// Global to hold the display data (required for output damping)
short displayData[32];

// Plot the output graph
void drawFftGraph(short inputData[])
{
    
    NOP();
    NOP();
}

// Initialise the gLCD
void gLcdInit(void)
{
	// Bring the display out of reset
	//GLCD_RES = 0; // Screen in reset
	__delay_us(250);
	//GLCD_RES = 1; // Screen out of reset
	__delay_us(250);

	// Set Y Address = 0
	fLcdWrite(GLCD_CMD, 0, 0b01000000);
	fLcdWrite(GLCD_CMD, 1, 0b01000000);

	// Set X Address = 0
	fLcdWrite(GLCD_CMD, 0, 0b10111000);
	fLcdWrite(GLCD_CMD, 1, 0b10111000);

	// Set Display start line = 0
	fLcdWrite(GLCD_CMD, 0, 0b11000000);
	fLcdWrite(GLCD_CMD, 1, 0b11000000);

	// Turn the display ON
	fLcdWrite(GLCD_CMD, 0, 0b00111111);
	fLcdWrite(GLCD_CMD, 1, 0b00111111);
}

// Clear the gLCD to black (zero)
void gLcdClear(void)
{
	unsigned char x, y;

	for (y = 0; y < 8; y++)
	{
		// Move to the correct screen page
		fLcdWrite(GLCD_CMD, 0, y | 0b10111000);
		fLcdWrite(GLCD_CMD, 0, 0b01000000);

		fLcdWrite(GLCD_CMD, 1, y | 0b10111000);
		fLcdWrite(GLCD_CMD, 1, 0b01000000);
		
		for (x = 0; x < 64; x++)
		{
			fLcdWrite(GLCD_DATA, 0, 0x00);
			fLcdWrite(GLCD_DATA, 1, 0x00);
		}
	}
}

#endif