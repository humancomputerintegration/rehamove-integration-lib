#include "smpt_ll_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)
#include <unistd.h> /* Not for Windows */
#endif

#define VERSION_NUMBER "v1.5"
#define TIMEOUT_COUNTER 10000000

typedef struct {
    char port_name[64];
    Smpt_device device;
    int battery;
} Rehamove;

char * get_version();
Rehamove * open_port(const char * port_name);
int close_port(Rehamove * r);
int pulse(Rehamove * r, int channel, float current, int pulse_width);
int get_battery(Rehamove * r);
int battery_request(Rehamove * r);
int custom_pulse(Rehamove * r, int channel, int num_points, float c0, int w0, float c1, int w1, float c2, int w2, float c3, int w3, float c4, int w4, float c5, int w5, float c6, int w6, float c7, int w7, float c8, int w8, float c9, int w9, float c10, int w10, float c11, int w11, float c12, int w12, float c13, int w13, float c14, int w14, float c15, int w15);

void print_device(Smpt_device d, const char * filename);
void error_callback(const char * message) {
    printf("ERROR CALLBACK: %s\n", message);
}

/* USER-FACING FUNCTIONS */

char * get_version() {
    return VERSION_NUMBER;
}

Rehamove * open_port(const char * port_name) {
    //smpt_init_error_callback(&error_callback); //We disabled the callback print for MacOS because this was generating 1k+ errors every time.

    uint8_t packet_number = 1;  /* The packet_number can be used for debugging purposes */

    Rehamove * r = (Rehamove *) calloc(1, sizeof(Rehamove));

    for (int i = 0; i < strlen(port_name); i++) {
        (r->port_name)[i] = *(port_name + i);
    }
    (r->port_name)[strlen(port_name)] = '\0';
    r->battery = -1;

    Smpt_device device = {0};
    r->device = device;
    bool open_port_result = smpt_open_serial_port(&(r->device), port_name);
    if (!open_port_result) {
        printf("open_port() ERROR: Opening connection to port %s failed!\n", port_name);
        free(r);
        return NULL;
    }

    Smpt_ll_init ll_init = {0};       /* Struct for ll_init command */
    /* Clear ll_init struct and set the data */
    smpt_clear_ll_init(&ll_init);
    ll_init.packet_number = packet_number;

    /* Send the ll_init command to stimulation unit */
    bool ll_init_result = smpt_send_ll_init(&(r->device), &ll_init);
    if (!ll_init_result) {
        printf("open_port() ERROR: Sending device initialization message failed!\n");
        free(r);
        return NULL;
    }

    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("open_port() ERROR: Receiving device initialization message timed out!\n");
            free(r);
            return NULL;
        }
        counter += 1;
    }   
    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ll_Init_Ack)) {
        printf("open_port() ERROR: Unsuccessful device initialization response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ll_Init_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        free(r);
        return NULL;
    }

    Smpt_ll_init_ack init_ack;
    smpt_get_ll_init_ack(&(r->device), &init_ack);
    printf("open_port() SUCCESS: Connected to port %s and initialized device.\n", port_name);
    return r;
}

