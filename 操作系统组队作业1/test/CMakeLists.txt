cmake_minimum_required(VERSION 3.0.0)
project(test)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(./ SRC)
include_directories(${HEADPATH})
link_directories(${LIBPATH})
link_libraries(${LIBNAME})
set(EXECUTABLE_OUTPUT_PATH ${EXEPATH})
add_executable(${TESTNAME} ${SRC})