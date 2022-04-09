/**
* runSimulations.c consists of function definitions of the simulator.
*/

#include "runSimulations.h"


/* === main function ========================================================= */
int main (int argc, char **argv) {
    /* processing user input (simulation parameters) */
    if (argc != 5) {
        fprintf(stderr, "Program should take 4 arguments\n");
        return 1;
    }
    double leftArrival = readDouble(argv[1]);
    int leftLight = readInt(argv[2]);
    double rightArrival = readDouble(argv[3]);
    int rightLight = readInt(argv[4]);

    /* running simulations and outputting final result */
    srand(time(0));
    FULL_RESULT * result = runSimulations(leftArrival, leftLight, rightArrival, rightLight);
    FULL_SIM * simulation = setFullSim(leftArrival, leftLight, rightArrival, rightLight);
    printResult(result, simulation);

    freeSim(simulation);
    freeResult(result);
}


/* === function definitions ========================================================= */
FULL_RESULT * runSimulations (double leftArrival, int leftLight,
							  double rightArrival, int rightLight) {
	FULL_RESULT *finalResult = initFullResult();
	int run;

	for (run = 0; run < RUNS; run++) {
		FULL_RESULT * runResult = runSimulation(leftArrival, leftLight, rightArrival, rightLight);
		addResult(&finalResult, runResult);
		freeResult(runResult);
	}
	divResult(&finalResult, RUNS);
	return finalResult;
}

FULL_RESULT * runSimulation (double leftArrival, int leftLight,
							 double rightArrival, int rightLight) {
	FULL_RESULT *fullResult = initFullResult();
	FULL_SIM *fullSim = setFullSim(leftArrival, leftLight, rightArrival, rightLight);

	/* running through a number of iterations */
	fullSim->iter = 0;
	while (fullSim->iter < ITERATIONS || !(isEmpty(fullSim->left->vehicles) &&
                                           isEmpty(fullSim->right->vehicles))) {
		runIteration(&fullResult, &fullSim);
		fullSim->iter++;
	}
	freeSim(fullSim); /* freeing the simulation */
	return fullResult;
}

void runIteration (FULL_RESULT ** fullResult, FULL_SIM ** fullSim) {
	/* either the light changes or vehicles join/pass */
	if (lightChange(fullSim)) {
		(*fullSim)->trafficLight = abs(1 - (*fullSim)->trafficLight);
		(*fullSim)->lightChangeTime = (*fullSim)->iter;
	}
	else {
		tryArrival(fullResult, fullSim);
		tryClearance(fullResult, fullSim);
		tryPass(fullResult, fullSim);
	}
}

int lightChange (FULL_SIM ** fullSim) {
	/* traffic light changes if the lightPeriod time has been reached */
	return (*fullSim)->trafficLight == 0 ? /* either right or left side is green */
	       (*fullSim)->iter - (*fullSim)->lightChangeTime == (*fullSim)->right->lightPeriod :
           (*fullSim)->iter - (*fullSim)->lightChangeTime == (*fullSim)->left->lightPeriod;
}

void tryArrival (FULL_RESULT ** fullResult, FULL_SIM ** fullSim) {
	/* vehicles stop arriving after fixed amount (500) of iterations */
	if ((*fullSim)->iter < ITERATIONS) {
		vehicleArrive(&(*fullResult)->left, &(*fullSim)->left, (*fullSim)->iter);
		vehicleArrive(&(*fullResult)->right, &(*fullSim)->right, (*fullSim)->iter);
	}
}

void vehicleArrive (RESULT ** result, SIM ** sim, int iter) {
	/* either a vehicle arrives or not based on arrivalRate */
	if (randomBias((*sim)->arrivalRate)) {
		pushBack(&(*sim)->vehicles, iter);
		(*result)->vehicleCount++;
	}
}

void tryPass (FULL_RESULT ** fullResult, FULL_SIM ** fullSim) {
	/* vehicle on the green side of the traffic light passes */
	if ((*fullSim)->trafficLight == 0 && !isEmpty((*fullSim)->right->vehicles)) {
		vehiclePass(&(*fullResult)->right, &(*fullSim)->right, (*fullSim)->iter);
	} else if (!isEmpty((*fullSim)->left->vehicles)) {
		vehiclePass(&(*fullResult)->left, &(*fullSim)->left, (*fullSim)->iter);
	}
}

void vehiclePass (RESULT ** result, SIM ** sim, int iter) {
	/* right/left side is green, vehicle passes wait time is stored */
	int waitTime = iter - popFront(&(*sim)->vehicles);
	/* total and maximum wait times are adjusted */
	(*result)->totalWait += waitTime;
	if ((*result)->maxWait < waitTime) (*result)->maxWait = waitTime;

}

void tryClearance(FULL_RESULT ** fullResult, FULL_SIM ** fullSim) {
	/* after the specified (500) iterations, clearance time is calculated */
	if ((*fullSim)->iter >= ITERATIONS) {
		if (!isEmpty((*fullSim)->right->vehicles)) {
			(*fullResult)->right->clearanceTime++;
		}
		if (!isEmpty((*fullSim)->left->vehicles)) {
			(*fullResult)->left->clearanceTime++;
		}
	}
}

int randomBias (double biasRate) {
	/* returns boolean based on bias rate */
	double randValue = (1.0 * rand()) / RAND_MAX;
	return randValue < biasRate;
}