int pulse(Rehamove * r, int channel, float current, int pulse_width) {
    if (r == NULL) {
        printf("pulse() ERROR: No Rehamove object found!\n");
        return 1;
    }

    uint8_t packet_number = 1;

    Smpt_ll_channel_config ll_channel_config = {0};   /* Struct for ll_channel_config command */
    /* Set the data */
    ll_channel_config.enable_stimulation = true;
    ll_channel_config.channel = channel;
    ll_channel_config.number_of_points = 3;         /* Set the number of points*/
    ll_channel_config.packet_number = packet_number;
    /* Set the stimulation pulse */
    ll_channel_config.points[0].current = current;
    ll_channel_config.points[0].time    = pulse_width;
    ll_channel_config.points[1].time    = pulse_width / 2;
    ll_channel_config.points[2].current = current * -1;
    ll_channel_config.points[2].time    = pulse_width;

    /* Send the ll_channel_list command to the stimulation unit */
    bool ll_config_result = smpt_send_ll_channel_config(&(r->device), &ll_channel_config);
    if (!ll_config_result) {
        printf("pulse() ERROR: Pulse command not sent!\n");
        return 1;
    }

    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("pulse() ERROR: Receiving pulse response timed out!\n");
            return 1;
        }
        counter += 1;
    }

    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ll_Channel_Config_Ack)) {
        // Common error situation -> electrode error (e.g. electrode not connected).
        if (ack.result == Smpt_Result_Electrode_Error) {
            printf("pulse() ERROR: Unsuccessful pulse response - electrode error! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ll_Channel_Config_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
            return 1;
        }
        // Default error message -> specify the code.
        printf("pulse() ERROR: Unsuccessful pulse response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ll_Channel_Config_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    } else {
        Smpt_ll_channel_config_ack channel_config_ack;
        smpt_get_ll_channel_config_ack(&(r->device), &channel_config_ack);
    }
    return 0;
}

int custom_pulse(Rehamove * r, int channel, int num_points, float c0, int w0, float c1, int w1, float c2, int w2, float c3, int w3, float c4, int w4, float c5, int w5, float c6, int w6, float c7, int w7, float c8, int w8, float c9, int w9, float c10, int w10, float c11, int w11, float c12, int w12, float c13, int w13, float c14, int w14, float c15, int w15) {

    if (r == NULL) {
        printf("custom_pulse() ERROR: No Rehamove object found!\n");
        return 1;
    }

    uint8_t packet_number = 2;
    Smpt_ll_channel_config ll_channel_config = {0};   /* Struct for ll_channel_config command */
    /* Set the data */
    ll_channel_config.enable_stimulation = true;
    ll_channel_config.channel = channel;
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

    /* Send the ll_channel_list command to the stimulation unit */
    bool ll_config_result = smpt_send_ll_channel_config(&(r->device), &ll_channel_config);
    if (!ll_config_result) {
        printf("custom_pulse() ERROR: Pulse command not sent!\n");
        return 1;
    }

    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("custom_pulse() ERROR: Receiving pulse response timed out!\n");
            return 1;
        }
    }

    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ll_Channel_Config_Ack)) {
        // Common error situation -> electrode error (e.g. electrode not connected).
        if (ack.result == Smpt_Result_Electrode_Error) {
            printf("custom_pulse() ERROR: Unsuccessful pulse response - electrode error! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ll_Channel_Config_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
            return 1;
        }
        // Default error message -> specify the code.
        printf("custom_pulse() ERROR: Unsuccessful pulse response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ll_Channel_Config_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    } else {
        Smpt_ll_channel_config_ack channel_config_ack;
        smpt_get_ll_channel_config_ack(&(r->device), &channel_config_ack);
    }
    return 0;
}

int close_port(Rehamove * r) {
    if (r == NULL) {
        printf("close_port() ERROR: No Rehamove object found!\n");
        return 1;
    }

    uint8_t packet_number = 1;
    bool ll_stop_result = smpt_send_ll_stop(&(r->device), packet_number);
    if (!ll_stop_result) {
        printf("close_port() ERROR: Stopping device request not sent!\n");
        return 1;
    }

    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("close_port() ERROR: Receiving device stop response timed out!\n");
            return 1;
        }
    }

    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);
    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ll_Stop_Ack)) {
        // Default error message -> specify the code.
        printf("close_port() ERROR: Unsuccessful device stop response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ll_Stop_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    }

    bool close_port_result = smpt_close_serial_port(&(r->device));
    if (!close_port_result) {
        printf("close_port() ERROR! Close port request not sent!\n");
        return 1;
    }
    free(r);
    printf("close_port() SUCCESS: Stopped device and closed port successfully.\n");
    return 0;
}

int get_battery(Rehamove * r) {
    if (r == NULL) {
        printf("get_battery() ERROR: No Rehamove object found!\n");
        return -1;
    }
    return r->battery;
}

int battery_request(Rehamove * r) {
    if (r == NULL) {
        printf("battery_request() ERROR: No Rehamove object found!\n");
        return 1;
    }
    uint8_t packet_number = 42;
    bool battery_result = smpt_send_get_battery_status(&(r->device), packet_number);
    if (!battery_result) {
        printf("battery_result() ERROR: Battery request not sent!\n");
        return 1;
    }
    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("battery_result() ERROR: Receiving battery response timed out!\n");
            return 1;
        }
    }

    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Get_Battery_Status_Ack)) {
        // Default error message -> specify the code.
        printf("battery_result() ERROR: Unsuccessful battery response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Get_Battery_Status_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    } else {
        Smpt_get_battery_status_ack battery_ack;
        smpt_get_get_battery_status_ack(&(r->device), &battery_ack);
        r->battery = battery_ack.battery_level;
    }
    return 0;
}


