#include <stddef.h>
#include <stdlib.h>
#include "system_parser.h"
#include "system_monitor.h"

// Initialize the system structure.
void SystemInit(System* system)
{
    system->num_processes = 0;
    system->processes = NULL;
}

// Get the array of processes from the system.
Process* SystemGetProcesses(System* system)
{
    return system->processes;
}

// Get the memory utilization of the system.
float SystemGetMemoryUtilization(const System* system)
{
    return GetMemoryUtilization();
}

// Get the uptime of the system.
long SystemGetUpTime(const System* system)
{
    return GetSystemUpTime();
}

// Get the total number of processes on the system.
int SystemGetTotalProcesses(const System* system)
{
    return GetTotalProcesses();
}

// Get the number of running processes on the system.
int SystemGetRunningProcesses(const System* system)
{
    return GetRunningProcesses();
}

// Get the kernel version of the system.
const char* SystemGetKernel(System* system)
{
    return GetKernelVersion();
}

// Get the operating system name of the system.
const char* SystemGetOperatingSystem(System* system)
{
    return GetOperatingSystem();
}
