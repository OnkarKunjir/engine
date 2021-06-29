cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

project(engine VERSION 0.0.1)

# glob all .cpp files in src directory
file(GLOB_RECURSE ENGINE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE ENGINE_HDR "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

add_library(engine ${ENGINE_SRC} ${ENGINE_HDR})

# subdirectoires
add_subdirectory(deps)

target_link_libraries(engine PUBLIC glfw glad stb_image glm::glm)
target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_executable(engine-test main.cpp)
target_link_libraries(engine-test engine)

# custom targets
add_custom_target(
  test
  DEPENDS engine-test
  COMMAND ./engine-test)

add_custom_target(
  update_assets COMMAND cp -ru "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
                        "${CMAKE_BINARY_DIR}/")

add_dependencies(engine update_assets)
