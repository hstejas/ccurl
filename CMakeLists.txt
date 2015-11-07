#Specipecify the version being used aswell as the language
cmake_minimum_required(VERSION 2.6)
#Name your project here
project(ccurl)

#Sends the -std=c++11 flag to the gcc compiler
add_definitions(-std=c++11)
add_library( ccurl STATIC ccurl.cpp)

find_package (CURL)
if (CURL_FOUND)
  include_directories(${CURL_INCLUDE_DIRS})
  target_link_libraries (ccurl ${CURL_LIBRARIES})
endif (CURL_FOUND)
