using UnityEngine;
namespace UnityRehamove {
	public class Rehamove {
		private RehamoveDevice rehamoveDevice;

		public Rehamove(string port_name) {
			Debug.Log("Rehamove init()");
			rehamoveDevice = rehamovelib.open_port(port_name);
		}

		public int add(int x, int y) {
			Debug.Log("Rehamove add()");
			return rehamovelib.add(x, y);
		}

		public void pulse(string channel, int current, int pulse_width) {
			Debug.Log("Rehamove pulse()");
			rehamovelib.pulse(rehamoveDevice, channel, current, pulse_width);
		}

		public void close() {
			Debug.Log("Rehamove close()");
			rehamovelib.close_port(rehamoveDevice);
		}

		// void OnApplicationQuit()
	 //    {
	 //        Debug.Log("Application ending after " + Time.time + " seconds");
		// 	rehamovelib.pulse(rehamoveDevice, "blue", 5, 100);
	 //    }

		~Rehamove() {
			Debug.Log("I'm being destroyed! Add: " + rehamovelib.add(2, 3).ToString());
			// rehamovelib.close_port(rehamoveDevice);
			// Debug.Log("done closing port");
		}
	}
}