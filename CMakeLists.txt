cmake_minimum_required (VERSION 3.5)
project (gatery-template)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/) 
INCLUDE(libs/gatery/cmake/GtryCompileResourceFile.cmake)

add_subdirectory(libs/gatery/)

find_package(Boost COMPONENTS system filesystem thread iostreams json REQUIRED)

file(GLOB_RECURSE srcs
    "source/*.cpp" "source/*.h"
)

add_executable(gatery_template ${srcs})

target_include_directories (gatery_template PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries (gatery_template
    gatery
)
