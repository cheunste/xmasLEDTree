# xmasLEDTree

##Introduction

This is the github page for the LED Christmas Tree project shown in XXXXXXXXXXXXXX. Software is split into three sections

1. Android app, the application to allowo user to choose animation and choose when to play/stop music
2. Raspberry Pi, the server that plays music using pygame, handles users input and mangage the microcontroller's animation
3. PIC18F46K80 microcontroller, the microcontroller that lights up the WS2812 LED and performs a fourier analysis of the sound from the Raspberry Pi and lights up LEDs based on resulting fourier analysis.

##Dependencies and Other Notes

Note this is still a work in progress

###1. Android app

The IP Address the android app uses to find the raspberry pi server is hard coded. You need to know the IP address of the raspberry pi server and entered it in the app.

###2. Raspberry Pi

Requires: [cherrypy] (http://www.cherrypy.org/), [pygame] (http://pygame.org/hifi.html), [GPIO] (https://pypi.python.org/pypi/RPi.GPIO)

folderPath needs to be changed in the musicManager.py file to your music folder path on the rapsberry pi

Start the server by performing "sudo python httpServer.py". Need to do this because of threading and GPIO usage requires sudo.

GPIO pins can be changed in the gpioManager file and GPIO pins use BCM notation. Refer to the following [post for more information] (http://raspberrypi.stackexchange.com/a/12967)

The three files, musicManager.py, gpioManager.py and httpServer.py needs to be in the same directory.

###3. Microcontroller

FFT code and audio circuit is based off of [Simon Inns' real time audio spectrum analysyer project](waitingforfriday.com/index.php/Real-Time_Audio_Spectrum_Analyser)

The FFT code does not seem to accurate with higher frequencies (over 5kHz). 

Since the microcontroller is responsible for both the FFT calculation and lighting up the LEDs, the spctrum analyzer is significantly slow.

Certain pins on the chip are reservered for sending signal to the WS2812 LEDs. Changing this will require significant change in code.

Certain pins on the chip are used to hook up to the raspberry pi. These are used to activate certain animations. If you want to use different pins, you can change it in the main.c file
