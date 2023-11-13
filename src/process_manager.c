#include "process_manager.h"
#include "system_parser.h"


int KillProcess(int pid, int signal) {
    if (kill(pid, signal) == 0) {
        return 0; 
    }
    else {
        perror("Error sending signal");
        return -1;
    }
}
