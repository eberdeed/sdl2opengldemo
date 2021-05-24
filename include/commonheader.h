/*******************************************************************
 * CommonHeader:  A header file to reduce repetition of #define
 * and #include statements.
 * Edward C. Eberle <eberdeed@eberdeed.net>
 * March 2020 San Diego, California USA
 * Copyright Maureen A. Quinn 03/2020
****************************************************************/

#ifndef COMMONHEADER_H
//! The defines.
#define COMMONHEADER_H
//! The number of milliseconds each background appears.
#define NUM_MILLISECS 5000
//! GLEW The OpenGL library manager
#define GLEW_STATIC
#include <glew.h>
//! GLM The OpenGL math library
#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/matrix_interpolation.hpp>
#include <gtc/matrix_access.hpp> 
#include <gtx/euler_angles.hpp>
// SDL The Simple Direct Media Layer
#include <SDL.h>
//! Assimp the Asset Importation Library
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include <material.h>
#include <mesh.h>

//! Std C++
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <cmath>
#include <exception>
#include <fstream>
#include <vector>
#include <algorithm>

//! Free Image Plus
#include <FreeImagePlus.h>
#include <FreeImage.h>

//! Boost
#include <filesystem.hpp>

//! Mine 
#include <assimpopengl.h>

//! The namespaces used.
using namespace std;
using namespace glm;
using namespace boost::filesystem;


#endif // COMMONHEADER_H
