#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "1beva2327/deque.h"
#include "simulation.h"

typedef enum {
    IDLE = 0,
    ACCEPTANCE = 1,
    PROCESSING = 2
} TaskType;

typedef struct {
    TaskType task;
    int remaining_time;
    int processing_time;
} WorkerState;

static BigInteger* createBigIntegerFromUnsigned(unsigned int value) {
    BigInteger* number = createBigInteger();
    char buffer[32];

    if (!number) {
        return NULL;
    }

    snprintf(buffer, sizeof(buffer), "%u", value);
    if (stringToBigInteger(buffer, number) != 0) {
        Done(&number);
        return NULL;
    }

    return number;
}

static int addUnsignedToBigInteger(BigInteger** target, unsigned int value) {
    BigInteger* increment;
    BigInteger* sum;

    if (!target || !*target) {
        return -1;
    }

    increment = createBigIntegerFromUnsigned(value);
    if (!increment) {
        return -1;
    }

    sum = addBigInteger(*target, increment);
    Done(&increment);
    if (!sum) {
        return -1;
    }

    Done(target);
    *target = sum;
    return 0;
}

static int assignIdleWorker(
    WorkerState* worker,
    int* waitingApplicants,
    Deque* shelf,
    int takeFromFront,
    int acceptanceTime
) {
    if (!worker || worker->task != IDLE) {
        return 0;
    }

    if (*waitingApplicants > 0) {
        worker->task = ACCEPTANCE;
        worker->remaining_time = acceptanceTime;
        (*waitingApplicants)--;
        return 1;
    }

    if (!isEmpty(shelf)) {
        if (takeFromFront) {
            removeFront(shelf);
        } else {
            removeBack(shelf);
        }
        worker->task = PROCESSING;
        worker->remaining_time = worker->processing_time;
        return 1;
    }

    return 0;
}

static void initResult(SimulationResult* result) {
    memset(result, 0, sizeof(*result));
    result->total_arrivals = createBigIntegerFromUnsigned(0);
    result->total_accepted = createBigIntegerFromUnsigned(0);
    result->total_processed = createBigIntegerFromUnsigned(0);
    result->shelf_peak = createBigIntegerFromUnsigned(0);
    result->worker1_busy_time = createBigIntegerFromUnsigned(0);
    result->worker2_busy_time = createBigIntegerFromUnsigned(0);
    result->worker1_idle_during_day = createBigIntegerFromUnsigned(0);
    result->worker2_idle_during_day = createBigIntegerFromUnsigned(0);
}

static void freeBigIntegerFields(SimulationResult* result) {
    Done(&result->total_arrivals);
    Done(&result->total_accepted);
    Done(&result->total_processed);
    Done(&result->shelf_peak);
    Done(&result->worker1_busy_time);
    Done(&result->worker2_busy_time);
    Done(&result->worker1_idle_during_day);
    Done(&result->worker2_idle_during_day);
}

