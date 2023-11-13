#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <ctype.h>
#include <dirent.h>
#include <pwd.h> 
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include "system_parser.h"

#define CMDLINE_MAX 1024

// Function to retrieve a list of process IDs
int* GetProcessIds(int* count) {
    DIR* dir;
    struct dirent* ent;
    int* pids = NULL;
    int i = 0;

    dir = opendir("/proc");
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (isdigit(*ent->d_name)) {
                int pid = atoi(ent->d_name);
                pids = (int*)realloc(pids, (i + 1) * sizeof(int));
                pids[i++] = pid;
            }
        }

        closedir(dir);
    }

    *count = i;
    return pids;
}


float GetMemoryUtilization() {
    
    int fd = open("/proc/meminfo", O_RDONLY);
    if (fd == -1) {
        perror("Error opening /proc/meminfo");
        return -1.0f;
    }

    char buffer[100];
    ssize_t bytesRead;
    unsigned long memory_total = 0;
    unsigned long memory_free = 0;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        char* line = buffer;
        char* end;

        while ((end = strchr(line, '\n')) != NULL) {
            *end = '\0';

            unsigned long value;
            if (sscanf(line, "MemTotal: %lu kB", &value) == 1) {
                memory_total = value;
            }
            else if (sscanf(line, "MemFree: %lu kB", &value) == 1) {
                memory_free = value;
            }

            // Break the loop if both values are obtained
            if (memory_total != 0 && memory_free != 0) {
                close(fd);
                if (memory_total != 0) {
                    float memory_used = (float)(memory_total - memory_free) / memory_total;
                    return memory_used;
                }
                else {
                    return -1.0f; 
                }
            }

            line = end + 1;
        }
    }

    close(fd);

    return -1.0f; 
}


long GetSystemUpTime() {
    
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        perror("Failed to retrieve system information");
        return -1; // Return an error code or handle the error appropriately
    }
    return info.uptime;
  
}

float* GetCpuUtilization() {
    char cpuValues[256];
    memset(cpuValues, 0, 256);

    FILE* file = fopen("/proc/stat", "r");
    if (file != NULL) {
        fgets(cpuValues, 256, file);
        fclose(file);
    }
    else {
        perror("Failed to open /proc/stat");
        return NULL;
    }

    float* cpuUtilization = (float*)malloc(8 * sizeof(float));
    if (cpuUtilization == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    char user[16], nice[16], system[16], idle[16], iowait[16], irq[16], softirq[16], steal[16];
    memset(user, 0, 16);
    memset(nice, 0, 16);
    memset(system, 0, 16);
    memset(idle, 0, 16);
    memset(iowait, 0, 16);
    memset(irq, 0, 16);
    memset(softirq, 0, 16);
    memset(steal, 0, 16);

    sscanf(cpuValues, "%s %s %s %s %s %s %s %s", user, nice, system, idle, iowait, irq, softirq, steal);

    cpuUtilization[0] = atof(user);
    cpuUtilization[1] = atof(nice);
    cpuUtilization[2] = atof(system);
    cpuUtilization[3] = atof(idle);
    cpuUtilization[4] = atof(iowait);
    cpuUtilization[5] = atof(irq);
    cpuUtilization[6] = atof(softirq);
    cpuUtilization[7] = atof(steal);

    return cpuUtilization;
}


int GetTotalProcesses()
{
    DIR* dir = opendir("/proc");
    if (dir == NULL) {
        return -1;  // Return -1 to indicate an error
    }

    int count = 0;

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry's name consists of digits, which is common for process directories
        int is_digit_name = 1;
        for (int i = 0; entry->d_name[i] != '\0'; i++) {
            if (!isdigit((unsigned char)(entry->d_name[i]))) {
                is_digit_name = 0;
                break;
            }
        }

        if (is_digit_name) {
            count++;
        }
    }

    closedir(dir);

    return count;
}

