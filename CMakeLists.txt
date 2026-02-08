cmake_minimum_required(VERSION 3.10)
project(avoe)

#Adds the cmake file in the lib directory see that one
add_subdirectory(lib)

#Adds the cmake directory in the plugins directory
add_subdirectory(plugins)


#makes the executable onto the main
add_executable(avoe ./core/main.cpp)
#adds the core stuff
target_sources(avoe PRIVATE 
core/mission.cpp
core/motor.cpp
core/sensor.cpp
core/vehicle.cpp
core/log.cpp
core/io.cpp
)

#links the directory file from above
target_link_libraries(avoe PRIVATE lib plugins)


