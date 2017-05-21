cmake_minimum_required(VERSION 3.5)
project(sentiment)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.61.0 COMPONENTS filesystem)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(sentiment ${SOURCE_FILES})
    target_link_libraries(sentiment ${Boost_LIBRARIES})
endif()

#add_subdirectory(boost-cmake)

