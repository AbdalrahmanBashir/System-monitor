# src/CMakeLists.txt

# Source files
set(SOURCE_FILES

    system_monitor.c
    system_parser.c
    process_manager.c
    display_system_info.c
    process.c

)

# Header files
set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/system_monitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/system_parser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/process_manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/display_system_info.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/process.h
)

# Create a library
add_library(LinuxProcessLib ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(LinuxProcessLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
