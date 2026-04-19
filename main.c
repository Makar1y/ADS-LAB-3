#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "params.h"
#include "simulation.h"

#ifdef _WIN32
#include <windows.h>
#endif

static int hasSuffix(const char* text, const char* suffix) {
    size_t textLength;
    size_t suffixLength;

    if (!text || !suffix) {
        return 0;
    }

    textLength = strlen(text);
    suffixLength = strlen(suffix);

    if (suffixLength > textLength) {
        return 0;
    }

    return strcmp(text + textLength - suffixLength, suffix) == 0;
}

static void buildDefaultConfigPath(const char* executablePath, char* buffer, size_t bufferSize) {
    size_t length;

    if (!executablePath || !buffer || bufferSize == 0) {
        return;
    }

    snprintf(buffer, bufferSize, "%s", executablePath);
    length = strlen(buffer);

    if (hasSuffix(buffer, ".exe")) {
        buffer[length - 4] = '\0';
        strncat(buffer, ".cfg", bufferSize - strlen(buffer) - 1);
    } else {
        strncat(buffer, ".cfg", bufferSize - strlen(buffer) - 1);
    }
}

static void printUsage(const char* executableName) {
    printf("Naudojimas:\n");
    printf("  %s [parametru_failas] [-rnd seka]\n", executableName);
    printf("  %s [-rnd seka]\n", executableName);
}

int main(int argc, char* argv[]) {
    SimulationParams params;
    SimulationResult result;
    char configPath[512];
    char errorBuffer[256];
    const char* paramsFile = NULL;
    unsigned int seed = 0U;
    int seedProvided = 0;
    int i;

    setvbuf(stdout, NULL, _IONBF, 0);

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    buildDefaultConfigPath(argv[0], configPath, sizeof(configPath));

    for (i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-rnd") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Po parametro -rnd turi sekti skaicius.\n");
                printUsage(argv[0]);
                return 1;
            }
            seed = (unsigned int)strtoul(argv[i + 1], NULL, 10);
            seedProvided = 1;
            ++i;
        } else if (!paramsFile) {
            paramsFile = argv[i];
        } else {
            fprintf(stderr, "Per daug neapibreztu parametru.\n");
            printUsage(argv[0]);
            return 1;
        }
    }

    if (!paramsFile) {
        paramsFile = configPath;
    }

    if (readParamsFile(paramsFile, &params) != 0) {
        fprintf(stderr, "Nepavyko perskaityti parametru failo: %s\n", paramsFile);
        return 1;
    }

    if (validateParams(&params, errorBuffer, (int)sizeof(errorBuffer)) != 0) {
        fprintf(stderr, "Netinkami parametrai: %s\n", errorBuffer);
        return 1;
    }

    if (!seedProvided) {
        seed = time(NULL);
    }

    srand(seed);

    if (runSimulation(&params, &result) != 0) {
        fprintf(stderr, "Nepavyko sekmingai įvykdyti modeliavimą.\n");
        return 1;
    }

    printSimulationResult(&params, &result, seed);
    freeSimulationResult(&result);
    return 0;
}
