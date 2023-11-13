#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "system_parser.h"

// Constructor-style initialization.
void ProcessInit(Process* process, int pid) {
    process->pid = pid;
}

// Function to return this process's ID.
int ProcessPid(const Process* process) {
    return process->pid;
}

// Function to return this process's CPU utilization.
float ProcessCpuUtilization(const Process* process) {
    return GetCpuUtilizationForProcess(process->pid);
}

// Function to return the command that generated this process.
const char* ProcessCommand(const Process* process) {
    return GetCommandForProcess(process->pid);
}

// Function to return this process's memory utilization.
const char* ProcessRam(const Process* process) {
    return GetRamForProcess(process->pid);
}

// Function to return the user (name) that generated this process.
const char* ProcessUser(const Process* process) {
    return GetUserForProcess(process->pid);
}

// Function to return the age of this process.
long ProcessUpTime(const Process* process) {
    return GetUpTimeForProcess(process->pid);
}
