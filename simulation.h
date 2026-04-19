#ifndef SIMULATION_H
#define SIMULATION_H

#include "bigint_compat.h"
#include "params.h"

typedef struct {
    BigInteger* total_arrivals;
    BigInteger* total_accepted;
    BigInteger* total_processed;
    BigInteger* shelf_peak;
    BigInteger* worker1_busy_time;
    BigInteger* worker2_busy_time;
    BigInteger* worker1_idle_during_day;
    BigInteger* worker2_idle_during_day;
    int total_elapsed_time;
    int overtime_total;
    int overtime_processing_only;
    int remaining_queue_at_close;
    int last_acceptance_finish_time;
    double worker1_occupancy;
    double worker2_occupancy;
} SimulationResult;

int runSimulation(const SimulationParams* params, SimulationResult* result);
void freeSimulationResult(SimulationResult* result);
void printSimulationResult(const SimulationParams* params, const SimulationResult* result, unsigned int seed);

#endif
