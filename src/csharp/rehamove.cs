using UnityEngine;
using System;
using System.Linq;

namespace UnityRehamove {

	public class Rehamove {
		public RehamoveDevice rehamove;
		public int mode;

		public static string current_version = "v1.6";

		public static string[] channel0 = { "r", "red" };
		public static string[] channel1 = { "b", "blue" };
		public static string[] channel2 = { "g1", "gray1", "grey1", "black" };
		public static string[] channel3 = { "g2", "gray2", "grey2", "white" };

		public static int MODE_LOW_LEVEL = 0;
		public static int MODE_MID_LEVEL = 1;

		public Rehamove(string port_name) {
			rehamove = rehamovelib.open_port(port_name);
			mode = 0;
			if (rehamove == null) {
				Debug.Log("C# Rehamove init() ERROR!");
			} else {
				Debug.Log("C# Rehamove init() SUCCESS.");
			}
		}

		public string version() {
			string c_version = rehamovelib.get_version();
			Debug.Log("Rehamove Version: Python-side " + Rehamove.current_version.ToString() + ", C-side " + c_version);
			return Rehamove.current_version;
		}

		public int get_mode() {
			int result = rehamovelib.get_mode(rehamove);
			return result;			
		}

		public float get_current() {
			float result = rehamovelib.get_current(rehamove);
			return result;			
		}

		public int get_pulse_width() {
			int result = rehamovelib.get_pulse_width(rehamove);
			return result;			
		}

		public string info() {
			if (rehamove == null) {
				Debug.Log("C# Rehamove info() ERROR! Rehamove object does not exist.");
				return null;
			}
			int mode = get_mode();
			float current = get_current();
			int pulse_width = get_pulse_width();

			string output;
			if (mode == Rehamove.MODE_LOW_LEVEL) {
				output = String.Format("Rehamove device in low-level mode. Mid-level pulse is set to {0} mA and {1} us.", current, pulse_width);
			} else if (mode == Rehamove.MODE_MID_LEVEL) {
				output = String.Format("Rehamove device in mid-level mode. Mid-level pulse is set to {0} mA and {1} us.", current, pulse_width);
			} else {
				output = "Rehamove info() ERROR!";
			}

			return output;
		}

		public int get_channel(string channel) {
			int chosen_channel = 0; // Default
			if (channel0.Contains(channel)) {
				chosen_channel = 0;
			} else if (channel1.Contains(channel)) {
				chosen_channel = 1;
			} else if (channel2.Contains(channel)) {
				chosen_channel = 2;
			} else if (channel3.Contains(channel)) {
				chosen_channel = 3;
			}
			return chosen_channel;
		}

		public int get_channel(int channel) {
			if ((channel < 0) || (channel > 3)) {
				channel = 0; // Default
			}
			return channel;
		}
		
		public int pulse(string channel, float current, int pulse_width) {
			int converted_channel = get_channel(channel);
			return pulse(converted_channel, current, pulse_width);
		}

		public int pulse(int channel, float current, int pulse_width) {
			if (rehamove == null) {
				Debug.Log("C# Rehamove pulse() ERROR! Rehamove object does not exist.");
				return -1;
			}
			if (mode != MODE_LOW_LEVEL) {
				Debug.Log("C# Rehamove pulse() ERROR! Mode must be set to low-level.");
				return -1;
			}
			int result = rehamovelib.pulse(rehamove, channel, current, pulse_width);
			if (result != 0) {
				Debug.Log("C# Rehamove pulse() ERROR!");
				return -1;
			} else {
				Debug.Log("C# Rehamove pulse() sent.");
				return 0;
			}
		}

		public int battery() {
			if (rehamove == null) {
				Debug.Log("C# Rehamove battery() ERROR! Rehamove object does not exist.");
				return -1;
			}
			int result = rehamovelib.battery_request(rehamove);
			if (result != 0) {
				Debug.Log("C# Rehamove battery() ERROR!");
				return -1;
			} else {
				int battery_level = rehamovelib.get_battery(rehamove);
				Debug.Log("C# Rehamove battery(): " + battery_level.ToString() + "%");
				return battery_level;
			}
		}

