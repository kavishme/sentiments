cmake_minimum_required(VERSION 3.5)
project(sentiment)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES sentiment.cpp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.61.0 COMPONENTS filesystem chrono)
SET(OPENMP_CXX_FLAGS "-O3 -fopenmp")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPENMP_CXX_FLAGS}")

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(sentiment ${SOURCE_FILES})
    target_link_libraries(sentiment ${Boost_LIBRARIES})
endif()

#add_subdirectory(boost-cmake)

#cmake_minimum_required(VERSION 3.5)
#project(sentiment)
#
#set(CMAKE_CXX_STANDARD 11)
#
#set(SOURCE_FILES sentiment.cpp sentiment_wrap.cxx)
#
#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost 1.61.0 COMPONENTS filesystem chrono)
#SET(OPENMP_CXX_FLAGS "-O3 -fopenmp")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPENMP_CXX_FLAGS}")
#
#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS} "/usr/include/python2.7")
#    add_executable(sentiment ${SOURCE_FILES})
#    target_link_libraries(sentiment ${Boost_LIBRARIES} python2.7)
#endif()

#add_subdirectory(boost-cmake)

