file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/*.h")

add_library("glad" ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories("glad" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
