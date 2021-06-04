cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_BUILD_TYPE "Debug")

project(engine VERSION 0.0.1)

# glob all .cpp files in src directory
file(GLOB_RECURSE ENGINE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(engine main.cpp ${ENGINE_SRC})

# subdirectoires
add_subdirectory(deps)

target_link_libraries(engine PUBLIC glfw glad)
target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# custom targets
add_custom_target(
  test
  DEPENDS engine
  COMMAND ./engine)
