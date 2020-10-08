cmake_minimum_required (VERSION 2.6)

file(GLOB_RECURSE sources      ./src/*.cpp ./src/*.h)
project (TrainSig)
find_package(nlohmann_json 3.9.1 REQUIRED)
include_directories(./src/)
add_executable(TrainSig ${sources})
