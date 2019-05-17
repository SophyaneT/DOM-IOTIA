#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan 29 20:50:39 2019

@author: Gaetan
"""

from bluetooth import *
import socket
import RPi.GPIO as GPIO
from time import sleep


GPIO.setmode(GPIO.BCM)
'''LED'''
GPIO.setup(23, GPIO.OUT)
GPIO.output(23, GPIO.LOW)
GPIO.setup(24, GPIO.OUT)
GPIO.output(24, GPIO.LOW)
GPIO.setup(25, GPIO.OUT)
GPIO.output(25, GPIO.LOW)

'''Moteur'''
GPIO.setup(MOTOR1_EN, GPIO.OUT)
GPIO.setup(MOTOR1_A, GPIO.OUT)
GPIO.setup(MOTOR1_B, GPIO.OUT)
motor1GPIO = GPIO.PWM(MOTOR1_EN, 100)
MOTOR1_EN = 14
MOTOR1_A = 18
MOTOR1_B = 15

port = 3
MAC_Adress = "80:7D:3A:C7:FD:BE" 

data = b''
client_socket=BluetoothSocket(RFCOMM)
client_socket.connect(("80:7D:3A:C7:FD:BE",1))
print ("Connecte " + MAC_Adress)


while True:
    size = 1024
    data = client_socket.recv(size)

    stringdata = data.decode("utf-8")
    test = stringdata
    print(stringdata)
    '''*************************ACTION  LUMIERE*************************'''
    if test[0] == 'L':
        #int(test[4:8])
        #print(test[4:8])
        if int(test[4:8]) <=2000:
            GPIO.output(23, GPIO.HIGH)
            print("allumer")
        else:
            GPIO.output(23, GPIO.LOW)
            print("eteind")

    '''*************************ACTION  TEMPERATURE*************************'''
    if test[0] == 'T':
        #int(test[4:8])
        #print(test[4:8])
        if int(test[4:6]) <=23:
            GPIO.output(24, GPIO.HIGH)
            GPIO.output(25, GPIO.LOW)
            print("clime")
        else:
            GPIO.output(24, GPIO.LOW)
            GPIO.output(25, GPIO.HIGH)
            print("chauffage")

	'''*************************ACTION  Pluie*************************'''
    if test[0] == 'P':
        #int(test[4:8])
        #print(test[4:8])
        if int(test[4:7]) == "OUI":
            motor1GPIO.start(50)
	    GPIO.output(MOTOR1_A, GPIO.HIGH)
    	    GPIO.output(MOTOR1_B, GPIO.LOW)
 	    sleep(1.5)
        else:
            GPIO.output(24, GPIO.LOW)
            GPIO.output(25, GPIO.HIGH)
            print("chauffage")
        
client_socket.close()
