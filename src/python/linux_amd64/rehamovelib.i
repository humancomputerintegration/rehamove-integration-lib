%module rehamovelib
%{
#include "smpt_ll_client.h"
#include "smpt_ml_client.h"

typedef struct {
    Smpt_device device;
    int battery;
    int mode;
    float current;
    uint16_t pulse_width;
} RehamoveDevice;

extern RehamoveDevice * open_port(const char * port_name);
extern int close_port(RehamoveDevice * r);

extern int initialize_low_level(RehamoveDevice * r);
extern int stop_low_level(RehamoveDevice * r);
extern int pulse(RehamoveDevice * r, int channel, float current, int pulse_width);
extern int custom_pulse(RehamoveDevice * r, int channel, int num_points, float c0, int w0, float c1, int w1, float c2, int w2, float c3, int w3, float c4, int w4, float c5, int w5, float c6, int w6, float c7, int w7, float c8, int w8, float c9, int w9, float c10, int w10, float c11, int w11, float c12, int w12, float c13, int w13, float c14, int w14, float c15, int w15);

extern int change_mode(RehamoveDevice * r, int mode);
extern int set_pulse_data(RehamoveDevice * r, float current, int pulse_width);
extern int run(RehamoveDevice * r, int channel, float period, int total_milliseconds);
extern int midlevel_start(RehamoveDevice * r, int channel, float period);
extern int midlevel_update(RehamoveDevice * r);
extern int midlevel_end(RehamoveDevice * r);

extern char * get_version();
extern int get_battery(RehamoveDevice * r);
extern int get_mode(RehamoveDevice * r);
extern float get_current(RehamoveDevice * r);
extern int get_pulse_width(RehamoveDevice * r);
extern int get_battery(RehamoveDevice * r);
extern int battery_request(RehamoveDevice * r);

%}

typedef struct {
    Smpt_device device;
    int battery;
    int mode;
    float current;
    uint16_t pulse_width;
} RehamoveDevice;

extern RehamoveDevice * open_port(const char * port_name);
extern int close_port(RehamoveDevice * r);

extern int initialize_low_level(RehamoveDevice * r);
extern int stop_low_level(RehamoveDevice * r);
extern int pulse(RehamoveDevice * r, int channel, float current, int pulse_width);
extern int custom_pulse(RehamoveDevice * r, int channel, int num_points, float c0, int w0, float c1, int w1, float c2, int w2, float c3, int w3, float c4, int w4, float c5, int w5, float c6, int w6, float c7, int w7, float c8, int w8, float c9, int w9, float c10, int w10, float c11, int w11, float c12, int w12, float c13, int w13, float c14, int w14, float c15, int w15);

extern int change_mode(RehamoveDevice * r, int mode);
extern int set_pulse_data(RehamoveDevice * r, float current, int pulse_width);
extern int run(RehamoveDevice * r, int channel, float period, int total_milliseconds);
extern int midlevel_start(RehamoveDevice * r, int channel, float period);
extern int midlevel_update(RehamoveDevice * r);
extern int midlevel_end(RehamoveDevice * r);

extern char * get_version();
extern int get_battery(RehamoveDevice * r);
extern int get_mode(RehamoveDevice * r);
extern float get_current(RehamoveDevice * r);
extern int get_pulse_width(RehamoveDevice * r);
extern int battery_request(RehamoveDevice * r);