/* FOR DEBUGGING */

void print_device(Smpt_device d, const char * filename) {

    FILE * file = fopen(filename, "w+, css=UTF-8");
    if (file == NULL) {
        printf("Could not print to file %s\n", filename);
        return;
    }

    fprintf(file, "PRINTING DEVICE.\n");
    fprintf(file, "packet_length %d\n", d.packet_length);
    fprintf(file, "packet array of size %d: ", Smpt_Length_Max_Packet_Size);
    for (int i = 0; i < Smpt_Length_Max_Packet_Size; i++) {
        fprintf(file, "%d ", (d.packet)[i]);
    }
    fprintf(file, "\n");
    fprintf(file, "cmd_list c:\n");
    Smpt_cmd_list c = d.cmd_list;
        fprintf(file, "c.acks_length %d\n", c.acks_length);
        fprintf(file, "c.acks_current_index %d\n", c.acks_current_index);
        fprintf(file, "c.acks array of size %d: ( ", Smpt_Length_Number_Of_Acks);
        for (int i = 0; i < Smpt_Length_Number_Of_Acks; i++) {
            Smpt_ack a = *(c.acks + i);
            fprintf(file, "[packet %d command %d result %d] ", a.packet_number, a.command_number, a.result);
        }
        fprintf(file, ")\n");
        fprintf(file, "c.requests_current_index %d\n", c.requests_current_index);
        fprintf(file, "c.requests_expected_index %d\n", c.requests_expected_index);
        fprintf(file, "c.number_of_expected %d\n", c.number_of_expected);
        fprintf(file, "c.requests array of size %d: ( ", Smpt_Length_Number_Of_Acks);
        for (int i = 0; i < Smpt_Length_Number_Of_Acks; i++) {
            Smpt_cmd a = *(c.requests + i);
            fprintf(file, "[packet %d command %d] ", a.packet_number, a.command_number);
        }
        fprintf(file, ")\n");
        fprintf(file, "c.new_ack_available %d\n", c.new_ack_available);
    //fprintf(file, "serial_port_handle %p\n", d.serial_port_handle_);
    fprintf(file, "current_packet_number %d\n", d.current_packet_number);
    fprintf(file, "serial_port_name array of size %d: ( ", Smpt_Length_Serial_Port_Chars);
    for (int i = 0; i < Smpt_Length_Serial_Port_Chars; i++) {
        fprintf(file, "%c ", *(d.serial_port_name + i));
    }
    fprintf(file, ")\n");
    fprintf(file, "packet_input_buffer p:\n");
    Packet_input_buffer p = d.packet_input_buffer;
        fprintf(file, "p.buffer %p\n", p.buffer);
        fprintf(file, "p.buffer_state %p\n", p.buffer_state);
        fprintf(file, "p.write_row_length_count %d\n", p.write_row_length_count);
        fprintf(file, "p.write_row_count %d\n", p.write_row_count);
        fprintf(file, "p.read_row_count %d\n", p.read_row_count);
        fprintf(file, "p.ignore_next_byte %d\n", p.ignore_next_byte);
        fprintf(file, "p.number_of_rows %d\n", p.number_of_rows);
        fprintf(file, "p.row_length %d\n", p.row_length);
    fprintf(file, "packet_input_buffer_data array of size (%d * %d): ( ", Smpt_Length_Packet_Input_Buffer_Rows, Smpt_Length_Max_Packet_Size);
    for (int i = 0; i < Smpt_Length_Packet_Input_Buffer_Rows * Smpt_Length_Max_Packet_Size; i++) {
        fprintf(file, "%d ", *(d.packet_input_buffer_data + i));
    }
    fprintf(file, ")\n");
    fprintf(file, "packet_input_buffer_state array of size %d: ( ", Smpt_Length_Packet_Input_Buffer_Rows);
    for (int i = 0; i < Smpt_Length_Packet_Input_Buffer_Rows; i++) {
        fprintf(file, "%d ", *(d.packet_input_buffer_state + i));
    }
    fprintf(file, ")\n");
    fprintf(file, "END PRINT DEVICE.\n");
    fclose(file);
}
