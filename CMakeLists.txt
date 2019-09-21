cmake_minimum_required(VERSION 3.14)
project(rfoutlet)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.67.0 COMPONENTS system filesystem thread REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

find_library(wiringPi_LIB wiringPi)

add_subdirectory(hiredis)

add_subdirectory(src)

add_executable(rfoutlet
        src/main.cpp
        src/RCSwitch.cpp
        src/OutletController.cpp
        src/SimpleSerial.cpp
        include/PlantExceptions.h
        src/PlantWatcher.cpp
        src/CacheIO.cpp
        include/BasePlantIO.h include/ScpSender.h include/PhotoHandler.h)

target_include_directories(rfoutlet PRIVATE include hiredis)
target_link_libraries(rfoutlet stdc++fs hiredis ${wiringPi_LIB} ${Boost_LIBRARIES})