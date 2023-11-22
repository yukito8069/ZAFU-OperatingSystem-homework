cmake_minimum_required(VERSION 3.0.0)

project(homework)
set(CMAKE_CXX_STANDARD 20)
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)
set(EXEPATH ${PROJECT_SOURCE_DIR}/bin) 
set(HEADPATH ${PROJECT_SOURCE_DIR}/include)
set(LIBNAME libname)
set(TESTNAME test1)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
