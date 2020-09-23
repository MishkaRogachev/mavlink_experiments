# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
project(mavlink_experiments)

# CMake modules
include(cmake/RecurseSubdirs.cmake)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Add compiler flags
add_compile_options(-std=c++11 -Wall)

# Enable Qt modules
find_package(Qt5 COMPONENTS Core Network SerialPort Positioning REQUIRED)

# Global libraries
set(LIBRARIES
# Qt5
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
    Qt5::Positioning
)

# Include mavlink headers globaly
include_directories("3dparty/mavlink_v2")
include_directories("3dparty/mavlink_v2/ardupilotmega")

# Subdirectories
add_subdirectory(common)
add_subdirectory(uav)
add_subdirectory(gcs)
