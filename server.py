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
cmd1 = 'feh -F --auto-zoom ~/disable_display/img/1_left.jpeg &'
cmd2 = 'feh -F --auto-zoom ~/disable_display/img/2_right.jpeg &'
cmd3 = 'feh -F --auto-zoom ~/disable_display/img/3_smile.jpeg &'
kill = 'pkill -9 -ef feh'

while 1:
  why = sock.recv(1024)
  if(why == '0'):
    os.system(cmd1)
    print("ln")
  elif(why == '1'):
    os.system(cmd2)
    print("lu")
  elif(why == '2'):
    os.system(kill)
  elif(why == '3'):
    os.system(cmd3)
 
