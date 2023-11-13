#pragma once
#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// System
float GetMemoryUtilization();
long GetSystemUpTime();
int* GetProcessIds(int* count);
int GetTotalProcesses();
int GetRunningProcesses();
const char* GetOperatingSystem();
const char* GetKernelVersion();

// CPU
enum CPUStates {
    USER,
    NICE,
    SYSTEM,
    IDLE,
    IOWAIT,
    IRQ,
    SOFTIRQ,
    STEAL,
    GUEST,
    GUESTNICE
};

float* GetCpuUtilization();


// Processes
float GetCpuUtilizationForProcess(int pid);
const char* GetCommandForProcess(int pid);
const char* GetRamForProcess(int pid);
const char* GetUidForProcess(int pid);
const char* GetUserForProcess(int pid);
long GetUpTimeForProcess(int pid);

#endif
