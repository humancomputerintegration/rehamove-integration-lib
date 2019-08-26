import rehamovelib

class Rehamove:

	current_version = "v1.6"

	channel0 = ['r', 'red']
	channel1 = ['b', 'blue']
	channel2 = ['g1', 'gray1', 'grey1', 'black']
	channel3 = ['g2', 'gray2', 'grey2', 'white']

	MODE_LOW_LEVEL = 0
	MODE_MID_LEVEL = 1

	def __init__(self, port_name):
		self.rehamove = rehamovelib.open_port(port_name)
		self.mode = 0

	def version(self):
		c_version = rehamovelib.get_version()
		print("Rehamove Version: Python-side " + str(Rehamove.current_version) + ", C-side " + str(c_version))
		return Rehamove.current_version

	def get_mode(self):
		result = rehamovelib.get_mode(self.rehamove)
		return result

	def get_current(self):
		result = rehamovelib.get_current(self.rehamove)
		return result

	def get_pulse_width(self):
		result = rehamovelib.get_pulse_width(self.rehamove)
		return result

	def info(self):
		mode = self.get_mode()
		current = self.get_current()
		pulse_width = self.get_pulse_width()

		if mode == Rehamove.MODE_LOW_LEVEL:
			return "Rehamove device in low-level mode. Mid-level pulse is set to {} mA and {} us.".format(current, pulse_width)
		elif mode == Rehamove.MODE_MID_LEVEL:
			return "Rehamove device in mid-level mode. Mid-level pulse is set to {} mA and {} us.".format(current, pulse_width)
		else:
			return "Rehamove info() ERROR!"

	def get_channel(self, channel):
		chosen_channel = channel
		if isinstance(channel, str):
			channel = channel.lower()
			if channel in Rehamove.channel0:
				chosen_channel = 0
			elif channel in Rehamove.channel1:
				chosen_channel = 1
			elif channel in Rehamove.channel2:
				chosen_channel = 2
			elif channel in Rehamove.channel3:
				chosen_channel = 3
			else:
				chosen_channel = 0 # Default
		elif isinstance(channel, int):
			if channel < 0 and channel > 3:
				chosen_channel = 0 # Default
		else:
			chosen_channel = 0
		return chosen_channel

	def pulse(self, channel, current, pulse_width):
		if self.rehamove == None:
			print("python Rehamove pulse() ERROR! Rehamove object does not exist.")
			return -1
		chosen_channel = self.get_channel(channel)
		result = rehamovelib.pulse(self.rehamove, chosen_channel, current, pulse_width)
		if result != 0:
			print("python Rehamove pulse() ERROR!")
			return -1
		else:
			print("python Rehamove pulse() sent.")
			return 0

	def custom_pulse(self, channel, points_array):
		if self.rehamove == None:
			print("python Rehamove custom_pulse() ERROR! Rehamove object does not exist.")
			return -1
		chosen_channel = self.get_channel(channel)
		original_length = len(points_array)
		num_points = len(points_array)
		# Error handling (warning) if too many points.
		if num_points > 16:
			print("python Rehamove custom_pulse() WARNING! Maximum of 16 points allowed, truncating points array.")
			num_points = 16
		
		# Error handling (exception) if malformed points.
		try:
			for i in range(0, num_points):
				current = points_array[i][0]
				pulse_width = points_array[i][1]
		except:
			print("python Rehamove custom_pulse() ERROR! Malformed points array, should be: [ (current0, pulse_width0), (current1, pulse_width1), ... ]")
			return -1

		# Handle if the user supplies less than 16 points: fill up empty points in the array.
		remaining_points = 16 - num_points
		for _ in range(0, remaining_points):
			points_array.append((0.0, 0))

		# Get all of our point data.
		c0, w0 = points_array[0][0], points_array[0][1]
		c1, w1 = points_array[1][0], points_array[1][1]
		c2, w2 = points_array[2][0], points_array[2][1]
		c3, w3 = points_array[3][0], points_array[3][1]
		c4, w4 = points_array[4][0], points_array[4][1]
		c5, w5 = points_array[5][0], points_array[5][1]
		c6, w6 = points_array[6][0], points_array[6][1]
		c7, w7 = points_array[7][0], points_array[7][1]
		c8, w8 = points_array[8][0], points_array[8][1]
		c9, w9 = points_array[9][0], points_array[9][1]
		c10, w10 = points_array[10][0], points_array[10][1]
		c11, w11 = points_array[11][0], points_array[11][1]
		c12, w12 = points_array[12][0], points_array[12][1]
		c13, w13 = points_array[13][0], points_array[13][1]
		c14, w14 = points_array[14][0], points_array[14][1]
		c15, w15 = points_array[15][0], points_array[15][1]

		result = rehamovelib.custom_pulse(self.rehamove, chosen_channel, original_length, c0, w0, c1, w1, c2, w2, c3, w3, c4, w4, c5, w5, c6, w6, c7, w7, c8, w8, c9, w9, c10, w10, c11, w11, c12, w12, c13, w13, c14, w14, c15, w15)
		if result != 0:
			print("python Rehamove custom_pulse() ERROR!")
			return -1
		else:
			print("python Rehamove custom_pulse() sent.")
			return 0

	def battery(self):
		if self.rehamove == None:
			print("python Rehamove ERROR! Rehamove object does not exist.")
			return -1
		result = rehamovelib.battery_request(self.rehamove)
		if result != 0:
			print("python Rehamove battery() ERROR!")
			return -1
		else:
			battery_level = rehamovelib.get_battery(self.rehamove)
			print("python Rehamove battery(): " + str(battery_level) + "%")
			return battery_level

	def change_mode(self, mode):
		if self.rehamove == None:
			print("python Rehamove change_mode() ERROR! Rehamove object does not exist.")
			return -1
		result = rehamovelib.change_mode(self.rehamove, mode)
		if result != 0:
			print("python Rehamove change_mode() ERROR!")
			return -1
		else:
			print("python Rehamove change_mode(): Changed mode to " + str(mode) + ".")
			self.mode = mode
			return 0

	def set_pulse(self, current, pulse_width):
		if self.rehamove == None:
			print("python Rehamove set_pulse() ERROR! Rehamove object does not exist.")
			return -1
		result = rehamovelib.set_pulse_data(self.rehamove, current, pulse_width)
		if result != 0:
			print("python Rehamove set_pulse() ERROR!")
			return -1
		else:
			print("python Rehamove set_pulse(): Set pulse current to " + str(current) + " and pulse width to " + str(pulse_width) + ".")
			return 0

	def run(self, channel, period, total_milliseconds):
		if self.rehamove == None:
			print("python Rehamove run() ERROR! Rehamove object does not exist.")
			return -1
		if self.mode != Rehamove.MODE_MID_LEVEL:
			print("python Rehamove run() ERROR! Mode must be set to mid-level.")
			return -1
		chosen_channel = self.get_channel(channel)
		result = rehamovelib.run(self.rehamove, chosen_channel, period, total_milliseconds)
		if result != 0:
			print("python Rehamove run() ERROR!")
			return -1
		else:
			print("python Rehamove run(): Completed.")
			return 0

	def start(self, channel, period):
		if self.rehamove == None:
			print("python Rehamove start() ERROR! Rehamove object does not exist.")
			return -1
		if self.mode != Rehamove.MODE_MID_LEVEL:
			print("python Rehamove start() ERROR! Mode must be set to mid-level.")
			return -1
		chosen_channel = self.get_channel(channel)
		result = rehamovelib.midlevel_start(self.rehamove, chosen_channel, period)
		if result != 0:
			print("python Rehamove start() ERROR!")
			return -1
		else:
			print("python Rehamove start(): Completed.")
			return 0

	def update(self):
		if self.rehamove == None:
			print("python Rehamove update() ERROR! Rehamove object does not exist.")
			return -1
		if self.mode != Rehamove.MODE_MID_LEVEL:
			print("python Rehamove update() ERROR! Mode must be set to mid-level.")
			return -1
		result = rehamovelib.midlevel_update(self.rehamove)
		if result != 0:
			print("python Rehamove update() ERROR!")
			return -1
		else:
			print("python Rehamove update(): Completed.")
			return 0

	def end(self):
		if self.rehamove == None:
			print("python Rehamove end() ERROR! Rehamove object does not exist.")
			return -1
		if self.mode != Rehamove.MODE_MID_LEVEL:
			print("python Rehamove end() ERROR! Mode must be set to mid-level.")
			return -1
		result = rehamovelib.midlevel_end(self.rehamove)
		if result != 0:
			print("python Rehamove end() ERROR!")
			return -1
		else:
			print("python Rehamove end(): Completed.")
			return 0

	def __del__(self):
		# Only close the port if we have a Rehamove object to close
		if self.rehamove != None:
			result = rehamovelib.close_port(self.rehamove)
			if result != 0:
				print("python Rehamove close_port() ERROR!")

