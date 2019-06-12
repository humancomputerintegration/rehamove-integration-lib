from rehamove import *
import sys
import time

waveform0 = [(5, 200), (0, 100), (-5, 200)]
waveform1 = [(5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100)]
waveform2 = [(5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100), (5, 200)]
waveform3 = [(5, 200), (0, 100), (-5, 200)]

repetitions = 500

def main(arg_list):
	if len(arg_list) != 2:
		print("test.py ERROR! Arguments should be: python test.py [port_name]")
		return
	port_name = arg_list[1]
	print("test.py started with port_name: {}".format(port_name))

	r = Rehamove(port_name)
	#r.battery()

	print("Starting pulses every second:")
	time.sleep(10)

	for i in range(0, 100):
		print("Pulse {}".format(i))
		r.pulse("blue", 7, 200)
		time.sleep(1)

	# print("single pulse starting")
	# for i in range(0, repetitions):
	# 	r.pulse("blue", 5, 200)
	# 	time.sleep(0.1)

	# time.sleep(2)
	
	# waveform0 = [(5, 200), (0, 100), (-5, 200)]
	# print("waveform0 starting")
	# for i in range(0, repetitions):
	#  	r.custom_pulse("blue", waveform0)
	#  	time.sleep(0.1) 
	 	
	waveform1 = [(5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100), (5, 200), (0, 100), (-5, 200), (0, 100)]
	print("waveform1 starting")
	for i in range(0, repetitions):
	 	r.custom_pulse("blue", waveform1)
	 	time.sleep(0.1) 

	 	# Works

	# time.sleep(2)
	# print("waveform2 starting")

	# for i in range(0, repetitions):
	# 	r.custom_pulse("blue", waveform2)

	# time.sleep(2)
	# print("waveform3 starting")

	# for i in range(0, repetitions):
	# 	r.custom_pulse("blue", waveform3)

	r.battery()

if __name__ == '__main__':
	main(sys.argv)