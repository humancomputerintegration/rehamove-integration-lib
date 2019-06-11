%module rehamovelib
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "smpt_ll_client.h"

typedef struct {
	char port_name[64];
	Smpt_device device;
} RehamoveDevice;

extern int add(int x, int y);
extern RehamoveDevice * open_port(const char * port_name);
extern void close_port(RehamoveDevice * r);
extern void pulse(RehamoveDevice * r, char * channel, int current, int pulse_width);
extern void custom_pulse(RehamoveDevice * r, char * channel, int num_points, float c0, int w0, float c1, int w1, float c2, int w2, float c3, int w3, float c4, int w4, float c5, int w5, float c6, int w6, float c7, int w7, float c8, int w8, float c9, int w9, float c10, int w10, float c11, int w11, float c12, int w12, float c13, int w13, float c14, int w14, float c15, int w15);
extern int battery(RehamoveDevice * r);
%}

typedef struct {
	char port_name[64];
	Smpt_device device;
} RehamoveDevice;

extern int add(int x, int y);
extern RehamoveDevice * open_port(const char * port_name);
extern void close_port(RehamoveDevice * r);
extern void pulse(RehamoveDevice * r, char * channel, int current, int pulse_width);
extern void custom_pulse(RehamoveDevice * r, char * channel, int num_points, float c0, int w0, float c1, int w1, float c2, int w2, float c3, int w3, float c4, int w4, float c5, int w5, float c6, int w6, float c7, int w7, float c8, int w8, float c9, int w9, float c10, int w10, float c11, int w11, float c12, int w12, float c13, int w13, float c14, int w14, float c15, int w15);
extern int battery(RehamoveDevice * r);