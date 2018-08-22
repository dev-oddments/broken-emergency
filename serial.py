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


ser = serial.Serial('/dev/ttyACM0',9600)

while 1:
  read_serial=ser.readline()
  print(read_serial)
  
