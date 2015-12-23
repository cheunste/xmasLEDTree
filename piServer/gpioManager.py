import RPi.GPIO as GPIO
'''
This method is to set up GPIO pins when the program initially starts.
GPIO pins will be using BCM notation along with physcial board reference in ()
GPIO pins used are also mapped to their respective usage and default state in []

Please be careful with rapsberry pi versions. 
Refer to following link if you get confused:
http://raspberrypi.stackexchange.com/questions/12966/what-is-the-difference-between-board-and-bcm-for-gpio-pin-numbering 


Setting a pin high (1) means it is active
Setting a pin low (0) means it is inactive 

GPIO04 (07)-
GPIO08 (24)-Music Playing [1]
GPIO07 (26)-Music Pause [0]
GPIO09 (21)-
GPIO10 (19)-
GPIO17 (11)-
GPIO18 (12)-Spectrum Mode [1]
GPIO21 (13)-
GPIO22 (14)-
GPIO23 (16)-Random Mode [0]
GPIO24 (18)-Ring Mode [0]
GPIO25 (22)-LEDOffPin[1]
GPIO27 (13)-
GPIO22 (15)-

'''

RGLevelPin		= 14
RGStripPin		= 15
spectrumPin		= 18
randomPin		= 23
ringPin			= 24
LEDOffPin		= 25
playingPin		= 8
bouncePin		= 7

def GPIOSetup():
	GPIO.cleanup()
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(spectrumPin,GPIO.OUT)
	GPIO.setup(playingPin,GPIO.OUT)
	GPIO.setup(bouncePin,GPIO.OUT)
	GPIO.setup(ringPin,GPIO.OUT)
	GPIO.setup(randomPin,GPIO.OUT)
	GPIO.setup(LEDOffPin,GPIO.OUT)
	GPIO.setup(RGLevelPin,GPIO.OUT)
	GPIO.setup(RGStripPin,GPIO.OUT)

	GPIO.output(spectrumPin,GPIO.HIGH)
	GPIO.output(playingPin,GPIO.HIGH)
	GPIO.output(randomPin,GPIO.LOW)
	GPIO.output(ringPin,GPIO.LOW)
	GPIO.output(bouncePin,GPIO.LOW)
	GPIO.output(LEDOffPin,GPIO.LOW)
	GPIO.output(RGLevelPin,GPIO.LOW)
	GPIO.output(RGStripPin,GPIO.LOW)

#This method is for clearing GPIO related to animation
def clearAnimationGPIO():
	GPIO.output(spectrumPin,GPIO.LOW)
	GPIO.output(randomPin,GPIO.LOW)
	GPIO.output(ringPin,GPIO.LOW)
	GPIO.output(RGLevelPin,GPIO.LOW)
	GPIO.output(RGStripPin,GPIO.LOW)

#Spectrum Animation
def spectrumAnimation(state):
	if state:
		clearAnimationGPIO()
		GPIO.output(spectrumPin,GPIO.HIGH)
		print "Spectrum is now activated"
	else:
		clearAnimationGPIO()
		GPIO.output(spectrumPin,GPIO.LOW)
		print "Spectrum is deactivated"

#Random Color Animation
def rndAnimation(state):
	if state:
		clearAnimationGPIO()
		GPIO.output(randomPin,GPIO.HIGH)
		print "Random is now activated"
	else:
		clearAnimationGPIO()
		GPIO.output(spectrumPin,GPIO.LOW)
		print "Random is deactivated"

#Ring Animation
def ringAnimation(state):
	if state:
		clearAnimationGPIO()
		GPIO.output(ringPin,GPIO.HIGH)
		print "Ring is now activated"
	else:
		clearAnimationGPIO()
		GPIO.output(ringPin,GPIO.LOW)
		print "Ring is deactivated"

#Method for Red Green Levels
def rgLevelAnimation(state):
	if state:
		clearAnimationGPIO()
		GPIO.output(RGLevelPin,GPIO.HIGH)
		print "Red Green Level is now active"
	else:
		clearAnimationGPIO()
		GPIO.output(RGLevelPin,GPIO.LOW)
		print "Red Green Level is now deactived"

#Method for Red Green Strip
def rgStripsAnimation(state):
	if state:
		clearAnimationGPIO()
		GPIO.output(RGStripPin,GPIO.HIGH)
		print "Red Green Strips is now active"
	else:
		clearAnimationGPIO()
		GPIO.output(RGStripPin,GPIO.LOW)
		print "Red Green Strips is now deactived"

#Method for bounce animation
def bounce(state):
	print "in gpio bounce method"
	#GPIO.output(bouncePin,GPIO.HIGH) if state else GPIO.output(bouncePin,GPIO.LOW)
	if state:
		clearAnimationGPIO()
		GPIO.output(bouncePin,GPIO.HIGH)
	else:
		clearAnimationGPIO()
		GPIO.output(bouncePin,GPIO.LOW)
	print "Pause pin is now ",state

#Method to see if music is playing. Spectrum animation depends on this, but the dependency shows up in
#the microcontorller
def playing(state):
	print "in gpio playing method"
	#GPIO.output(playingPin,GPIO.HIGH) if state else GPIO.output(bouncePin,GPIO.LOW)
	if state:
		GPIO.output(playingPin,GPIO.HIGH)
	else:
		GPIO.output(playingPin,GPIO.LOW)

	print "Playing pin is now",state

#Method to shut all the lights on the tree.
def lightsState(state):
	print "lightsOff state: ",state
	if not state:
		GPIO.output(LEDOffPin,GPIO.LOW)
		print "LEDOffPin is low"
	else:
		GPIO.output(LEDOffPin,GPIO.HIGH)
		clearAnimationGPIO()
		print "LEDOffPin is high"
