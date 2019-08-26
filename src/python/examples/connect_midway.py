from rehamove import *
import time
r = Rehamove("COM3") # while USB device is unplugged
while r.rehamove == None: # plug in the USB device at some point during the loop
	r = Rehamove("COM3")
	time.sleep(0.5)
r.battery()
r.pulse(1, 6, 200)
r.version()