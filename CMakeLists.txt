cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_BUILD_TYPE "Debug")

project(engine VERSION 0.0.1)


add_executable(engine main.cpp)

add_custom_target(
  test
  DEPENDS engine
  COMMAND ./engine < input.txt
  )
