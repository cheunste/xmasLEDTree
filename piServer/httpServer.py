import cherrypy
from cherrypy.process.plugins import Monitor
import threading
import os,time,datetime
import re, random
import json
import pygame
import Queue
import gpioManager
import musicManager

#CONSTANTS
folderPath='/home/pi/music/'
startTime=16
endTime=23
maxQueueItem=10
currHour=datetime.datetime.now().hour
currMonth=datetime.datetime.now().month

trackerDict= {"currentAnimation":"SPECTRUM","LEDState":0}
#Create a queue. This is used to pass commands to the music thread and NOT anything else.
#maxQueueItem is the max queue item. Change maxQeueuItem if needed 
musicCommandQueue= Queue.Queue(maxQueueItem)
queueLock=threading.Lock()

#This method is used to check if current hour is within the desired activation time
def inTimeFrame():
	return (currHour >= startTime) and (currHour < endTime)

#Another threaded method that's used to shut off all LED when outside of timeframe
def LEDOff():
	while currMonth==11 or currMonth==12:
		while not inTimeFrame():
			gpioManager.lightsState(True)

	
#Class that's used for HTTP GET and POST requests. Returns JSON format
class ledTreeServer(object):
	exposed=True
	
	@cherrypy.tools.accept(media='text/plain')
	@cherrypy.expose
	@cherrypy.tools.json_in()
	@cherrypy.tools.json_out()
	def index(self,**kwargs):
		cherrypy.response.headers['Content-Type']="application/json"
		jsonInput=cherrypy.request.json
		data=jsonInput

		returnMessage=''
		currentAnimation=""
		LEDState=1

		#print kwargs

		for jsonItem in jsonInput:
			print "ITEM: ", jsonItem
			print "DATA[ITEM]: ",data[jsonItem]
	
			if jsonItem=="SPECTRUM":
				print "IN SPECTRUM"
				trackerDict["currentAnimation"]="SPECTRUM"
				gpioManager.clearAnimationGPIO()
				gpioManager.spectrumAnimation(data[jsonItem])
				returnMessage.join("Spectrum Mode On ")

			elif jsonItem=="RING":
				print "IN RING"
				trackerDict["currentAnimation"]="RING"
				gpioManager.clearAnimationGPIO()
				gpioManager.ringAnimation(data[jsonItem])
				returnMessage.join("Ring Mode On ")

			elif jsonItem=="RANDOM":
				print "IN RANDOM"
				trackerDict["currentAnimation"]="RANDOM"
				gpioManager.clearAnimationGPIO()
				gpioManager.rndAnimation(data[jsonItem])
				returnMessage.join("Random Mode On ")

			elif jsonItem=="RGSTRIPS":
				print "IN RGSTRIPS"
				trackerDict["currentAnimation"]="RGSTRIPS"
				gpioManager.clearAnimationGPIO()
				gpioManager.rgStripsAnimation(data[jsonItem])
				returnMessage.join("RG Strip Mode On ")

			elif jsonItem=="RGLEVEL":
				print "IN RGLEVEL"
				trackerDict["currentAnimation"]="RGLEVEL"
				gpioManager.clearAnimationGPIO()
				gpioManager.rgLevelAnimation(data[jsonItem])
				returnMessage.join("RG Level Mode On ")

			elif jsonItem == "LED":
				print "IN LED"
				trackerDict["LEDState"]=data[jsonItem]
				gpioManager.lightsState(data[jsonItem])
				returnMessage.join("LED state changed")

			elif jsonItem == "BOUNCE":
				print "IN BOUNCE"
				trackerDict["currentAnimation"]="BOUNCE"
				gpioManager.lightsState(data[jsonItem])
				returnMessage.join("BOUNCE Mode on")

			#The following items are used to manipulate music and requires a queue
			elif jsonItem=="PAUSE":
				print "IN PAUSE"
				gpioManager.playing(False)
				#Add command and state to the queue
				queueLock.acquire()
				musicCommandQueue.put(jsonItem)
				musicCommandQueue.put(data[jsonItem])
				queueLock.release()
			elif jsonItem=="PLAY":
				print "IN PLAY"
				gpioManager.playing(True)
				#Add command and state to the queue
				queueLock.acquire()
				musicCommandQueue.put(jsonItem)
				musicCommandQueue.put(data[jsonItem])
				queueLock.release()

			#NOTE: Skip and Stop doesn't work
			elif jsonItem=="SKIP":
				print "IN SKIP"
				#Add command and state to the queue
				queueLock.acquire()
				musicCommandQueue.put(jsonItem)
				musicCommandQueue.put(data[jsonItem])
				queueLock.release()
			elif jsonItem=="STOP":
				print "IN STOP"
				#Add command and state to the queue
				queueLock.acquire()
				musicCommandQueue.put(jsonItem)
				musicCommandQueue.put(data[jsonItem])
				queueLock.release()

			#This one is only used when the android app wants to get data. This is still in testing
			elif jsonItem=="FETCH":
				return {trackerDict['currentAnimation']:1,"LED":trackerDict['LEDState']}
				return "Here is something...."

			else:
				print "Something is wrong"
				returnMessage.join("Error")

		#return rtnMessage
		return returnMessage

def startServer():
	cherrypy.config.update({'server.socket_host':'0.0.0.0'})
	cherrypy.config.update({'server.socket_port':9000})
	cherrypy.quickstart(ledTreeServer(),'/')

if __name__=='__main__':
	'''
	This is where the entire program start. There are three
	parts to this program

	1) Music playing
	2) GET/POST requests made
	3) GPIO handling 

	Playing music and GET/POST should be separated by thread since I do not want funcitons interrupting each other.
	GPIO could be put together with the GET/POST request thread. 

	The entire server should only be activated when it is dark, so about 1600-2300. You will want to import the datetime object 
	for this
	'''

	#init pygame parameters
	pygame.init()
	pygame.mixer.init(22050,16,2,4096)
	pygame.mixer.music.set_volume(1.0)

	#Set up GPIO Pin with WiringPi GPIO reference
	gpioManager.GPIOSetup()

	#Create a thread for playing music.
	musicThread=threading.Thread(target=musicManager.musicHandler,args=(musicCommandQueue,queueLock))
	musicThread.daemon=True

        #Create a thread to monitor time
        timeThread=threading.Thread(target=LEDOff)
        timeThread.daemon=True

	#Start the two threads
	musicThread.start()
        timeThread.start()

	#Start the server
	startServer()


	'''
	Used for debuggign
	'''
	#musicManager.musicHandler(musicCommandQueue,queueLock)
	#startServer()
