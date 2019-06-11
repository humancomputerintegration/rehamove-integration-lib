import rehamovelib

class Rehamove:
	def __init__(self, port_name):
		self.rehamove = rehamovelib.open_port(port_name)

	def pulse(self, channel, current, pulse_width):
		rehamovelib.pulse(self.rehamove, channel, current, pulse_width)

	def custom_pulse(self, channel, points_array):
		original_length = len(points_array)
		num_points = len(points_array)
		# Error handling (warning) if too many points.
		if num_points > 16:
			print("custom_pulse(): WARNING! Maximum of 16 points allowed, truncating points array.")
			num_points = 16
		
		# Error handling (exception) if malformed points.
		try:
			for i in range(0, num_points):
				current = points_array[i][0]
				pulse_width = points_array[i][1]
				#print("Point {}: {} mA {} us".format(i, current, pulse_width))
		except:
			print("custom_pulse: ERROR! Malformed points array, should be: [ (current0, pulse_width0), (current1, pulse_width1), ... ]")
			return

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

		rehamovelib.custom_pulse(self.rehamove, channel, original_length, c0, w0, c1, w1, c2, w2, c3, w3, c4, w4, c5, w5, c6, w6, c7, w7, c8, w8, c9, w9, c10, w10, c11, w11, c12, w12, c13, w13, c14, w14, c15, w15)

		#print("PYTHON custom_pulse {} {}, {} {} {} {} {} {} {} {} / {} {} {} {} {} {} {} {} / {} {} {} {} {} {} {} {} / {} {} {} {} {} {} {} {}".format(self.rehamove, channel, c0, w0, c1, w1, c2, w2, c3, w3, c4, w4, c5, w5, c6, w6, c7, w7, c8, w8, c9, w9, c10, w10, c11, w11, c12, w12, c13, w13, c14, w14, c15, w15))
		
	def battery(self):
		rehamovelib.battery(self.rehamove)

	def __del__(self):
		rehamovelib.close_port(self.rehamove)
