#!/usr/bin/python
import sys, serial, threading

def tf():
  global run,sr
  while run:
    sys.stdout.write(sr.read())
    sys.stdout.flush()

sr = serial.Serial(port=sys.argv[1], timeout=0.1)
t=threading.Thread(target=tf)
run=1
t.start()
try:
  while True:
    sr.write(sys.stdin.readline())
except KeyboardInterrupt:
  print ""
  run=0
t.join()
