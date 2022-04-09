/**
 * simulator.h consists of structure definitions and function
 * prototypes of the simulator.c source.
 */

#ifndef TRAFFIC_SIM_SIMULATORBASE_H
#define TRAFFIC_SIM_SIMULATORBASE_H

#include <errno.h>
#include <limits.h>
#include <string.h>
#include "deque.h"


/* === structure definitions ========================================================= */
struct simStruct {
    DEQUE *vehicles;
    double arrivalRate;
    int lightPeriod;
}; typedef struct simStruct SIM;

struct fullSimStruct {
    /* current iteration in the simulation */
    short int iter;
    /* 0 - right side is green, 1 - left side is green */
    short int trafficLight;
    /* iteration when the lights were changed */
    short int lightChangeTime;
    SIM *left;
    SIM *right;
}; typedef struct fullSimStruct FULL_SIM;

struct resultStruct {
    /* results for individual traffic side */
    int totalWait;
    int maxWait;
    int clearanceTime;
    int vehicleCount;
}; typedef struct resultStruct RESULT;

struct fullResultStruct {
    /* general results, both sides of the traffic */
    RESULT *left;
    RESULT *right;
}; typedef struct fullResultStruct FULL_RESULT;


/* === function prototypes ========================================================= */
FULL_SIM * setFullSim (double, int, double, int);
SIM * setSim (double, int);
void freeSim (FULL_SIM *);

FULL_RESULT * initFullResult ();
RESULT * initResult ();
void freeResult (FULL_RESULT *);
void addResult (FULL_RESULT **, FULL_RESULT *);
void divResult (FULL_RESULT **, int);
void printResult (FULL_RESULT *, FULL_SIM *);

int readInt (char *);
double readDouble (char *);


#endif
