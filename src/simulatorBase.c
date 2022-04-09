/**
* simulator.c consists of function definitions of the simulator.
*/

#include "simulatorBase.h"


/* === function definitions ========================================================= */
FULL_SIM  * setFullSim (double leftArrival, int leftLight,
                        double rightArrival, int rightLight) {
    FULL_SIM *fullSim;
    if ((fullSim = (FULL_SIM *)malloc(sizeof(FULL_SIM))) == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    /* setting initial full simulation parameters */
    fullSim->trafficLight = 0;
    fullSim->lightChangeTime = 0;
    fullSim->left = setSim(leftArrival, leftLight);
    fullSim->right = setSim(rightArrival, rightLight);
    return fullSim;
}

SIM * setSim (double arrival, int light) {
    SIM *simulation;
    if ((simulation = (SIM *)malloc(sizeof(SIM))) == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    /* setting initial simulation values */
    simulation->vehicles = getNewNode(0);
    simulation->arrivalRate = arrival;
    simulation->lightPeriod = light;
    return simulation;
}

void freeSim (FULL_SIM * simulation) {
    emptyDeque(&simulation->left->vehicles);
    free(simulation->left);
    emptyDeque(&simulation->right->vehicles);
    free(simulation->right);
    free(simulation);
}

FULL_RESULT * initFullResult () {
    FULL_RESULT *fullResult;
    if ((fullResult = (FULL_RESULT *)malloc(sizeof(FULL_RESULT))) == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    /* setting initial full result values */
    fullResult->left = initResult();
    fullResult->right = initResult();
    return fullResult;
}

RESULT * initResult () {
    RESULT *result;
    if ((result = (RESULT *)malloc(sizeof(RESULT))) == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    /* setting initial result values */
    result->totalWait = 0;
    result->maxWait = 0;
    result->clearanceTime = 0;
    result->vehicleCount = 0;
    return result;
}

void freeResult (FULL_RESULT * result) {
    free(result->left);
    free(result->right);
    free(result);
}

void addResult (FULL_RESULT ** base, FULL_RESULT * addend) {
    /* adding the left side */
    (*base)->left->totalWait += addend->left->totalWait;
    (*base)->left->maxWait += addend->left->maxWait;
    (*base)->left->vehicleCount += addend->left->vehicleCount;
    (*base)->left->clearanceTime += addend->left->clearanceTime;

    /* adding the right side */
    (*base)->right->totalWait += addend->right->totalWait;
    (*base)->right->maxWait += addend->right->maxWait;
    (*base)->right->vehicleCount += addend->right->vehicleCount;
    (*base)->right->clearanceTime += addend->right->clearanceTime;
}

void divResult (FULL_RESULT ** base, int divisor) {
    /* dividing the left side */
    (*base)->left->totalWait /= divisor;
    (*base)->left->maxWait /= divisor;
    (*base)->left->vehicleCount /= divisor;
    (*base)->left->clearanceTime /= divisor;

    /* dividing the right side */
    (*base)->right->totalWait /= divisor;
    (*base)->right->maxWait /= divisor;
    (*base)->right->vehicleCount /= divisor;
    (*base)->right->clearanceTime /= divisor;
}

void printResult (FULL_RESULT * result, FULL_SIM * simulation) {
    printf("Parameter values:\n");
    printf("\tfrom left:\n");
    printf("\t\ttraffic arrival rate: %4.2f\n", simulation->left->arrivalRate);
    printf("\t\ttraffic light period: %4d\n", simulation->left->lightPeriod);

    printf("\tfrom right:\n");
    printf("\t\ttraffic arrival rate: %4.2f\n", simulation->right->arrivalRate);
    printf("\t\ttraffic light period: %4d\n", simulation->right->lightPeriod);


    printf("Results (averaged over 100 runs):\n");
    printf("\tfrom left:\n");
    printf("\t\tnumber of vehicles:   %4d\n", result->left->vehicleCount);
    printf("\t\taverage waiting time: %4d\n", result->left->totalWait / result->left->vehicleCount);
    printf("\t\tmaximum waiting time: %4d\n", result->left->maxWait);
    printf("\t\tclearance time:       %4d\n", result->left->clearanceTime);

    printf("\tfrom right:\n");
    printf("\t\tnumber of vehicles:   %4d\n", result->right->vehicleCount);
    printf("\t\taverage waiting time: %4d\n", result->right->totalWait / result->right->vehicleCount);
    printf("\t\tmaximum waiting time: %4d\n", result->right->maxWait);
    printf("\t\tclearance time:       %4d\n", result->right->clearanceTime);
}

int readInt (char * fromString) {
    char *p;
    errno = 0;
    int integer = strtol(fromString, &p, 10);
    if (*p != '\0' || errno != 0) {
        fprintf(stderr, "Invalid simulation parameters\n");
        exit(EXIT_FAILURE);
    } return integer;
}

double readDouble (char * fromString) {
    char *p;
    errno = 0;
    double integer = strtod(fromString, &p);
    if (*p != '\0' || errno != 0) {
        fprintf(stderr, "Invalid simulation parameters\n");
        exit(EXIT_FAILURE);
    } return integer;
}
