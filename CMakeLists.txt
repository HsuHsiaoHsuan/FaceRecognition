cmake_minimum_required( VERSION 2.8 )
project( app )

find_package( OpenCV REQUIRED )

#set( FLYCAP_INCLUDE "/usr/include/flycapture" )
#include_directories( ${FLYCAP_INCLUDE} )

add_executable( app face.cpp)
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

#target_link_libraries( app ${OpenCV_LIBS} -lflycapture tesseract )
target_link_libraries( app ${OpenCV_LIBS} )
