#include "smpt_ll_client.h"

void smpt_single_pulse(const char *port_name, int channel, int current, int pulse_width);

int main(void)
{
    /* EDIT: Change to the virtual com port of your device */
    const char *port_name = "/dev/ttyUSB0";

    // For loop for the scope.
    /*for (int i = 0; i < 100000; i++) {
    	smpt_single_pulse(port_name, 1, 1, 200);
    }*/
    smpt_single_pulse(port_name, 1, 1, 200);
    return 0;
}

void smpt_single_pulse(const char *port_name, int channel, int current, int pulse_width)
{
    uint8_t packet_number = 0;  /* The packet_number can be used for debugging purposes */
    Smpt_ll_init ll_init = {0};       /* Struct for ll_init command */
    Smpt_ll_channel_config ll_channel_config = {0};   /* Struct for ll_channel_config command */

    Smpt_device device = {0};
    smpt_open_serial_port(&device, port_name);

    /* Clear ll_init struct and set the data */
    smpt_clear_ll_init(&ll_init);
    ll_init.packet_number = packet_number;

    /* Send the ll_init command to stimulation unit */
    smpt_send_ll_init(&device, &ll_init);

    packet_number++;

    /* Set the data */
    ll_channel_config.enable_stimulation = true;
    ll_channel_config.channel = channel;  /* Use blue channel */
    ll_channel_config.number_of_points = 3;         /* Set the number of points*/
    ll_channel_config.packet_number = packet_number;

    /* Set the stimulation pulse */
    /* First point, current: 20 mA, positive, pulse width: 200 µs */
    ll_channel_config.points[0].current =  current;
    ll_channel_config.points[0].time    = pulse_width;

    /* Second point, pause 100 µs */
    ll_channel_config.points[1].time = pulse_width;

    /* Third point, current: -20 mA, negative, pulse width: 200 µs */
    ll_channel_config.points[2].current = -current;
    ll_channel_config.points[2].time    = pulse_width;

    /* Send the ll_channel_list command to the stimulation unit */
    smpt_send_ll_channel_config(&device, &ll_channel_config);

    packet_number++;

    /* Send the ll_stop command to the stimulation unit */
    smpt_send_ll_stop(&device, packet_number);

    smpt_close_serial_port(&device);
}
