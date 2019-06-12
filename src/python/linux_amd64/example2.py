import time
from rehamove import *

def main():

	r = Rehamove("/dev/ttyUSB0")
	
	waveform1 = [(5, 200), (0, 100), (-5, 200)]
	
	for i in range(0, 100):
	 	r.custom_pulse("blue", waveform1)
	 	time.sleep(0.1) 

	time.sleep(2)
	 	
	waveform2 = [(5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100)]
	for i in range(0, 100):
	 	r.custom_pulse("blue", waveform2)
	 	time.sleep(0.1) 

if __name__ == '__main__':
	main()