int GetRunningProcesses() {
    DIR* dir = opendir("/proc");
    if (dir == NULL) {
        return -1; // Error
    }

    int count = 0;

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        const char* filename = entry->d_name;
        if (!isdigit(filename[0])) {
            continue; // Skip non-numeric entries
        }

        char status_path[256];
        snprintf(status_path, sizeof(status_path), "/proc/%s/status", filename);

        // Attempt to open the status file for the process
        FILE* status_file = fopen(status_path, "r");
        if (status_file != NULL) {
            // Successfully opened the file, which indicates a valid running process
            fclose(status_file);
            count++;
        }
    }

    closedir(dir);

    return count;
}



const char* GetOperatingSystem()
{
    return "Linux";
}



const char* GetKernelVersion() {
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        return "Error retrieving kernel version";
    }

    static char kernel_version[256];
    snprintf(kernel_version, sizeof(kernel_version), "%s", buffer.release);

    return kernel_version;
}



float GetCpuUtilizationForProcess(int pid) {
    char path[1024];
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        return -1.0f;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    char* token = strtok(buffer, " ");
    for (int i = 0; i < 12; i++) {
        token = strtok(NULL, " ");
    }

    long utime = atol(token);
    token = strtok(NULL, " ");
    long stime = atol(token);
    token = strtok(NULL, " ");
    long cutime = atol(token);
    token = strtok(NULL, " ");
    long cstime = atol(token);

    long total_time = utime + stime + cutime + cstime;
    long hertz = sysconf(_SC_CLK_TCK);
    long seconds = GetUpTimeForProcess(pid);
    float cpu_usage = 100.0f * ((float)total_time / (float)hertz) / (float)seconds;

    return cpu_usage;
}

const char* GetCommandForProcess(int pid) {
    char path[1024];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return "Unknown";
    }

    char buffer[CMDLINE_MAX];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, "Name:", 5) == 0) {
            fclose(file);

            // Extract the command from the "Name:" line
            const char* commandPtr = buffer + 5;
            while (*commandPtr != '\0' && (*commandPtr == ' ' || *commandPtr == '\t')) {
                commandPtr++;
            }

            // Trim leading whitespace
            // Remove trailing newline character if present
            size_t length = strlen(commandPtr);
            if (length > 0 && commandPtr[length - 1] == '\n') {
                ((char*)commandPtr)[length - 1] = '\0';
            }

            return commandPtr;

        }
    }

    fclose(file);
    return "Unknown";
}




const char* GetRamForProcess(int pid) {
    char path[1024];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        return "0 KB";
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, "VmSize:", 7) == 0) {
            fclose(file);

            // Extract the memory information.
            const char* memoryInfo = buffer + 7;

            // Remove trailing newline or carriage return characters if present.
            size_t length = strlen(memoryInfo);
            while (length > 0 && (memoryInfo[length - 1] == '\n' || memoryInfo[length - 1] == '\r')) {
                length--;
            }

            // Copy the memory information into a new buffer.
            char* result = malloc(length + 1);
            strncpy(result, memoryInfo, length);
            result[length] = '\0';

            return result;
        }
    }

    fclose(file);
    return "0 KB";
}


const char* GetUidForProcess(int pid) {
    char path[1024];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        return "0";
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, "Uid:", 4) == 0) {
            fclose(file);

            // Extract the numeric part of the "Uid:" line
            const char* uidPtr = buffer + 4;
            while (*uidPtr != '\0' && (*uidPtr < '0' || *uidPtr > '9')) {
                uidPtr++;
            }

            return uidPtr;
        }
    }

    fclose(file);
    return "0";
}

const char* GetUserForProcess(int pid) {
    char uid[1024];
    snprintf(uid, sizeof(uid), "%s", GetUidForProcess(pid));

    struct passwd* pw = getpwuid(atoi(uid));
    if (pw == NULL) {
        return "Unknown";
    }

    return pw->pw_name;
}

long GetUpTimeForProcess(int pid) {
    char path[1024];
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        return -1;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    char* token = strtok(buffer, " ");
    for (int i = 0; i < 21; i++) {
        token = strtok(NULL, " ");
    }

    long start_time = atol(token);
    long hertz = sysconf(_SC_CLK_TCK);
    long uptime = GetSystemUpTime();
    long seconds = uptime - (start_time / hertz);

    return seconds;
}



