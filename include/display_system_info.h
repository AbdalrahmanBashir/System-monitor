#pragma once
#ifndef DISPLAY_SYSTEM_INFO_H
#define DISPLAY_SYSTEM_INFO_H

#include "process.h"
#include "system_monitor.h"
#include "system_parser.h"
#include <ncurses.h>

char DisplayProgressBar(WINDOW* window, float percent, int row, int col);
char* FormatElapsedTime(WINDOW* mainwin, long seconds, int row, int col);
void DisplaySystemInfo(WINDOW* mainwin, System* system, int scroll_offset);


#endif
