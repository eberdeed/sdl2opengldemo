############################################################
#   The CMake File for SDL2OpenGLDemo.  It provides for
#   the following libraries:  Boost, GLM, GL, GLEW,
#   stdc++, freeimageplus, SDL2, assimp, pthread.
#   Created by Edward C. Eberle <eberdeed@ebedeed.net>
#   March 2020 San Diego California USA
############################################################
cmake_minimum_required(VERSION 3.12)
project(sdl2opengldemo)
add_subdirectory(assimpopengl)
add_subdirectory(src)
find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN YES)
set(PROJECT_NAME "The OpenGL Demo")
set(PROJECT_BRIEF "A program to display blender objects in a variety of sky boxes.")
doxygen_add_docs(doc include src assimpopengl/include assimpopengl/src COMMENT "Generating documentation.")
install(DIRECTORY openglresources DESTINATION /usr/share FILE_PERMISSIONS WORLD_READ)
install(DIRECTORY assimpopengl/LGPL DESTINATION /usr/share/doc/sdl2opengldemo-doc FILE_PERMISSIONS WORLD_READ)
install(DIRECTORY build/html DESTINATION /usr/share/doc/sdl2opengldemo-doc FILE_PERMISSIONS WORLD_READ)
install(DIRECTORY build/man DESTINATION /usr/share/doc/sdl2opengldemo-doc FILE_PERMISSIONS WORLD_READ)
install(FILES README.txt CHANGELOG.txt sdl2opengldemowriteup.odt sdl2opengldemowriteup.pdf
DESTINATION /usr/share/doc/sdl2opengldemo-doc PERMISSIONS WORLD_READ)
