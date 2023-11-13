# app/CMakeLists.txt

# Source files
set(APP_SOURCE_FILES
    main.c
)

# Link the executable with the library and ncurses
add_executable(SYSMONApp ${APP_SOURCE_FILES})
target_link_libraries(SYSMONApp PRIVATE LinuxProcessLib ${CURSES_LIBRARIES})
