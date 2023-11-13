# Root CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(SYSMONApp)

# Find and link against ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Add subdirectories
add_subdirectory(src)
add_subdirectory(app)
