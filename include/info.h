/*******************************************************************
 * Info:  A header file to allow classes to access the blender 
 * object model structure. It is needed to use the assimpopengl
 * library included in this package.
 * Edward C. Eberle <eberdeed@eberdeed.net>
 * March 2020 San Diego, California USA
 ****************************************************************/

#ifndef INFO_H
#define INFO_H
#include "commonheader.h"
#include "mesh.h"
/** \brief A series of structures to encapsulate:
 * 1.  The meshes and textures of a blender object
 * (each mesh may have multiple textures). 
 * vector<MeshInfo> meshes;
 * 2.  The location of the blender object in the file
 * structure.
 * string path;
 * 3. The affine transform matrix defining position 
 * and orientation. 
 * mat4 model;
 * 4. Location is provided so a sort by distance so 
 * the camera can be instituted.
 * vec3 location;
 * 5. A distance variable so the vector can
 * be sorted by distance.
 * int dist = 0;
 * 6. An identification value so the vector
 * can be sorted into it's original order.
 * int idval = 0;
 * 7. A boolean to identify diffuse only objects.
 * bool diffOnly = true;
 * 8. A gamma variable to control brightness.
 * float gamma = 1.0f;
 */
//! The mesh and associated textures.
struct MeshInfo {
    Mesh* mesh;
    vector<Texture>textures;
};
//! The blender objects definition in the program.
struct ModelInfo {
    string path;
    vector<MeshInfo> meshes;
    mat4 model;
    vec3 location;
    int dist = 0;
    int idval = 0;
    bool diffOnly = true;
    float gamma = 1.0f;
};

#endif // INFO_H