		public int change_mode(int new_mode) {
			if (rehamove == null) {
				Debug.Log("C# Rehamove change_mode() ERROR! Rehamove object does not exist.");
				return -1;
			}
			int result = rehamovelib.change_mode(rehamove, new_mode);
			if (result != 0) {
				Debug.Log("C# Rehamove change_mode() ERROR!");
				return -1;
			} else {
				Debug.Log("C# Rehamove change_mode(): Changed mode to " + mode.ToString() + ".");
				mode = new_mode;
				return 0;
			}
		}

		public int set_pulse(float current, int pulse_width) {
			if (rehamove == null) {
				Debug.Log("C# Rehamove set_pulse() ERROR! Rehamove object does not exist.");
				return -1;
			}
			int result = rehamovelib.set_pulse_data(rehamove, current, pulse_width);
			if (result != 0) {
				Debug.Log("C# Rehamove set_pulse() ERROR!");
				return -1;
			} else {
				Debug.Log("C# Rehamove set_pulse(): Set pulse current to " + current.ToString() + " and pulse width to " + pulse_width.ToString() + ".");
				return 0;
			}
		}

		public int run(string channel, float period, int total_milliseconds) {
			int chosen_channel = get_channel(channel);
			return run(chosen_channel, period, total_milliseconds);
		}

		public int run(int channel, float period, int total_milliseconds) {
			if (rehamove == null) {
				Debug.Log("C# Rehamove run() ERROR! Rehamove object does not exist.");
				return -1;
			}
			if (mode != MODE_MID_LEVEL) {
				Debug.Log("C# Rehamove run() ERROR! Mode must be set to mid-level.");
				return -1;
			}
			int result = rehamovelib.run(rehamove, channel, period, total_milliseconds);
			if (result != 0) {
				Debug.Log("C# Rehamove run() ERROR!");
				return -1;
			} else {
				Debug.Log("C# Rehamove run(): Completed.");
				return 0;
			}
		}

		public int start(string channel, float period) {
			int chosen_channel = get_channel(channel);
			return start(chosen_channel, period);
		}

		public int start(int channel, float period) {
			if (rehamove == null) {
				Debug.Log("C# Rehamove start() ERROR! Rehamove object does not exist.");
				return -1;
			}
			if (mode != MODE_MID_LEVEL) {
				Debug.Log("C# Rehamove start() ERROR! Mode must be set to mid-level.");
				return -1;
			}
			int result = rehamovelib.midlevel_start(rehamove, channel, period);
			if (result != 0) {
				Debug.Log("C# Rehamove start() ERROR!");
				return -1;
			} else {
				Debug.Log("C# Rehamove start(): Completed.");
				return 0;
			}
		}
		
		public int update() {
			if (rehamove == null) {
				Debug.Log("C# Rehamove update() ERROR! Rehamove object does not exist.");
				return -1;
			}
			if (mode != MODE_MID_LEVEL) {
				Debug.Log("C# Rehamove update() ERROR! Mode must be set to mid-level.");
				return -1;
			}
			int result = rehamovelib.midlevel_update(rehamove);
			if (result != 0) {
				Debug.Log("C# Rehamove update() ERROR!");
				return -1;
			} else {
				Debug.Log("C# Rehamove update(): Completed.");
				return 0;
			}
		}

		public int end() {
			if (rehamove == null) {
				Debug.Log("C# Rehamove end() ERROR! Rehamove object does not exist.");
				return -1;
			}
			if (mode != MODE_MID_LEVEL) {
				Debug.Log("C# Rehamove end() ERROR! Mode must be set to mid-level.");
				return -1;
			}
			int result = rehamovelib.midlevel_end(rehamove);
			if (result != 0) {
				Debug.Log("C# Rehamove end() ERROR!");
				return -1;
			} else {
				Debug.Log("C# Rehamove end(): Completed.");
				return 0;
			}
		}

		public int close() {
			if (rehamove == null) {
				Debug.Log("C# RehamoveDevice close() ERROR! RehamoveDevice object does not exist.");
				return -1;
			}
			int result = rehamovelib.close_port(rehamove);
			if (result != 0) {
				Debug.Log("C# RehamoveDevice close() ERROR!");
				return -1;
			} else {
				Debug.Log("C# RehamoveDevice close() sent.");
				return 0;
			}
		}

		~Rehamove() {
			Debug.Log("I'm being destroyed!");
		}
	}
}