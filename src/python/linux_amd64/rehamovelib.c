#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "smpt_ll_client.h"

typedef struct {
    char port_name[64];
    Smpt_device device;
} Rehamove;

/*
Function declarations in this section.
*/
Rehamove * open_port(const char * port_name);
void close_port(Rehamove * r);
void pulse(Rehamove * r, char * channel, int current, int pulse_width);
void custom_pulse(Rehamove * r, char * channel, int num_points, float c0, int w0, float c1, int w1, float c2, int w2, float c3, int w3, float c4, int w4, float c5, int w5, float c6, int w6, float c7, int w7, float c8, int w8, float c9, int w9, float c10, int w10, float c11, int w11, float c12, int w12, float c13, int w13, float c14, int w14, float c15, int w15);
void battery(Rehamove * r);

/*
Actual implementation details below.
*/

Rehamove * open_port(const char * port_name) {
	Rehamove * r = (Rehamove *) calloc(1, sizeof(Rehamove));

	for (int i = 0; i < strlen(port_name); i++) {
		(r->port_name)[i] = *(port_name + i);
	}
	(r->port_name)[strlen(port_name)] = '\0';

	printf("open_port(): Created port_name %s\n", r->port_name);

	Smpt_device device = {0};
    int open_port_result = smpt_open_serial_port(&device, r->port_name);
    if (open_port_result == 0) {
        printf("open_port(): ERROR! Unable to connect to port %s.\n", r->port_name);
    }
    else {
        printf("open_port(): Successfully opened port.\n");
    }
    r->device = device;
	return r;
}

void close_port(Rehamove * r) {
	int result = smpt_close_serial_port(&(r->device));
	if (result == 0) {
		printf("close_port(): ERROR! Unable to close port %s !\n", r->port_name);
		return;
	} 
	printf("close_port(): Successfully closed port %s .\n", r->port_name);
	free(r);
    return;
}

void print_channel_config(Smpt_ll_channel_config * s) {

    printf("PRINTING CHANNEL CONFIG\n");
    printf("enable_stimulation: %d\n", s->enable_stimulation);
    printf("channel: %d\n", s->channel);
    printf("modify_demux: %d\n", s->modify_demux);
    printf("number_of_points: %d\n", s->number_of_points);
    printf("Smpt_Length_Points: %d\n", Smpt_Length_Points);
    printf("points array: ");
    for (int i = 0; i < Smpt_Length_Points; i++) {
        Smpt_point p = *(s->points + i);
        printf("(time %d float %f control_mode %d interpolation_mode %d) ", p.time, p.current, p.control_mode, p.interpolation_mode);
    }
    printf("\n");
    printf("Smpt_Length_Demux_Config: %d\n", Smpt_Length_Demux_Config);
    printf("demux_config array: ");
    for (int i = 0; i < Smpt_Length_Demux_Config; i++) {
        printf("(%d) ", *(s->demux_config + i));
    }
    printf("\n");
    printf("demux_length: %d\n", s->demux_length);
    printf("packet_number: %d\n", s->packet_number);
}

void pulse(Rehamove * r, char * channel, int current, int pulse_width) {

    uint8_t packet_number = 0;  /* The packet_number can be used for debugging purposes */
    Smpt_ll_init ll_init = {0};       /* Struct for ll_init command */
    Smpt_ll_channel_config ll_channel_config = {0};   /* Struct for ll_channel_config command */

    /* Clear ll_init struct and set the data */
    smpt_clear_ll_init(&ll_init);

    //print_channel_config(&ll_channel_config);

    ll_init.packet_number = packet_number;

    /* Send the ll_init command to stimulation unit */
    smpt_send_ll_init(&(r->device), &ll_init);

    packet_number++;

    /* Set the data */
    ll_channel_config.enable_stimulation = true;
    
    char lowercase[strlen(channel) + 1];
    for (int i = 0; i < strlen(channel); i++) {
        lowercase[i] = tolower(channel[i]);
    }
    lowercase[strlen(channel)] = '\0';

    int chosen_channel = Smpt_Channel_Blue;
    if (strncmp(lowercase, "red", strlen("red")) == 0) {
        chosen_channel = Smpt_Channel_Red;
    }
    else if (strncmp(lowercase, "blue", strlen("blue")) == 0) {
        chosen_channel = Smpt_Channel_Blue;
    }
    else if (strncmp(lowercase, "black", strlen("gray")) == 0) {
        chosen_channel = Smpt_Channel_Black;
    }

    ll_channel_config.channel = chosen_channel;  /* Use blue channel */
    ll_channel_config.number_of_points = 3;         /* Set the number of points*/
    ll_channel_config.packet_number = packet_number;

    /* Set the stimulation pulse */
    /* First point, current: 20 mA, positive, pulse width: 200 µs */
    ll_channel_config.points[0].current =  current;
    ll_channel_config.points[0].time    = pulse_width;

    /* Second point, pause 100 µs */
    ll_channel_config.points[1].time = pulse_width / 2;

    /* Third point, current: -20 mA, negative, pulse width: 200 µs */
    ll_channel_config.points[2].current = current * -1;
    ll_channel_config.points[2].time    = pulse_width;

    //print_channel_config(&ll_channel_config);

    /* Send the ll_channel_list command to the stimulation unit */
    smpt_send_ll_channel_config(&(r->device), &ll_channel_config);

    //print_channel_config(&ll_channel_config);

    packet_number++;

    /* Send the ll_stop command to the stimulation unit */
    smpt_send_ll_stop(&(r->device), packet_number);
    //printf("pulse(): Successfully finished.\n");
}