int runSimulation(const SimulationParams* params, SimulationResult* result) {
    WorkerState worker1;
    WorkerState worker2;
    Deque* shelf;
    int waitingApplicants = 0;
    int nextApplicationId = 1;
    int currentTime = 0;
    int peakShelfSize = 0;
    int queueAtCloseRecorded = 0;

    if (!params || !result) {
        return -1;
    }

    initResult(result);
    if (!result->total_arrivals || !result->total_accepted || !result->total_processed ||
        !result->shelf_peak || !result->worker1_busy_time || !result->worker2_busy_time ||
        !result->worker1_idle_during_day || !result->worker2_idle_during_day) {
        freeBigIntegerFields(result);
        return -1;
    }

    shelf = createDeque(params->workday_duration + 2);
    if (!shelf) {
        freeBigIntegerFields(result);
        return -1;
    }

    worker1.task = IDLE;
    worker1.remaining_time = 0;
    worker1.processing_time = params->worker1_processing_time;

    worker2.task = IDLE;
    worker2.remaining_time = 0;
    worker2.processing_time = params->worker2_processing_time;

    result->last_acceptance_finish_time = params->workday_duration;

    while (currentTime < params->workday_duration || waitingApplicants > 0 || !isEmpty(shelf) ||
           worker1.task != IDLE || worker2.task != IDLE) {
        int duringDay = currentTime < params->workday_duration;

        if (duringDay && (rand() % 100) < params->arrival_probability) {
            ++waitingApplicants;
            addUnsignedToBigInteger(&result->total_arrivals, 1);
        }

        assignIdleWorker(&worker1, &waitingApplicants, shelf, 1, params->acceptance_time);
        assignIdleWorker(&worker2, &waitingApplicants, shelf, 0, params->acceptance_time);

        if (worker1.task == IDLE && duringDay) {
            addUnsignedToBigInteger(&result->worker1_idle_during_day, 1);
        }
        if (worker2.task == IDLE && duringDay) {
            addUnsignedToBigInteger(&result->worker2_idle_during_day, 1);
        }

        if (worker1.task != IDLE) {
            --worker1.remaining_time;
            addUnsignedToBigInteger(&result->worker1_busy_time, 1);
        }
        if (worker2.task != IDLE) {
            --worker2.remaining_time;
            addUnsignedToBigInteger(&result->worker2_busy_time, 1);
        }

        if (worker1.task != IDLE && worker1.remaining_time == 0) {
            if (worker1.task == ACCEPTANCE) {
                insertFront(shelf, nextApplicationId++);
                addUnsignedToBigInteger(&result->total_accepted, 1);
                if (shelf->size > peakShelfSize) {
                    peakShelfSize = shelf->size;
                }
                result->last_acceptance_finish_time = currentTime + 1;
            } else {
                addUnsignedToBigInteger(&result->total_processed, 1);
            }
            worker1.task = IDLE;
        }

        if (worker2.task != IDLE && worker2.remaining_time == 0) {
            if (worker2.task == ACCEPTANCE) {
                insertBack(shelf, nextApplicationId++);
                addUnsignedToBigInteger(&result->total_accepted, 1);
                if (shelf->size > peakShelfSize) {
                    peakShelfSize = shelf->size;
                }
                result->last_acceptance_finish_time = currentTime + 1;
            } else {
                addUnsignedToBigInteger(&result->total_processed, 1);
            }
            worker2.task = IDLE;
        }

        if (!queueAtCloseRecorded && currentTime + 1 == params->workday_duration) {
            result->remaining_queue_at_close = waitingApplicants;
            queueAtCloseRecorded = 1;
        }

        if (getCount(shelf) > peakShelfSize) {
            peakShelfSize = getCount(shelf);
        }

        ++currentTime;
    }

    addUnsignedToBigInteger(&result->shelf_peak, (unsigned int)peakShelfSize);

    result->total_elapsed_time = currentTime;
    result->overtime_total = currentTime - params->workday_duration;
    result->overtime_processing_only = currentTime - result->last_acceptance_finish_time;
    if (result->overtime_processing_only < 0) {
        result->overtime_processing_only = 0;
    }

    if (result->total_elapsed_time > 0) {
        char* busy1 = bigIntegerToStringDec(result->worker1_busy_time);
        char* busy2 = bigIntegerToStringDec(result->worker2_busy_time);
        double worker1Busy = busy1 ? atof(busy1) : 0.0;
        double worker2Busy = busy2 ? atof(busy2) : 0.0;

        free(busy1);
        free(busy2);

        result->worker1_occupancy = 100.0 * worker1Busy / result->total_elapsed_time;
        result->worker2_occupancy = 100.0 * worker2Busy / result->total_elapsed_time;
    }

    destroyDeque(shelf);
    return 0;
}

void freeSimulationResult(SimulationResult* result) {
    if (!result) {
        return;
    }

    freeBigIntegerFields(result);
}

static void printBigIntegerLine(const char* label, const BigInteger* value) {
    char* text = bigIntegerToStringDec(value);
    printf("%-48s %s\n", label, text ? text : "(klaida)");
    free(text);
}

void printSimulationResult(const SimulationParams* params, const SimulationResult* result, unsigned int seed) {
    printf("Priemimo komisijos modeliavimas\n");
    printf("-----------------------------------------------\n");
    printf("Atsitiktiniu skaičių generatoriaus pradine reikšme: %u\n", seed);
    printf("Priemimo darbo dienos trukme:                     %d\n", params->workday_duration);
    printf("Vieno prašymo priemimo trukme:                    %d\n", params->acceptance_time);
    printf("1 darbuotojos tvarkymo trukme:                    %d\n", params->worker1_processing_time);
    printf("2 darbuotojos tvarkymo trukme:                    %d\n", params->worker2_processing_time);
    printf("Stojančiojo atejimo tikimybe:                     %d%%\n", params->arrival_probability);
    printf("\nRezultatai\n");
    printf("-----------------------------------------------\n");
    printBigIntegerLine("Iš viso atejo stojančiuju:", result->total_arrivals);
    printBigIntegerLine("Iš viso priimta prašymu:", result->total_accepted);
    printBigIntegerLine("Iš viso sutvarkyta prašymu:", result->total_processed);
    printBigIntegerLine("Didžiausias prašymu kiekis lentynoje:", result->shelf_peak);
    printBigIntegerLine("1 darbuotojos užimtas laikas:", result->worker1_busy_time);
    printBigIntegerLine("2 darbuotojos užimtas laikas:", result->worker2_busy_time);
    printBigIntegerLine("1 darbuotojos poilsio laikas darbo diena:", result->worker1_idle_during_day);
    printBigIntegerLine("2 darbuotojos poilsio laikas darbo diena:", result->worker2_idle_during_day);
    printf("%-48s %d\n", "Laukiančių stojančiuju eile dienos pabaigoje:", result->remaining_queue_at_close);
    printf("%-48s %d\n", "Papildomas darbo laikas po priemimo valandu:", result->overtime_total);
    printf("%-48s %d\n", "Iš jo vien prašymu tvarkymui po paskutinio priemimo:", result->overtime_processing_only);
    printf("%-48s %.2f%%\n", "1 darbuotojos užimtumas:", result->worker1_occupancy);
    printf("%-48s %.2f%%\n", "2 darbuotojos užimtumas:", result->worker2_occupancy);
}
