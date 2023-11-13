#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <ncurses.h>
#include "display_system_info.h"
#include "system_monitor.h"
#include "system_parser.h"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60
#define CMDLINE_MAX 1024
  
// Function to format elapsed time and display in the specified row and column.
char* FormatElapsedTime(WINDOW* mainwin, long seconds, int row, int col) {
    int days = seconds / 86400;
    int hours = (seconds % 86400) / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = seconds % 60;

    mvwprintw(mainwin, row, col, "%dd %02dh %02dm %02ds", days, hours, minutes, secs);
}

// Function to update and display a progress bar within the ncurses window.
char DisplayProgressBar(WINDOW* window, float percent, int row, int col) {
    int val = (int)(percent * 100);
    int lpad = (int)(percent * PBWIDTH);
    int rpad = PBWIDTH - lpad;

    // Erase the previous content in the specified row and column.
    mvwprintw(window, row, col, "%*s", PBWIDTH + 7, "");

    // Print the updated progress bar.
    mvwprintw(window, row, col, "%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
}


// Function to display system information in the ncurses window.
void DisplaySystemInfo(WINDOW* mainwin, System* system, int scroll_offset) {
    // Clear the main window.
    wclear(mainwin);

    // Display header
    mvwprintw(mainwin, 0, 50, "System  Monitor");

    // Display CPU Utilization.
    mvwprintw(mainwin, 2, 1, "CPU Utilization:");
    float* cpuUtilization = GetCpuUtilization(system);
    mvwprintw(mainwin, 3, 2, "User: %.2f%%", cpuUtilization[0]);
    mvwprintw(mainwin, 4, 2, "Nice: %.2f%%", cpuUtilization[1]);
    mvwprintw(mainwin, 5, 2, "System: %.2f%%", cpuUtilization[2]);
    mvwprintw(mainwin, 6, 2, "Idle: %.2f%%", cpuUtilization[3]);
    mvwprintw(mainwin, 7, 2, "Iowait: %.2f%%", cpuUtilization[4]);
    mvwprintw(mainwin, 8, 2, "IRQ: %.2f%%", cpuUtilization[5]);
    mvwprintw(mainwin, 9, 2, "SoftIRQ: %.2f%%", cpuUtilization[6]);
    mvwprintw(mainwin, 10, 2, "Steal: %.2f%%", cpuUtilization[7]);

    // Display OS and Kernel information.
    mvwprintw(mainwin, 2, 52, "OS: %s", SystemGetOperatingSystem(system));
    mvwprintw(mainwin, 3, 52, "Kernel: %s", SystemGetKernel(system));

    // Display Uptime.
    mvwprintw(mainwin, 4, 52, "Uptime:");
    FormatElapsedTime(mainwin, SystemGetUpTime(system), 4, 60);

    // Display Memory Utilization using a progress bar.
    mvwprintw(mainwin, 5, 52, "Memory Utilization:");
    wmove(mainwin, 5, 72);
    DisplayProgressBar(mainwin, SystemGetMemoryUtilization(system), 5, 72);

    // Display Total and Running Processes.
    mvwprintw(mainwin, 6, 52, "Total Processes: %d", SystemGetTotalProcesses(system));
    mvwprintw(mainwin, 7, 52, "Running Processes: %d", SystemGetRunningProcesses(system));

    // Display menu options.
    mvprintw(12, 1, "k - Kill a process   q - Quit");

    // Display process information in a table.
    mvwprintw(mainwin, 15, 1, "PID     User             CPU Usage          RAM          Uptime                  Command");
    
    // Get process information and display in rows.
    int count;
    int* pids = GetProcessIds(&count);
    if (pids != NULL) {
        int row = 16;
        int max_displayed_rows = 10;
        scrollok(mainwin, TRUE);
        for (int i = scroll_offset; i < count && i < scroll_offset + max_displayed_rows; i++) {
            int pid = pids[i];
            
            Process current_process;
            ProcessInit(&current_process, pid);

            // Use Process functions to get process information
            const char* command = ProcessCommand(&current_process);
            const char* user = ProcessUser(&current_process);
            float cpuUsage = ProcessCpuUtilization(&current_process);
            const char* ram = ProcessRam(&current_process);
            FormatElapsedTime(mainwin, ProcessUpTime(&current_process), row, 60);

            mvwprintw(mainwin, row, 1, "%d", pid);
            mvwprintw(mainwin, row, 9, "%s", user);
            mvwprintw(mainwin, row, 26, "%.2f%%", cpuUsage);
            mvwprintw(mainwin, row, 38, "%s", ram);
            mvwprintw(mainwin, row, 80, "%s", command);
            row++;
        }

        free(pids);
    }
 
    // Refresh the main window to display changes.
    wrefresh(mainwin);
}