void custom_pulse(Rehamove * r, char * channel, int num_points, float c0, int w0, float c1, int w1, float c2, int w2, float c3, int w3, float c4, int w4, float c5, int w5, float c6, int w6, float c7, int w7, float c8, int w8, float c9, int w9, float c10, int w10, float c11, int w11, float c12, int w12, float c13, int w13, float c14, int w14, float c15, int w15) {

    //printf("C custom_pulse: %p %s, %f %d %f %d %f %d %f %d / %f %d %f %d %f %d %f %d / %f %d %f %d %f %d %f %d / %f %d %f %d %f %d %f %d", r, channel, c0, w0, c1, w1, c2, w2, c3, w3, c4, w4, c5, w5, c6, w6, c7, w7, c8, w8, c9, w9, c10, w10, c11, w11, c12, w12, c13, w13, c14, w14, c15, w15);

    uint8_t packet_number = 0;  /* The packet_number can be used for debugging purposes */
    Smpt_ll_init ll_init = {0};       /* Struct for ll_init command */
    Smpt_ll_channel_config ll_channel_config = {0};   /* Struct for ll_channel_config command */

    /* Clear ll_init struct and set the data */
    smpt_clear_ll_init(&ll_init);

    ll_init.packet_number = packet_number;

    /* Send the ll_init command to stimulation unit */
    smpt_send_ll_init(&(r->device), &ll_init);

    packet_number++;

    /* Set the data */
    ll_channel_config.enable_stimulation = true;
    
    char lowercase[strlen(channel) + 1];
    for (int i = 0; i < strlen(channel); i++) {
        lowercase[i] = tolower(channel[i]);
    }
    lowercase[strlen(channel)] = '\0';

    int chosen_channel = Smpt_Channel_Blue;
    if (strncmp(lowercase, "red", strlen("red")) == 0) {
        chosen_channel = Smpt_Channel_Red;
    }
    else if (strncmp(lowercase, "blue", strlen("blue")) == 0) {
        chosen_channel = Smpt_Channel_Blue;
    }
    else if (strncmp(lowercase, "black", strlen("gray")) == 0) {
        chosen_channel = Smpt_Channel_Black;
    }

    ll_channel_config.channel = chosen_channel;  /* Use blue channel */
    ll_channel_config.number_of_points = num_points;         /* Set the number of points*/
    ll_channel_config.packet_number = packet_number;

    /* Set the stimulation pulses */
    ll_channel_config.points[0].current = c0;
    ll_channel_config.points[0].time = w0;
    ll_channel_config.points[1].current = c1;
    ll_channel_config.points[1].time = w1;
    ll_channel_config.points[2].current = c2;
    ll_channel_config.points[2].time = w2;
    ll_channel_config.points[3].current = c3;
    ll_channel_config.points[3].time = w3;
    ll_channel_config.points[4].current = c4;
    ll_channel_config.points[4].time = w4;
    ll_channel_config.points[5].current = c5;
    ll_channel_config.points[5].time = w5;
    ll_channel_config.points[6].current = c6;
    ll_channel_config.points[6].time = w6;
    ll_channel_config.points[7].current = c7;
    ll_channel_config.points[7].time = w7;
    ll_channel_config.points[8].current = c8;
    ll_channel_config.points[8].time = w8;
    ll_channel_config.points[9].current = c9;
    ll_channel_config.points[9].time = w9;
    ll_channel_config.points[10].current = c10;
    ll_channel_config.points[10].time = w10;
    ll_channel_config.points[11].current = c11;
    ll_channel_config.points[11].time = w11;
    ll_channel_config.points[12].current = c12;
    ll_channel_config.points[12].time = w12;
    ll_channel_config.points[13].current = c13;
    ll_channel_config.points[13].time = w13;
    ll_channel_config.points[14].current = c14;
    ll_channel_config.points[14].time = w14;
    ll_channel_config.points[15].current = c15;
    ll_channel_config.points[15].time = w15;

    //print_channel_config(&ll_channel_config);

    /* Send the ll_channel_list command to the stimulation unit */
    smpt_send_ll_channel_config(&(r->device), &ll_channel_config);

    packet_number++;

    /* Send the ll_stop command to the stimulation unit */
    smpt_send_ll_stop(&(r->device), packet_number);
    //printf("custom_pulse(): Successfully finished.\n");
}

void battery(Rehamove * r) {
    // Annoyingly have to close and reopen a new port.
    smpt_close_serial_port(&(r->device));
    printf("close(): Successfully finished.\n");

    Smpt_device device = {0};
    int open_port_result = smpt_open_serial_port(&device, r->port_name);
    if (open_port_result == 0) {
        printf("open(): ERROR! Unable to connect to port %s.\n", r->port_name);
    }
    else {
        printf("open(): Successfully opened port.\n");
    }
    r->device = device;

    /* Send the call to get the battery status. Signature is:
    
     SMPT_API bool smpt_send_get_battery_status  (   Smpt_device *const      device,
        uint8_t     packet_number 
    )
    */
    uint8_t packet_number = 42;  /* The packet_number can be used for debugging purposes */
    bool send_result = smpt_send_get_battery_status(&(r->device), packet_number);

    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {

        counter += 1;
    }
        
    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);

    Smpt_get_battery_status_ack battery_ack;
    smpt_get_get_battery_status_ack(&(r->device), &battery_ack);

    printf("Battery life is at %d %%.\n", battery_ack.battery_level);
}
