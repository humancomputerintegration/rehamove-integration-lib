from rehamove import *
import time

# Trying on Windows, connecting to USB port COM3
r = Rehamove("COM3")
r.battery()
for i in range(0, 5):
	r.pulse("blue", 6, 200)
	time.sleep(1)