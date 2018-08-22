# -*- coding: utf-8 -*-
import bluetooth
import os
import sys
import time
import serial
import time


cmd1 = 'feh -F --auto-zoom ~/disable_display/img/1_lf.png &'
cmd2 = 'feh -F --auto-zoom ~/disable_display/img/2_ri.png &'
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
      time.sleep(0.01)
    os.system(default)
    
  elif(why == '2'):
    os.system(cmd2)
    while(why == '2'):
      why=ser.readline(1)
      time.sleep(0.01)
    os.system(default)

  elif(why == '3'):
    os.system(smile)
    while(why == '3'):
      why=ser.readline(1)
      time.sleep(0.01)
    os.system(default)
 
  elif(why == '4'):
    os.system(kill)
