############################################################
#   The CMake File for SDL2OpenGLDemo.  It provides for
#   the following libraries:  Boost, GLM, GL, GLEW,
#   stdc++, freeimageplus, SDL2, assimp and pthread.
#   Created by Edward C. Eberle <eberdeed@ebedeed.net>
#   March 2020 San Diego California USA
############################################################
cmake_minimum_required(VERSION 3.12)
if(POLICY CMP0015)
  cmake_policy(SET CMP0015 NEW)
endif()
project(sdl2opengldemo)
add_executable(sdl2opengldemo sdl2opengldemo.cpp camera.cpp scenemkr.cpp uniformprinter.cpp)
add_definitions(-g -fPIC -std=c++17 -pthread)
include_directories(/usr/local/include /usr/include/glm /usr/include/GL
/usr/include/assimp /usr/include/boost /usr/local/include/SDL2 ../assimpopengl/include)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib /usr/lib/llvm-7/lib ../assimpopengl/src)
target_link_libraries(sdl2opengldemo stdc++ GL GLEW SDL2-2.0 freeimage freeimageplus 
boost_filesystem boost_system assimp assimpopengl pthread)
install(TARGETS sdl2opengldemo DESTINATION /usr/bin)
