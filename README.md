# System Monitor

A real-time system monitoring application built in C that provides a comprehensive view of system resources, processes, and performance metrics using an ncurses-based terminal interface.

## Features

### System Information Display
- **CPU Utilization**: Real-time display of CPU usage across different states (User, Nice, System, Idle, IOWait, IRQ, SoftIRQ, Steal)
- **Memory Utilization**: Visual progress bar showing current memory usage percentage
- **System Uptime**: Formatted display of system uptime in days, hours, minutes, and seconds
- **Operating System**: Display of OS name and kernel version
- **Process Statistics**: Total number of processes and running processes

### Process Management
- **Process List**: Real-time display of running processes with detailed information:
  - Process ID (PID)
  - Username
  - CPU usage percentage
  - Memory usage (RAM)
  - Process uptime
  - Command name
- **Process Control**: Ability to kill processes by PID
- **Scrolling**: Navigate through process list using arrow keys

### User Interface
- **Terminal-based UI**: Built with ncurses for a clean, responsive interface
- **Real-time Updates**: Automatic refresh of system information
- **Interactive Controls**: Keyboard-based navigation and process management
- **Progress Bars**: Visual representation of resource utilization

## Project Structure

```
System-monitor/
├── CMakeLists.txt              # Root CMake configuration
├── include/                    # Header files
│   ├── display_system_info.h   # UI display functions
│   ├── process.h              # Process data structure and functions
│   ├── process_manager.h      # Process control functions
│   ├── system_monitor.h       # Main system monitoring interface
│   └── system_parser.h        # System information parsing
├── src/                       # Source files
│   ├── CMakeLists.txt         # Library build configuration
│   ├── display_system_info.c  # UI implementation
│   ├── process.c              # Process management implementation
│   ├── process_manager.c      # Process control implementation
│   ├── system_monitor.c       # System monitoring implementation
│   └── system_parser.c        # System data parsing implementation
└── app/                       # Application entry point
    ├── CMakeLists.txt         # Executable build configuration
    └── main.c                 # Main application loop
```

## Dependencies

- **CMake** (version 3.10 or higher)
- **ncurses** library
- **C compiler** (GCC recommended)
- **Linux system** (uses `/proc` filesystem)

## Building the Project

### Prerequisites

1. Install required packages on Ubuntu/Debian:
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential cmake libncurses5-dev libncursesw5-dev
   ```

2. Install required packages on CentOS/RHEL/Fedora:
   ```bash
   sudo yum install gcc cmake ncurses-devel
   # or for newer versions:
   sudo dnf install gcc cmake ncurses-devel
   ```

### Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/AbdalrahmanBashir/System-monitor.git
   cd System-monitor
   ```

2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Configure and build:
   ```bash
   cmake ..
   make
   ```

4. Run the application:
   ```bash
   ./SYSMONApp
   ```

## Usage

### Starting the Application
```bash
./SYSMONApp
```

### Controls
- **Arrow Keys**: Navigate through the process list
  - `↑` (Up Arrow): Scroll up through processes
  - `↓` (Down Arrow): Scroll down through processes
- **k**: Kill a process (prompts for PID)
- **q**: Quit the application

### Process Management
1. Press `k` to enter process kill mode
2. Enter the PID of the process you want to terminate
3. The system will attempt to kill the process with SIGTERM
4. A success/error message will be displayed

## Technical Details

### System Information Sources
- **CPU Data**: Parsed from `/proc/stat`
- **Memory Data**: Parsed from `/proc/meminfo`
- **Process Data**: Retrieved from `/proc/[pid]/` directories
- **System Uptime**: Retrieved using `sysinfo()` system call
- **OS Information**: Retrieved using `uname()` system call

### Key Components

#### System Parser (`system_parser.c`)
- Handles all low-level system information retrieval
- Parses `/proc` filesystem data
- Provides functions for CPU, memory, and process statistics

#### Process Manager (`process_manager.c`)
- Manages process control operations
- Handles signal sending to processes
- Provides process termination functionality

#### Display System Info (`display_system_info.c`)
- Manages the ncurses user interface
- Handles screen updates and formatting
- Provides progress bars and time formatting

#### System Monitor (`system_monitor.c`)
- High-level system monitoring interface
- Manages system data structures
- Provides unified access to system information


## Error Handling

The application includes comprehensive error handling for:
- File system access errors
- Memory allocation failures
- Process management errors
- UI rendering issues

## Performance Considerations

- Efficient parsing of `/proc` filesystem
- Minimal memory allocation and deallocation
- Non-blocking input handling
- Optimized screen refresh rates

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Ensure the code compiles without warnings
5. Test the functionality
6. Submit a pull request

## License

MIT License

Copyright (c) 2025 Abdalrahman Bashir

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.



## Future Enhancements

- Network interface monitoring
- Disk I/O statistics
- Temperature monitoring
- Process tree visualization
- Configuration file support
- Logging functionality
- Remote monitoring capabilities 