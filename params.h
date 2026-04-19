#ifndef PARAMS_H
#define PARAMS_H

typedef struct {
    int workday_duration;
    int acceptance_time;
    int worker1_processing_time;
    int worker2_processing_time;
    int arrival_probability;
} SimulationParams;

int readParamsFile(const char* filename, SimulationParams* params);
int validateParams(const SimulationParams* params, char* errorBuffer, int errorBufferSize);

#endif
