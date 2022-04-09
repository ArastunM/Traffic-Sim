/**
 * runSimulations.h consists of structure definitions and function
 * prototypes of the runSimulation.c executable.
 */

#ifndef TRAFFIC_SIM_RUNSIMULATIONS_H
#define TRAFFIC_SIM_RUNSIMULATIONS_H
#define RUNS 100
#define ITERATIONS 500

#include <time.h>
#include "simulatorBase.h"


/* === function prototypes ========================================================= */
FULL_RESULT * runSimulations (double, int, double, int);
FULL_RESULT * runSimulation (double, int, double, int);
void runIteration(FULL_RESULT **, FULL_SIM **);
int randomBias (double);

int lightChange (FULL_SIM **);
void tryPass (FULL_RESULT **, FULL_SIM **);
void vehiclePass (RESULT **, SIM **, int);

void tryArrival (FULL_RESULT **, FULL_SIM **);
void vehicleArrive (RESULT **, SIM **, int);
void tryClearance (FULL_RESULT **, FULL_SIM **);


#endif
