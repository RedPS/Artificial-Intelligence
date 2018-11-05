cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 14)
project(Spam VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(training src/training.cc)
add_executable(classify src/classify.cc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
