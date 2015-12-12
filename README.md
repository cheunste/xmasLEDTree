# xmasLEDTree

This is the software portion to the LED Christmas project shown in XXXXXXXXXXXXXX. Software is split into three sections

1. Android app
2. Raspberry Pi
3. PIC18F46K80 microcontroller

##Dependencies and other notes

##1. Android app

The IP Address the android app uses to find the raspberry pi server is hard coded. You need to know the IP address of the raspberry pi server and entered it in the app.

##2. Raspberry Pi

Requires cherrypy, pygame

folderPath needs to be changed in the musicManager.py file to your music folder path on the rapsberry pi

Start the server by performing "sudo python httpServer.py"

GPIO pins can be changed in the gpioManager file. Refer to the following [post] (http://raspberrypi.stackexchange.com/a/12967)

##3. Microcontroller
