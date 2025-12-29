cmake_minimum_required(VERSION 3.10)
project(UltimateSim VERSION 1.0)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find SDL2
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(src)
include_directories(src/rendering)
include_directories(src/simulation)
include_directories(src/utils)

# Source files
set(SOURCES
    src/main.c
    src/rendering/renderer.c
    src/rendering/camera.c
    src/simulation/simulation.c
    src/utils/math_utils.c
)

# Create executable
add_executable(ultimatesim ${SOURCES})

# Link SDL2
target_link_libraries(ultimatesim ${SDL2_LIBRARIES})

# For macOS, link Cocoa framework
if(APPLE)
    target_link_libraries(ultimatesim "-framework Cocoa")
endif()

# Optional: Copy assets to build directory
if(WIN32)
    # Copy assets folder on Windows
    add_custom_command(TARGET ultimatesim POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:ultimatesim>/assets
    )
endif()
