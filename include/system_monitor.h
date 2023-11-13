#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include "process.h"

typedef struct {
    char* kernel;
    char* operating_system;
    Process* processes; // Array of processes
    int num_processes;  // Number of processes in the array
} System;

void SystemInit(System* system);
Process* SystemGetProcesses(System* system);
float SystemGetMemoryUtilization(const System* system);
long SystemGetUpTime(const System* system);
int SystemGetTotalProcesses(const System* system);
int SystemGetRunningProcesses(const System* system);
const char* SystemGetKernel(System* system);
const char* SystemGetOperatingSystem(System* system);
#endif
