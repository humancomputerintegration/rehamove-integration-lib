#include "smpt_ll_client.h"
#include "smpt_ml_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)
#include <unistd.h> /* Timer for Linux */
#elif defined(_WIN32) 
#include <Windows.h> /* Timer for Windows */
#endif

#define VERSION_NUMBER "v1.6"

#define TIMEOUT_COUNTER 10000000

#define MODE_LOW_LEVEL 0
#define MODE_MID_LEVEL 1

typedef struct {
    Smpt_device device;
    int battery;
    int mode;
    float current;
    uint16_t pulse_width;
} RehamoveDevice;

/* FUNCTION DECLARATIONS */

// Opening and closing the connection.
RehamoveDevice * open_port(const char * port_name);
int close_port(RehamoveDevice * r);

// Low-level functionality (the default) -> sending individual pulses.
int initialize_low_level(RehamoveDevice * r);
int stop_low_level(RehamoveDevice * r);
int pulse(RehamoveDevice * r, int channel, float current, int pulse_width);
int custom_pulse(RehamoveDevice * r, int channel, int num_points, float c0, int w0, float c1, int w1, float c2, int w2, float c3, int w3, float c4, int w4, float c5, int w5, float c6, int w6, float c7, int w7, float c8, int w8, float c9, int w9, float c10, int w10, float c11, int w11, float c12, int w12, float c13, int w13, float c14, int w14, float c15, int w15);

// Mid-level functionality -> setting a recurring pulse.
int change_mode(RehamoveDevice * r, int mode);
int set_pulse_data(RehamoveDevice * r, float current, int pulse_width);
int run(RehamoveDevice * r, int channel, float period, int total_milliseconds);
int midlevel_start(RehamoveDevice * r, int channel, float period);
int midlevel_update(RehamoveDevice * r);
int midlevel_end(RehamoveDevice * r);

// Global functionality -> can be called in any mode.
char * get_version();
int get_battery(RehamoveDevice * r);
int get_mode(RehamoveDevice * r);
float get_current(RehamoveDevice * r);
int get_pulse_width(RehamoveDevice * r);
int battery_request(RehamoveDevice * r);

// Debugging functions -> not intended for users to use.
void print_device(Smpt_device d, const char * filename);
void error_callback(const char * message) {
    printf("ERROR CALLBACK: %s\n", message);
}

/* FUNCTION DEFINITIONS */

RehamoveDevice * open_port(const char * port_name) {
    
    //smpt_init_error_callback(&error_callback);

    RehamoveDevice * r = (RehamoveDevice *) calloc(1, sizeof(RehamoveDevice));

    // Set the defaults.
    r->battery = -1;
    r->mode = -1;
    r->current = 0;
    r->pulse_width = 0;

    Smpt_device device = {0};
    r->device = device;

    bool open_port_result = smpt_open_serial_port(&(r->device), port_name);
    if (!open_port_result) {
        printf("open_port() ERROR: Opening connection to port %s failed!\n", port_name);
        free(r);
        return NULL;
    }

    // Default is low-level mode, so we will start with that.
    int initialize_low_level_result = initialize_low_level(r);
    if (initialize_low_level_result) {
        printf("open_port() ERROR: Unable to initialize low-level stimulation!\n");
        free(r);
        return NULL;
    }

    printf("open_port() SUCCESS: Connected to port %s and initialized device.\n", port_name);
    return r;
}

