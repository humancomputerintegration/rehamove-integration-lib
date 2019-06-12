import time
from rehamove import *

def main():

	r = Rehamove("/dev/ttyUSB0")

	for i in range(0, 10):
		r.pulse("blue", 6, 100)
		time.sleep(1)

if __name__ == '__main__':
	main()