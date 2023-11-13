#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#include <string.h>


typedef struct {
    int pid;
    char user[256];
    char cmd[256];
    float cpuUtilization;
    char ram[256];
    long int upTime;
} Process;

void ProcessInit(Process* process, int pid);
int ProcessPid(const Process* process);
const char* ProcessUser(const Process* process);
const char* ProcessCommand(const Process* process);
float ProcessCpuUtilization(const Process* process);
const char* ProcessRam(const Process* process);
long int ProcessUpTime(const Process* process);

#endif
