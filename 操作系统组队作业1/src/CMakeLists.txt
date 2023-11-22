cmake_minimum_required(VERSION 3.0.0)
project(src)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(./ SRC)
include_directories(${HEADPATH})
set(LIBRARY_OUTPUT_PATH ${LIBPATH})
add_library(${LIBNAME} STATIC ${SRC})
