cmake_minimum_required(VERSION 3.13)  # CMake version check
project(run)
set(CMAKE_CXX_STANDARD 17)            # Enable C++17 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Matplot++ REQUIRED)

add_subdirectory(src)