/**********************************************************
 *   SceneMkr:  A class for managing OpenGL objects.  
 *   This class allows for the loading and changing of skyboxes
 *   as well as calling the Model class for the loading of 3D assets.
 *   In this case the nanosuit and the cyborg.  The
 *   objects and the ideas came from www.learnopengl.com.
 *   Created by: Edward Charles Eberle <eberdeed@eberdeed.net>
 *   April 2020 San Diego, California USA
 * ********************************************************/
#ifndef SCENEMKR_H
#define SCENEMKR_H
#include "commonheader.h"
#include "createimage.h"
#include "shader.h"
#include "camera.h"
#include "info.h"
#include "uniformprinter.h"

/** \class SceneMkr A class to manage the loading and changing of sky boxes 
 *  as well as calling the Model class to load 3D assets.  In this case
 *  the nanosuit and the cyborg.  The skyboxes are changed by pre-loading the textures
 *  into an array of texture buffer handles and passing the drawing function a new buffer
 *  after NUM_MILLISECONDS time, which can be changed by changing the NUM_MILLISECONDS value
 *  in the commonheader.h file.
 */
class SceneMkr
{
public:
    /** \brief Constructor provides filenames for skyboxes. The shaders for the skybox are 
     * instantiated and the vertex array and textures for the skybox are pre-loaded from 
     * the filenames.
     */
    SceneMkr(int width, int height);
    ~SceneMkr();
    /** \brief Draw the sky box and call the Model class and through it the Mesh classes
     * to create the scene.
     */
    void drawScene(int width, int height);
    /** \brief Changes the skybox texture buffer by changing the index of the texture
     * buffer handle array.
     */
    void changeSkyBox();
protected:
    //! Find the direction towards an object.
    vec3 getDirection(vec3 viewer, vec3 viewed);
    //! print a vec3 value.
    void printVec3(vec3 vecVal);
    //! Class global variables.
    //! The shader programs;
    Shader *shader, *skyboxShader, *explodeShader, *cloudShader;
    //! Image to buffer class.
    CreateImage *image;
    //! Camera management.
    Camera *camera;
    //! Object creation and drawing for OpenGL.
    Model *figure;
    //! Bookeeping values.
    int width, height, val = 0, interval, count = 1;
    //! Camera position and focus object location.
    vec3 cameraPos, camFocus;
    //! The radius of the rotation around the objects and the change in time variable.
    float camRadius, delta;
     /** \brief A structure to contain the bulk of the
     *  configuration and mesh information for the given
     *  blender objects. See the info.h file for more information.
     */
    vector<ModelInfo>modelinfo;
    //! A single model definition value.
    ModelInfo item;
    //! A degree to radians conversion value.
    const float onedegree = (float) acos(-1.0f) / 180.0f;
    //! A 180 degree radian value.
    const float pi180 = acos(-1.0f);
    //! Transformation matrices for scaling, moving objects around, perspective and camera orientation.
    mat4 boxmodel, vertmodel, projection, view;
    //! Sky box buffer handles.
    GLuint cubeMapTexture;
    GLuint skyMaps[26];
    //! Vertex and buffer array handles.
    GLuint skyboxVAO, skyboxVBO;
    //! The array of filenames for the sky box images.
    string fnames[26][6];
    //! Turn on to debug, be sure to have something to catch the data.
    bool debug1 = false;
    //! Timing for the animation and the camera.
    chrono::system_clock::time_point intbegin, intend;
    //! Point light positions.
    vec3 pointLightPositions[4] = 
    {
        vec3( 20.0f,  10.0f,  20.0f),
        vec3( -20.0f,  10.0f,  -20.0f),
        vec3( -20.0f,  10.0f,  20.0f),
        vec3( 20.0f,  10.0f, -20.0f),
    };
    //! Positions of the spot lights.
    vec3 spotLightPositions[4] = 
    {
        vec3( 20.0f,  10.0f,  20.0f),
        vec3( -20.0f,  10.0f,  -20.0f),
        vec3( -20.0f,  10.0f,  20.0f),
        vec3( 20.0f,  10.0f, -20.0f),
    };
    //! Temporary variable to hold a point light.
    PointLight lightItem;
    //! The point light definition array.
    vector<PointLight> lights;
    //! Temporary variable to hold a spot light.
    SpotLight spotItem;
    //! The spot light definition array.
    vector<SpotLight> spotLights;
    //! Definition of the sky cube.
    GLfloat skyboxVertices[108] = {
        // Positions          
       -1.0f,  1.0f, -1.0f,
       -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
       -1.0f,  1.0f, -1.0f,
        
       -1.0f, -1.0f,  1.0f,
       -1.0f, -1.0f, -1.0f,
       -1.0f,  1.0f, -1.0f,
       -1.0f,  1.0f, -1.0f,
       -1.0f,  1.0f,  1.0f,
       -1.0f, -1.0f,  1.0f,
        
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        
       -1.0f, -1.0f,  1.0f,
       -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
       -1.0f, -1.0f,  1.0f,
        
       -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
       -1.0f,  1.0f,  1.0f,
       -1.0f,  1.0f, -1.0f,
        
       -1.0f, -1.0f, -1.0f,
       -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
       -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };
    string objectVertexShader = "/usr/share/openglresources/shaders/diffspecbinorm.vs";
    string objectFragmentShader = "/usr/share/openglresources/shaders/diffspecbinorm.frag";
    string vertexSkyShader = "/usr/share/openglresources/shaders/skyboxshader.vs";
    string fragmentSkyShader = "/usr/share/openglresources/shaders/skyboxshader.frag";
    string explodeVertex = "/usr/share/openglresources/shaders/explode.vs";
    string explodeFragment = "/usr/share/openglresources/shaders/explode.frag";
    string cloudVertex = "/usr/share/openglresources/shaders/cloud.vs";
    string cloudFragment = "/usr/share/openglresources/shaders/cloud.frag";
};

#endif // SCENEMKR_H
