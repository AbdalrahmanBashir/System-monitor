#pragma once
#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <signal.h>

// Function to send a signal to a process
int KillProcess(int pid, int signal);

#endif // PROCESS_MANAGER_H