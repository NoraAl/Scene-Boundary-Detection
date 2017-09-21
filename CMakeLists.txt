cmake_minimum_required(VERSION 2.8)
project( detectScenes )
find_package( OpenCV 3.2.0 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( detectScenes main.cpp process.cpp allHistograms.cpp segment.cpp )
target_link_libraries( detectScenes ${OpenCV_LIBS} )

