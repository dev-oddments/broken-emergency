# -*- coding: utf-8 -*-
import bluetooth
import os
import sys
import time

import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
time.sleep(1)

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
cmd1 = 'feh -F --auto-zoom ~/disable_display/img/1_lf.png &'
cmd2 = 'feh -F --auto-zoom ~/disable_display/img/2_ri.png &'
smile = 'feh -F --auto-zoom ~/disable_display/img/3_smile.png &'
default = 'feh -F --auto-zoom img/default.png &'
kill = 'pkill -9 -ef feh'
count = 0

while 1:
  why = sock.recv(1024)
  if(why == '1'):
    os.system(cmd1)
    while(why == '1'):
      why = sock.recv(1024)
      time.sleep(0.5)
    os.system(default)
    print("ln")
    
  elif(why == '2'):
    os.system(cmd2)
    while(why == '2'):
      why = sock.recv(1024)
      time.sleep(0.5)
    os.system(default)
    print("lu")

  elif(why == '3'):
    os.system(smile)
    while(why == '3'):
      why = sock.recv(1024)
      time.sleep(0.5)
    os.system(default)
 
  elif(why == '4'):
    os.system(kill)
###https://m.blog.naver.com/PostView.nhn?blogId=cosmosjs&logNo=220805719737&proxyReferer=https%3A%2F%2Fwww.google.co.kr%2F
  
  result = GPIO.input(23)
  if result == 1:
    count += 1
  if count == 10:
    os.system('python coolsms.py')
    print("진동이 감지 되었습니다.")
    time.sleep(0.05)
    count = 0
  else:
    print("진동이 없습니다.")
    time.sleep(0.05)
