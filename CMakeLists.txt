# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
project(mavlink_experiments)

# CMake modules
include(cmake/RecurseSubdirs.cmake)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add compiler flags
add_compile_options(-std=c++11 -Wall)

# Enable Qt modules
find_package(Qt5 COMPONENTS Core Network SerialPort REQUIRED)

# Global libraries
set(LIBRARIES
# Qt5
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
)

# Include mavlink headers globaly
HEADER_DIRECTORIES(MAVLINK_INCLUDES "3dparty/mavlink_v1")

# Subdirectories
# add_subdirectory(common)
# add_subdirectory(uav)
# add_subdirectory(gcs)
