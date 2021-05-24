/**********************************************************
 *   SDL2OpenGLDemo:  A class to display an arbitrary Blender
 *   object in OpenGL.  The objects and their locations are 
 *   passed into the program by the SceneMkr class.
 *   Blender can be found at www.blender.org and similarly
 *   OpenGL can be understood at www.khronos.org.  To understand
 *   the inner workings of OpenGL I used the book:
 *   "OpenGL ES 3.0 Programming Guide Second Edition" 
 *   by Dan Ginsburg and Budirijanto Purnomo published by 
 *   Addison-Wesley 2014. Also useful was:  www.learnopengl.com.
 *   SDL2 can be found at https://wiki.libsdl.org.
 *   Created by: Edward Charles Eberle <eberdeed@eberdeed.net>
 *   03/2020 San Diego, California USA
 * ********************************************************/

#ifndef SDL2OPENGLDEMO_Hmake
#define SDL2OPENGLDEMO_H

#include "commonheader.h"
#include "scenemkr.h"

/**   \class SDL2OpenGLDemo A class to display an arbitrary 
 *   blender object in OpenGL.  The objects and their 
 *   locations are passed into the program by the SceneMkr class.  
 *   SDL2 is used to provide windowing support and sound.
 */
class SDL2OpenGLDemo
{
public:
    /** \brief The constructor initializes data and starts up the sound.
     */
    SDL2OpenGLDemo();
    /** \brief The destructor deletes pointers and objects.
     */
    ~SDL2OpenGLDemo();
    /** \brief  Execution loop for rendering everything.
     */
    void execLoop();
protected:
    //! SDL2 Display variables.
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext context;
    SceneMkr *scene;
    /** \brief Keystroke processing.
     */
    void keyDown(SDL_Event e);
    /** \brief Window resize function.
     */
    void windowEvent(SDL_Event e);
    /** \brief An error output function that takes an
     *  output stream to define where it goes.
     */
    void logSDLError(ostream &os, const string &msg);
    /** \brief A static sound creation function
     *  that can fit in a thread.
     */
    static void sndMaker();
    //! A thread to hold the sound function.
    SDL_Thread *thread;
    //! Initial screen size values.
    const unsigned int SCR_WIDTH = 1000;
    const unsigned int SCR_HEIGHT = 800;
    //! Dynamic screen size values.
    unsigned int width, height;
    //! Booleans for program flow.
    bool firstMouse = true, altSet = false;
    //! A degree to radians conversion value.
    const float onedegree = acos(-1) / 180.0f;
    //! Mouse pointer location variables.
    float xpos, ypos, lastX, lastY;
    //! Thread return value.
    int threadReturnValue;
    //! Catch the data!
    bool debug1 = false;
};

//! A classless variable that is avoiding being static.
bool quit = false;

#endif // SDL2OPENGLDEMO_H

/** \brief The simplest main possible.
 */
int main(int argc, char **argv)
{
    SDL2OpenGLDemo blendit;
    return 0;
}
