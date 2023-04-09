cmake_minimum_required(VERSION 3.1)
project(ecs LANGUAGES CXX)

include_directories(include .)
add_executable(${PROJECT_NAME} main.cc Components.h SampleSystem.hpp)