int close_port(RehamoveDevice * r) {
    if (r == NULL) {
        printf("close_port() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }

    // Stop the low-level stimulation, if it is still active.
    if (r->mode == MODE_LOW_LEVEL) {
        int stop_low_level_result = stop_low_level(r);
        if (stop_low_level_result) {
            printf("close_port() ERROR: Unable to stop low-level stimulation!\n");
            return 1;
        }
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

int initialize_low_level(RehamoveDevice * r) {
    if (r == NULL) {
        printf("initialize_low_level() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }
    if (r->mode == MODE_LOW_LEVEL) {
        printf("initialize_low_level() ERROR: Low-level mode already initialized.\n");
        return 0;
    }

    uint8_t packet_number = 1;  
    Smpt_ll_init ll_init = {0};

    smpt_clear_ll_init(&ll_init);
    ll_init.packet_number = packet_number;

    /* Send the ll_init command to stimulation unit */
    bool ll_init_result = smpt_send_ll_init(&(r->device), &ll_init);
    if (!ll_init_result) {
        printf("initialize_low_level() ERROR: Sending device initialization message failed!\n");
        return 1;
    }

    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("initialize_low_level() ERROR: Receiving device initialization message timed out!\n");
            return 1;
        }
        counter += 1;
    }   

    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ll_Init_Ack)) {
        if (ack.result == Smpt_Result_Not_Initialized_Error) {
            printf("initialize_low_level() ERROR: Unsuccessful device initialization response, midlevel could be active! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ll_Init_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
            int end_midlevel_result = midlevel_end(r);
            return 1;
        }
        // Default error message -> specify the code.
        printf("initialize_low_level() ERROR: Unsuccessful device initialization response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ll_Init_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    } else {
        Smpt_ll_init_ack init_ack;
        smpt_get_ll_init_ack(&(r->device), &init_ack);
    }

    // After initializing the low-level stimulation, set the mode in our RehamoveDevice struct.
    r->mode = MODE_LOW_LEVEL;

    printf("initialize_low_level() SUCCESS: Device successfully initialized low-level stimulation.\n");
    return 0;
}

int stop_low_level(RehamoveDevice * r) {
    if (r == NULL) {
        printf("stop_low_level() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }
    if (r->mode == MODE_MID_LEVEL) {
        printf("stop_low_level() ERROR: Low-level stimulation already stopped.\n");
        return 0;
    }

    uint8_t packet_number = 1;
    bool ll_stop_result = smpt_send_ll_stop(&(r->device), packet_number);
    if (!ll_stop_result) {
        printf("stop_low_level() ERROR: Stopping low-level stimulation request not sent!\n");
        return 1;
    }

    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("stop_low_level() ERROR: Receiving low-level stimulation stop response timed out!\n");
            return 1;
        }
    }

    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ll_Stop_Ack)) {
        // Default error message -> specify the code.
        printf("stop_low_level() ERROR: Unsuccessful low-level stimulation stop response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ll_Stop_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    }

    // After stopping the low-level stimulation, set the mode in our RehamoveDevice struct.
    r->mode = MODE_MID_LEVEL;

    printf("stop_low_level() SUCCESS: Device successfully stopped low-level stimulation.\n");
    return 0;
}


int pulse(RehamoveDevice * r, int channel, float current, int pulse_width) {
    if (r == NULL) {
        printf("pulse() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }
    if (r->mode != MODE_LOW_LEVEL) {
        printf("pulse() ERROR: Not in low-level stimulation mode.\n");
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

int custom_pulse(RehamoveDevice * r, int channel, int num_points, float c0, int w0, float c1, int w1, float c2, int w2, float c3, int w3, float c4, int w4, float c5, int w5, float c6, int w6, float c7, int w7, float c8, int w8, float c9, int w9, float c10, int w10, float c11, int w11, float c12, int w12, float c13, int w13, float c14, int w14, float c15, int w15) {

    if (r == NULL) {
        printf("custom_pulse() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }
    if (r->mode != MODE_LOW_LEVEL) {
        printf("pulse() ERROR: Not in low-level stimulation mode.\n");
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


int change_mode(RehamoveDevice * r, int mode) {
    if (r == NULL) {
        printf("change_mode() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }

    if (mode == MODE_LOW_LEVEL) {
        if (r->mode == MODE_LOW_LEVEL) {
            printf("change_mode() ERROR: Low-level mode already initialized.\n");
            return 1;
        }
        int initialize_low_level_result = initialize_low_level(r);
        if (initialize_low_level_result) {
            printf("change_mode() ERROR: Unable to change to low-level mode!\n");
            return 1;
        }
        printf("change_mode() SUCCESS: Changed to low-level mode.\n");
        return 0;
    }

    else if (mode == MODE_MID_LEVEL) {
        if (r->mode == MODE_MID_LEVEL) {
            printf("change_mode() ERROR: Mid-level mode already initialized.\n");
            return 1;
        }
        int stop_low_level_result = stop_low_level(r);
        if (stop_low_level_result) {
            printf("change_mode() ERROR: Unable to change to mid-level mode!\n");
            return 1;
        }
        printf("change_mode() SUCCESS: Changed to mid-level mode.\n");
        return 0;
    }

    else {
        printf("change_mode() ERROR: Invalid mode specified!\n");
        return 1;
    }
}


int set_pulse_data(RehamoveDevice * r, float current, int pulse_width) {
    if (r == NULL) {
        printf("set_pulse_data() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }
    r->current = current;
    r->pulse_width = pulse_width;
    printf("set_pulse_data(): Set RehamoveDevice struct pulse to current %0.3f pulse_width %d\n", r->current, r->pulse_width);
    return 0;
}


int get_pulse_data(RehamoveDevice * r) {
    if (r == NULL) {
        printf("get_pulse_data() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }
    printf("get_pulse_data(): current %0.3f pulse_width %d\n", r->current, r->pulse_width);
    return 0;
}


int run(RehamoveDevice * r, int channel, float period, int total_milliseconds) {
    if (r == NULL) {
        printf("run() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }
    int seconds = total_milliseconds / 1000;
    int remainder = total_milliseconds % 1000;
    printf("total_milliseconds %d seconds %d remainder %d\n", total_milliseconds, seconds, remainder);

    Smpt_ml_init ml_init = {0};   
    smpt_clear_ml_init(&ml_init);
    
    bool ml_init_result = smpt_send_ml_init(&(r->device), &ml_init);
    if (!ml_init_result) {
        printf("ml_init() ERROR: Sending device mid-level initialization message failed!\n");
        return 1;
    }

    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("ml_init() ERROR: Receiving device mid-level initialization message timed out!\n");
            return 1;
        }
        counter += 1;
    }   

    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ml_Init_Ack)) {
        // Default error message -> specify the code.
        printf("ml_init() ERROR: Unsuccessful device mid-level initialization response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ml_Init_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    }

    Smpt_ml_update ml_update = {0};
    smpt_clear_ml_update(&ml_update);
    ml_update.enable_channel[channel] = true;
    ml_update.channel_config[channel].number_of_points = 3;
    ml_update.channel_config[channel].ramp = 0;
    ml_update.channel_config[channel].period = period;
    /* Set the stimulation pulse */
    ml_update.channel_config[channel].points[0].current = r->current;
    ml_update.channel_config[channel].points[0].time    = r->pulse_width;
    ml_update.channel_config[channel].points[1].time    = (r->pulse_width) / 2;
    ml_update.channel_config[channel].points[2].current = (r->current) * -1;
    ml_update.channel_config[channel].points[2].time    = r->pulse_width;
    
    bool ml_update_result = smpt_send_ml_update(&(r->device), &ml_update);
    if (!ml_update_result) {
        printf("ml_update_result() ERROR: Sending device mid-level update message failed!\n");
        return 1;
    }

    counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("ml_update_result() ERROR: Receiving device mid-level update message timed out!\n");
            return 1;
        }
        counter += 1;
    }   

    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ml_Update_Ack)) {
        // Default error message -> specify the code.
        printf("ml_update_result() ERROR: Unsuccessful device mid-level update response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ml_Update_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    }

    Smpt_ml_get_current_data ml_get_current_data = {0};
    ml_get_current_data.data_selection[Smpt_Ml_Data_Stimulation] = true;

    for (int i = 0; i <= seconds; i++) { 
        // Every second, we send a keep-alive update. We must always start with at least one.
        bool keep_alive_result = smpt_send_ml_get_current_data(&(r->device), &ml_get_current_data);
        if (!keep_alive_result) {
            printf("keep_alive_result() ERROR: Sending device alive message failed!\n");
            return 1;
        }

        counter = 0;
        while (!smpt_new_packet_received(&(r->device))) {
            if (counter > TIMEOUT_COUNTER) {
                printf("keep_alive_result() ERROR: Receiving device alive message timed out!\n");
                return 1;
            }
            counter += 1;
        }   
        
        smpt_last_ack(&(r->device), &ack);

        if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ml_Get_Current_Data_Ack)) {
            // Default error message -> specify the code.
            printf("keep_alive_result() ERROR: Unsuccessful device alive response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ml_Get_Current_Data_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
            return 1;
        }

        if (i == seconds) {
            break;
        }
        
        #if defined(__linux__)
        usleep(1000000);
        #elif defined(_WIN32) 
        Sleep(1000);
        #endif
    }

    // Before sending the stop message, wait for the remainder of milliseconds.
    #if defined(__linux__)
    usleep(1000 * remainder);
    #elif defined(_WIN32) 
    Sleep(remainder);
    #endif

    bool ml_stop_result = smpt_send_ml_stop(&(r->device), smpt_packet_number_generator_next(&(r->device)));
    if (!ml_stop_result) {
        printf("ml_stop_result() ERROR: Sending device stop message failed!\n");
        return 1;
    }

    counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("ml_stop_result() ERROR: Receiving device stop message timed out!\n");
            return 1;
        }
        counter += 1;
    }   
    
    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ml_Stop_Ack)) {
        // Default error message -> specify the code.
        printf("ml_stop_result() ERROR: Unsuccessful device stop response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ml_Stop_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    }

    printf("run() SUCCESS: Ran pulses of %0.2f mA and %d us on a period of %0.2f us for a total of %d ms.\n", r->current, r->pulse_width, period, total_milliseconds);
    return 0;
}


int midlevel_start(RehamoveDevice * r, int channel, float period) {
    if (r == NULL) {
        printf("midlevel_start() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }

    Smpt_ml_init ml_init = {0};   
    smpt_clear_ml_init(&ml_init);
    
    bool ml_init_result = smpt_send_ml_init(&(r->device), &ml_init);
    if (!ml_init_result) {
        printf("ml_init() ERROR: Sending device mid-level initialization message failed!\n");
        return 1;
    }

    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("ml_init() ERROR: Receiving device mid-level initialization message timed out!\n");
            return 1;
        }
        counter += 1;
    }   

    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ml_Init_Ack)) {
        // Default error message -> specify the code.
        printf("ml_init() ERROR: Unsuccessful device mid-level initialization response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ml_Init_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    }

    Smpt_ml_update ml_update = {0};
    smpt_clear_ml_update(&ml_update);
    ml_update.enable_channel[channel] = true;
    ml_update.channel_config[channel].number_of_points = 3;
    ml_update.channel_config[channel].ramp = 0;
    ml_update.channel_config[channel].period = period;
    /* Set the stimulation pulse */
    ml_update.channel_config[channel].points[0].current = r->current;
    ml_update.channel_config[channel].points[0].time    = r->pulse_width;
    ml_update.channel_config[channel].points[1].time    = (r->pulse_width) / 2;
    ml_update.channel_config[channel].points[2].current = (r->current) * -1;
    ml_update.channel_config[channel].points[2].time    = r->pulse_width;
    
    bool ml_update_result = smpt_send_ml_update(&(r->device), &ml_update);
    if (!ml_update_result) {
        printf("ml_update_result() ERROR: Sending device mid-level update message failed!\n");
        return 1;
    }

    counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("ml_update_result() ERROR: Receiving device mid-level update message timed out!\n");
            return 1;
        }
        counter += 1;
    }   

    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ml_Update_Ack)) {
        // Default error message -> specify the code.
        printf("ml_update_result() ERROR: Unsuccessful device mid-level update response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ml_Update_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    }

    int keep_alive_result = midlevel_update(r);
    if (keep_alive_result) {
        printf("midlevel_start() ERROR: Unsuccessful keep alive.\n");
        return 1;
    }
    return 0;
}


int midlevel_update(RehamoveDevice * r) {
    if (r == NULL) {
        printf("midlevel_update() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }

    Smpt_ml_get_current_data ml_get_current_data = {0};
    ml_get_current_data.data_selection[Smpt_Ml_Data_Stimulation] = true;

    bool keep_alive_result = smpt_send_ml_get_current_data(&(r->device), &ml_get_current_data);
    if (!keep_alive_result) {
        printf("keep_alive_result() ERROR: Sending device alive message failed!\n");
        return 1;
    }

    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("keep_alive_result() ERROR: Receiving device alive message timed out!\n");
            return 1;
        }
        counter += 1;
    }   
    
    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ml_Get_Current_Data_Ack)) {
        // Default error message -> specify the code.
        printf("keep_alive_result() ERROR: Unsuccessful device alive response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ml_Get_Current_Data_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    }

    return 0;
}


int midlevel_end(RehamoveDevice * r) {
    if (r == NULL) {
        printf("midlevel_end() ERROR: No RehamoveDevice object found!\n");
        return 1;
    }

    bool ml_stop_result = smpt_send_ml_stop(&(r->device), smpt_packet_number_generator_next(&(r->device)));
    if (!ml_stop_result) {
        printf("ml_stop_result() ERROR: Sending device stop message failed!\n");
        return 1;
    }

    int counter = 0;
    while (!smpt_new_packet_received(&(r->device))) {
        if (counter > TIMEOUT_COUNTER) {
            printf("ml_stop_result() ERROR: Receiving device stop message timed out!\n");
            return 1;
        }
        counter += 1;
    }   
    
    Smpt_ack ack;
    smpt_last_ack(&(r->device), &ack);

    if ((ack.result != Smpt_Result_Successful) || (ack.command_number != Smpt_Cmd_Ml_Stop_Ack)) {
        // Default error message -> specify the code.
        printf("ml_stop_result() ERROR: Unsuccessful device stop response! Expected: command %d result %d, Received: command %d result %d.\n", Smpt_Cmd_Ml_Stop_Ack, Smpt_Result_Successful, ack.command_number, ack.result);
        return 1;
    }

    return 0;
}


char * get_version() {
    return VERSION_NUMBER;
}


int get_battery(RehamoveDevice * r) {
    if (r == NULL) {
        printf("get_battery() ERROR: No RehamoveDevice object found!\n");
        return -1;
    }
    return r->battery;
}

int get_mode(RehamoveDevice * r) {
    if (r == NULL) {
        printf("get_mode() ERROR: No RehamoveDevice object found!\n");
        return -1;
    }
    return r->mode;
}

float get_current(RehamoveDevice * r) {
    if (r == NULL) {
        printf("get_current() ERROR: No RehamoveDevice object found!\n");
        return -1;
    }
    return r->current;
}

int get_pulse_width(RehamoveDevice * r) {
    if (r == NULL) {
        printf("get_pulse_width() ERROR: No RehamoveDevice object found!\n");
        return 0;
    }
    return (int) r->pulse_width;
}

int battery_request(RehamoveDevice * r) {
    if (r == NULL) {
        printf("battery_request() ERROR: No RehamoveDevice object found!\n");
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