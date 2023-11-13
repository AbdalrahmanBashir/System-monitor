#include <ncurses.h>
#include "system_monitor.h"
#include "display_system_info.h"
#include "process_manager.h"
#define CMDLINE_MAX 1024

int main() {
    WINDOW* mainwin;
    int scroll_offset = 0;
    int pid_to_kill = 0;
    int show_prompt = 0;

    // Initialize ncurses
    mainwin = initscr();
    cbreak();           // Line buffering disabled
    noecho();           // Do not display input characters
    curs_set(0);        // Hide the cursor
    nodelay(mainwin, TRUE); // Non-blocking input
    keypad(mainwin, TRUE);  // Enable special keys

    // Initialize system information
    System system;
    SystemInit(&system);

    // Set a timeout for getch to allow non-blocking input
    timeout(3200);

    int ch;
    while (1) {
        ch = getch();
        if (ch != ERR) {
            // Process user input
            if (ch == 'q') {
                break;
            }
            else if (ch == KEY_UP) {
                if (scroll_offset > 0) {
                    scroll_offset--;
                }
            }
            else if (ch == KEY_DOWN) {
                scroll_offset++;
            }
            else if (ch == 'k') {
                show_prompt = 1; // Set the flag to show the prompt
                pid_to_kill = 0; // Reset pid_to_kill
            }
        }

        // Display system information
        DisplaySystemInfo(mainwin, &system, scroll_offset);

        if (show_prompt) {
            // Show the prompt for entering PID to kill
            mvprintw(13, 1, "Enter PID to kill:");
            refresh();
            echo(); // Enable input echoing

            // Read user input for PID
            int scan_result = scanw("%d", &pid_to_kill);
            noecho(); // Disable input echoing

            // Process the entered PID
            if (scan_result == 1) {
                int result = KillProcess(pid_to_kill, SIGTERM);
                mvprintw(14, 1, "Kill result for PID %d: %s", pid_to_kill, (result == 0) ? "Success" : "Error");
            }

            show_prompt = 0; // Reset the flag
        }

        refresh();
        halfdelay(1200); // Set a delay for getch
    }

    // End ncurses
    endwin();

    return 0;
}
