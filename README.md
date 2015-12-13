# xmasLEDTree

WIP

##Table of Contents

1. [Introduction](##introduction)
2. [How To Use](##how-to-use)
3. [Design Details and Changes](##design-details-and-changes)

##Introduction

This is the github page for the LED Christmas Tree project shown in XXXXXXXXXXXXXX. The LED Christmas Tree is a project that is inspired by the [LEDmas Tree by HNTE] (http://www.hownottoengineer.com/projects/ledMAS.html).

Unlike HNTE's  LEDmas Tree, this version is significantly smaller (hence a bit cheaper), play music, can be somewhat controlled by user via an android app and has a spectrum analyzer mode that lights up LEDs based on the music that's playing.

The entire project contains four separate parts

1. The "tree" itself, which contains all the LEDS and the acrylic glass.
2. The raspberry pi, which is used to play music user have stored on it and receive command from the Android app.
3. The audio amplifier and filter circuit, which is used to amplifier the sound wave from the raspberry pi and to limit frequency to 10kHz.
4. The microcontroller circuit, used as both a spectrum analyzer and to light up LEDs.
5. The Android app, used to give user some interaction such as playing/pause music or changing animation mode.

The "tree" itself is built from acrylic glass, a pvc pipe and a block of wood. Each base (or level) of the "tree" is cut from a sheet of acrylic glass into six squares of various lengths each containing four strips of WS2812 LEDs hooked in series.

##How To Use

1. Clone repository 
    
'''
git clone https://github.com/cheunste/xmasLEDTree
'''

2. Set up a static IP address for the raspberry pi. Make sure port 9000 is not in use. You can change the port, if you want.
3. Load music onto the raspberry pi and in the musicManager.py file located in the piServer folder, set the musicPath varible to your music directory.
4. Open up android studio, and open up the LEDTreeApp project. In the MainActivity.java file, set address variable in the doInBackground() method to the IP address of the raspberry pi. If you changed the port in step 3. you need to change the port as well.
5. Build the LEDTreeApp project and load the apk file to your android device.

6. Open up MPLAB and load the LEDController.X project.
7. Flash the pic18f microcontroller.
8. Construct the circuit shown in Schematic 1.
9. Hook up the connection for the raspberry pi to the microcontroller circuit shown in Schematic 1.

##Design Details and Design Changes
As mentioned earlier, this project is based off of HNTE's LEDmas Tree, but I wanted to play music at the same time (in HNTE's youtube video, it looks like the music is just added on). I decided to add a spectrum analyzer because I wanted a way to visualize sound. 

The original design for this LED Christmas Tree allows a user to use an app to select music, send the music to the christmas tree and a microcontroller generates lights based on fourier analyzsis from the audio wave. However, this turned out to be significantly time consuming and cutbacks were made.

Originally, each LED Strip was suppose to be controlled individually by the microcontroller, however, this turned out to be impossible with a single PIC chip. The reason for this is because the WS2812 have incredibily strict timing and referencing pins using decision statements takes a significant amount of time. 

For example, If there are 24 separate strips of LED, and you need to generate a certain LED pattern on a certain strip, there needs to be some sort of decision statement (if-statements, case-switch, bitwise, etc.) to decide what strip to send to. If there are 24 cascaded if-statements the earlier if-statements can be referenced quicker than the latter if-statements meaning LED strips in latter if-statements will produce unexpected results due to timing. This is probably why in the many WS2812 examples, there is only one pin that's a constant reference. However, using a simple if-else statment on a single port allows me to control two sets of LED strips without any issues.

Although this could be solved by using multiple microcontrollers, I wanted my design to fit in a small box and I couldn't design the circuit with multiple micrcontrollers without going over the limits of the box. While this could be possible by using a PCB (Printed Circuit Board) due to chemical storage reasons, I could not make a PCB. As a compromise, all the LEDs strips on a base is hooked up in series. 

In addition, since the PIC microcontroller handles both the LED lighting and performs the fourier analysis needed for the spectrum analyzer part, the LEDs in spectrum mode is slower than the music playing.

The raspberry pi was originally going to be used as a middleman whose purpose is to take a music the user sends from the Android app (via bluetooth) and send it to the audio circuit. This was changed so that the music is stored on the raspberry pi itself and the user can not choose music and have limited control through the android app (only change animation, pause/play music). In addition, communication between the raspberry pi and android is now handled through HTTP. The main reason for this change is because Android development is significantly time consuming and complex.

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
