import threading
import os,time,datetime
import re, random
import json
import pygame
import Queue
import gpioManager
import httpServer

folderPath='/home/pi/music/'
startTime=13
endTime=23
maxQueueItem=10
currHour=datetime.datetime.now().hour
currMonth=datetime.datetime.now().month
def inTimeFrame():
	return (currHour >= startTime) and (currHour < endTime)
#Build a file list from the directory in folderpath.
def build_file_list():
	file_list=[]
	for root, folders, files in os.walk(folderPath):
		folders.sort()
		files.sort()
		for filename in files:
			if re.search(".wav$",filename) != None:
				file_list.append(os.path.join(root,filename))
	return file_list

#Plays all the songs in the file_list
def play_songs(file_list,musicCommandQueue,lock):
	#Shuffles all songs in the file list "randomly". Remove it if you want
	random.shuffle(file_list)
	for num,song in enumerate(file_list):
		pygame.mixer.music.load(file_list[num])
		print num,song
		#Play song
		if httpServer2.inTimeFrame():
			gpioManager.lightsState(not httpServer2.inTimeFrame())
			pygame.mixer.music.play()
		#pygame.mixer.music.play()
		while pygame.mixer.music.get_busy():
			pygame.time.Clock().tick(100)
			#This is most liekly where condition statements for when user wants to pause, skip, resume, goes
			if not musicCommandQueue.empty():
				print "INSIDE command queue  if statement"
				lock.acquire()
				command=musicCommandQueue.get()
				#value might not get used. Depends on how I end up designing the Android interface.
				value=musicCommandQueue.get()
				if command == "PAUSE":
					print "PAUSE"
					pygame.mixer.music.pause()
				if command == "PLAY":
					print "PLAYING...."
					pygame.mixer.music.unpause()
				if command == "STOP":
					print "STOPPED"
					pygame.mixer.stop()
				if command == "SKIP":
					print "SKIPING...."
					if (num+1)>num:
						continue
					else:
						pygame.mixer.music.stop()
						pygame.mixer.music.load(file_list[num+1])
						pygame.mixer.music.play()
				#Volume may not be implementable due existence of amplifier chip always giving a gain of 200
				if command == "VOLUME":
					print "SETTING VOLUME...."
					pygame.mixer.music.set_volume(value)
				lock.release()

		pygame.mixer.music.queue(song)

#Entry point of class
def musicHandler(musicCommandQueue,lock):
	#print currHour
	files=build_file_list()

		#self.play_songs(files)
	#if month is December and hour is between 1600 and 2300, play music
	while currMonth==11 or currMonth==12:
		while httpServer2.inTimeFrame():	
			gpioManager.lightsState(httpServer2.inTimeFrame())
			play_songs(files,musicCommandQueue,lock)
			#gpioManager.lightsState(False)
		#if it is not in time frame but still in the current moth, activate the pin on pi to turn off all the lights on the microcontroller
		#while not httpServer2.inTimeFrame():
		#	gpioManager.lightsState(True)
