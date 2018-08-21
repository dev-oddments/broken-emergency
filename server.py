# -*- coding: utf-8 -*-

from Tkinter import *
import bluetooth
import os
import sys

print "Searching for devices..."
print ""
nearby_devices = bluetooth.discover_devices()
num = 0
print "Select your device by entering its coresponding number..."
for i in nearby_devices:
  num+=1
  print num , ": " , bluetooth.lookup_name( i )

selection = input("> ") - 1
print "You have selected", bluetooth.lookup_name(nearby_devices[selection])
bd_addr = nearby_devices[selection]

port = 1

sock = bluetooth.BluetoothSocket( bluetooth.RFCOMM )
sock.connect((bd_addr, port))
data = ""
cmd1 = 'feh -F --auto-zoom ~/betterlife/img/1.png &'
cmd2 = 'feh -F --auto-zoom ~/betterlife/img/2.png &'
cmd3 = 'feh -F --auto-zoom ~/betterlife/img/3.png &'
cmd4 = 'feh -F --auto-zoom ~/betterlife/img/4.png &'
cmd5 = 'feh -F --auto-zoom ~/betterlife/img/5.png &'
cmd6 = 'feh -F --auto-zoom ~/betterlife/img/6.png &'
cmd7 = 'feh -F --auto-zoom ~/betterlife/img/7.png &'
cmd8 = 'feh -F --auto-zoom ~/betterlife/img/8.png &'

while 1:
  why = sock.recv(1024)
  if(why == '0'):
    os.system(cmd1)
    print("ln")
  elif(why == '1'):
    os.system(cmd2)
    print("lu")
  
 
