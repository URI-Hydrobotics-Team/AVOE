cmake_minimum_required(VERSION 3.10)
project(stonefish_sim)

# Find required packages
find_package(Stonefish REQUIRED 1.3.0)

# Add the executable
add_executable(avoe-frontend-stonefish main.cpp simulation_manager.cpp vehicle_refresh.cpp 
../../lib/network.cpp ../../lib/clock.cpp ../../lib/lib.cpp ../../lib/vt100.cpp ../../core/io.cpp ../../core/sensor.cpp ../../core/log.cpp ../../core/motor.cpp
)



include_directories(
	../../lib/network
	../../core
    /usr/local/include
    /usr/local/include/Stonefish
    /usr/local/include/Stonefish/graphics
    /usr/local/include/Stonefish/physics
    /usr/local/include/Stonefish/simulation
    /usr/local/include/Stonefish/entities/
)

# Specify the directory containing the Stonefish library
target_link_libraries(avoe-frontend-stonefish PUBLIC Stonefish::Stonefish)
