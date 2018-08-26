# -*- coding: utf-8 -*-
import bluetooth
import os
import sys
import time
import time
import serial

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

cmd2 = 'feh -F --auto-zoom ~/disable_display/img/1_lf.png &'
cmd1 = 'feh -F --auto-zoom ~/disable_display/img/2_ri.png &'
smile = 'feh -F --auto-zoom ~/disable_display/img/3_smile.png &'
default = 'feh -F --auto-zoom img/default.png &'
kill = 'pkill -9 -ef feh'
count = 0


ser = serial.Serial('/dev/ttyACM0',9600, timeout = 1)

while 1:
    
  why=ser.read(1)


  if(why == '1'):
    os.system(cmd1)
    while(why == '1'):
      why=ser.readline(1)
      sock.send('1')
      time.sleep(0.005)
    sock.send('9')
    os.system(default)
    
  elif(why == '2'):
    os.system(cmd2)
    while(why == '2'):
      why=ser.readline(1)
      sock.send('2')
      time.sleep(0.005)
    sock.send('9')
    os.system(default)

  elif(why == '3'):
    os.system(smile)
    while(why == '3'):
      why=ser.readline(1)
      sock.send('3')
      time.sleep(0.005)
    sock.send('9')
    os.system(default)
 
  elif(why == '4'):
    sock.send('4')
    os.system(kill)

  
  if(sock.recv == '8'):
    os.system("python sms.py")
    os.systme("feh -F --auto-zoom img/4.png &")
