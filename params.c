#include <stdio.h>

#include "params.h"

int readParamsFile(const char* filename, SimulationParams* params) {
    FILE* file;
    char line[256];
    int values[5];
    int count = 0;

    if (!filename || !params) {
        return -1;
    }

    file = fopen(filename, "r");
    if (!file) {
        return -2;
    }

    while (fgets(line, sizeof(line), file) && count < 5) {
        int value;

        if (sscanf(line, " %d", &value) == 1) {
            values[count++] = value;
        }
    }

    fclose(file);

    if (count != 5) {
        return -3;
    }

    params->workday_duration = values[0];
    params->acceptance_time = values[1];
    params->worker1_processing_time = values[2];
    params->worker2_processing_time = values[3];
    params->arrival_probability = values[4];

    return 0;
}

int validateParams(const SimulationParams* params, char* errorBuffer, int errorBufferSize) {
    if (!params) {
        snprintf(errorBuffer, (size_t)errorBufferSize, "Nenurodyti modeliavimo parametrai.");
        return -1;
    }

    if (params->workday_duration <= 0) {
        snprintf(errorBuffer, (size_t)errorBufferSize, "Priemimo laikas turi buti teigiamas.");
        return -1;
    }

    if (params->acceptance_time <= 0) {
        snprintf(errorBuffer, (size_t)errorBufferSize, "Prasymo priemimo laikas turi buti teigiamas.");
        return -1;
    }

    if (params->worker1_processing_time <= 0 || params->worker2_processing_time <= 0) {
        snprintf(errorBuffer, (size_t)errorBufferSize, "Abieju darbuotoju prasymo tvarkymo laikas turi buti teigiamas.");
        return -1;
    }

    if (params->arrival_probability < 0 || params->arrival_probability > 100) {
        snprintf(errorBuffer, (size_t)errorBufferSize, "Stojanciojo atejimo tikimybe turi buti intervale [0; 100].");
        return -1;
    }

    return 0;
}
