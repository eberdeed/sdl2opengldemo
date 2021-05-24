/**********************************************************
 *   SDL2OpenGLDemo:  A class to display an arbitrary Blender
 *   object in OpenGL.  The objects and their locations are 
 *   passed into the program by the SceneMkr class.
 *   Blender can be found at www.blender.org and similarly
 *   OpenGL can be found at www.khronos.org.  To understand
 *   the inner workings of OpenGL I used the book:
 *   "OpenGL ES 3.0 Programming Guide Second Edition" 
 *   by Dan Ginsburg and Budirijanto Purnomo published by 
 *   Addison-Wesley 2014. Also useful was:  www.learnopengl.com.
 *   Created by: Edward Charles Eberle <eberdeed@eberdeed.net>
 *   March 2020 San Diego, California USA
 * ********************************************************/


#include "../include/sdl2opengldemo.h"


SDL2OpenGLDemo::SDL2OpenGLDemo()
{
    try
    {
        cout << "\n\n\tCreating SDL2OpenGLDemo\n\n";
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            logSDLError(cout, "SDL_Init");
            exit(1);
        }
        else
        {
            cout << "\n\n\tInitialized SDL.\n\n";
        }
        quit = false;
        width = SCR_WIDTH;
        height = SCR_HEIGHT;
        if (debug1)
        { 
            /* Simply create a thread */
            int i, count = SDL_GetNumAudioDevices(0);

            for (i = 0; i < count; ++i) {
                cout << "\n\n\tAudio device " << i << " with name " << SDL_GetAudioDeviceName(i, 0) << "\n\n";
            }
        }
        thread = SDL_CreateThread((SDL_ThreadFunction)SDL2OpenGLDemo::sndMaker, "TestThread", (void *)NULL);

        if (NULL == thread) {
            logSDLError(cout, "SDL_CreateThread failed");
        } else {
            cout << "\n\n\tSound thread successfully created.\n\n";
        }
        // Setup the window
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

        window = SDL_CreateWindow("OpenGL Demo", 200, 200, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
        if (window == nullptr){
            logSDLError(cout, "CreateWindow");
            SDL_Quit();
            exit(1);
        }
        else
        {
            cout << "\n\n\tCreated SDL window.\n\n";
        }
        
        context = SDL_GL_CreateContext(window);
        if (context == nullptr){
            logSDLError(cout, "CreateContext");
            SDL_DestroyWindow(window);
            SDL_GL_DeleteContext(context);
            SDL_Quit();
            exit(1);
        }
        else
        {
            cout << "\n\n\tCreated SDL context.\n\n";
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        if (renderer == nullptr){
            logSDLError(cout, "CreateRenderer");
            SDL_DestroyWindow(window);
            SDL_GL_DeleteContext(context);
            SDL_Quit();
            exit(1);
        }
        else
        {
            cout << "\n\n\tCreated renderer.\n";
        }
        SDL_GL_MakeCurrent(window, context);
        glewExperimental=true;
        GLenum err=glewInit();
        if(err!=GLEW_OK)
        {
            //Problem: glewInit failed, something is seriously wrong.
            cout<<"\n\n\tThe function glewInit failed, aborting."<<endl;
            exit(1);
        }
        else
        {
            cout << "\n\n\tInitialized glew.\n";
        }
        cout << "\n\n\tUsing GLEW Version: " << glewGetString(GLEW_VERSION) << "\n\n"; 
        glEnable(GL_DEPTH_TEST);  
        bool enabled = glIsEnabled(GL_DEPTH_TEST);
        if (enabled)
        {
            cout << "\n\n\tDepth Test Enabled\n\n";
        }
        else
        {
            cout << "\n\n\tDepth Test Not Enabled\n\n";
        }
        glDepthFunc(GL_LESS);
        //glFrontFace(GL_CCW);
        glDisable(GL_CULL_FACE);
        enabled = glIsEnabled(GL_CULL_FACE);
        if (enabled)
        {
            cout << "\n\n\tCull Face Enabled\n\n";
        }
        else
        {
            cout << "\n\n\tCull Face Not Enabled\n\n";
        }
        //glCullFace(GL_BACK);
        glDepthRange(0.1f, 1000.0f);
        glViewport(0, 0, width, height);
        scene = new SceneMkr(width, height);
        execLoop();
        SDL_WaitThread(thread, &threadReturnValue);
        cout << "\n\n\tThread returned value:  " << threadReturnValue << "\n\n";
    }
    catch(exception exc)
    {
        cout << "\n\n\tError intializing SDL2OpenGLDemo:  " << exc.what() << "\n\n";
    }
}

SDL2OpenGLDemo::~SDL2OpenGLDemo()
{
    cout << "\n\n\tDestroying SDL2OpenGLDemo\n\n";
    /** Deleting the objects produces destroy messages
     *  from the object deleted.
     */
    delete scene;
    exit(0);
}


void SDL2OpenGLDemo::execLoop()
{
    quit = false;
    SDL_Event e;
    //! render loop
    //! -----------
    while (!quit)
    {
        scene->drawScene(width, height);
        SDL_GL_SwapWindow(window);
        while (SDL_PollEvent(&e))
        {
            keyDown(e);
            windowEvent(e);
        };
    };
    // ------------------------------------------------------------------
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    this->~SDL2OpenGLDemo();
}


//! ---------------------------------------------------------------------------------------------------------
// process all input: query SDL2 whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void SDL2OpenGLDemo::keyDown(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN) 
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                quit = true;
                break;
            case SDLK_RALT:
                altSet = true;
                break;
            case SDLK_LALT:
                altSet = true;
                break;
            case SDLK_RETURN:
                if (altSet)
                {
                    cout << "\n\n\tSet window fullscreen.\n\n";
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    altSet = false;
                }
                break;

          }
     }
}    

void SDL2OpenGLDemo::windowEvent(SDL_Event e)
{
    if (e.type == SDL_WINDOWEVENT) {
        switch (e.window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            cout << "\n\n\tWindow " << e.window.windowID << " shown.\n\n";
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            cout << "\n\n\tWindow " << e.window.windowID << " hidden.\n\n";
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            cout << "\n\n\tWindow " << e.window.windowID << " exposed.\n\n";
            break;
        case SDL_WINDOWEVENT_MOVED:
            cout << "\n\n\tWindow " << e.window.windowID << " moved to " 
            << e.window.data1 << ", " << e.window.data2 << "\n\n";
            break;
        case SDL_WINDOWEVENT_RESIZED:
            cout << "\n\n\tWindow " << e.window.windowID << " resized to " 
            << e.window.data1 << ", " << e.window.data2 << "\n\n";
            width = (unsigned  int)e.window.data1;
            height = (unsigned  int)e.window.data2;
            glViewport(0, 0, e.window.data1, e.window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            cout << "\n\n\tWindow " << e.window.windowID << " size changed to " 
            << e.window.data1 << ", " << e.window.data2 << "\n\n";
            width = (unsigned  int)e.window.data1;
            height = (unsigned  int)e.window.data2;
            glViewport(0, 0, e.window.data1, e.window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            cout << "\n\n\tWindow " << e.window.windowID << " minimized.\n\n";
            width = (unsigned  int)0;
            height = (unsigned  int)0;
            glViewport(0, 0, 0, 0);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            cout << "\n\n\tWindow " << e.window.windowID << " maximized.\n\n";
            width = (unsigned int)e.window.data1;
            height = (unsigned int)e.window.data2;
            SDL_SetWindowSize(window, width, height);
            glViewport(0, 0, width, height);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            cout << "\n\n\tWindow " << e.window.windowID << " restored.\n\n";
            break;
        case SDL_WINDOWEVENT_ENTER:
            cout << "\n\n\tMouse entered window " << e.window.windowID << ".\n\n";
            break;
        case SDL_WINDOWEVENT_LEAVE:
            cout << "\n\n\tMouse left window " << e.window.windowID << ".\n\n";
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            cout << "\n\n\tWindow " << e.window.windowID << " gained keyboard focus.\n\n";
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            cout << "\n\n\tWindow " << e.window.windowID << " lost keyboard focus.\n\n";
            break;
        case SDL_WINDOWEVENT_CLOSE:
            cout << "\n\n\tWindow " << e.window.windowID << " closed.\n\n";
            quit = true;
            break;
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            cout << "\n\n\tWindow " << e.window.windowID << " is offered focus.\n\n";
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            cout << "\n\n\tWindow " << e.window.windowID << " has a special hit test.\n\n";
            break;
        default:
            cout << "\n\n\tWindow " << e.window.windowID << " received an unknown event.\n\n";
            break;
        }
    }
}

void SDL2OpenGLDemo::logSDLError(ostream &os, const string &msg)
{
    os << "\n\n\t" << msg << " error: " << SDL_GetError() << "\n\n";
}


void SDL2OpenGLDemo::sndMaker()
{
    Uint32 wave_len1, wave_len2; // length of our sample
    Uint8 *wave_buf1, *wave_buf2; // buffer containing our audio file
    int result = 0;
    SDL_AudioSpec wave_spec, ret_spec; // the specs of our piece of music
    cout << "\n\n\tStarting sound production.";
    cout << "\n\tLoading WAV file.\n\n";
    try
    {
        if (SDL_LoadWAV("/usr/share/openglresources/sound/gamelan.wav", &wave_spec, &wave_buf1, &wave_len1) ==  NULL)
        {
            cout << "\n\n\tUnable to load WAV file:  " << SDL_GetError() << "\n\n";
        }
        else
        {
            cout << "\n\n\tWAV file successfully loaded.\n\n";
        }
        if (SDL_LoadWAV("/usr/share/openglresources/sound/meditation.wav", &wave_spec, &wave_buf2, &wave_len2) ==  NULL)
        {
            cout << "\n\n\tUnable to load WAV file:  " << SDL_GetError() << "\n\n";
        }
        else
        {
            cout << "\n\n\tWAV file successfully loaded.\n\n";
        }
        string name  = SDL_GetAudioDeviceName(0, 0);
        cout << "\n\n\tAudio device:  " << name << "\n\n";
        SDL_AudioDeviceID dev = SDL_OpenAudioDevice(name.c_str(), 0, &wave_spec, &ret_spec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
        if (dev < 0)
        {
            cout << "\n\n\tUnable to open audio device:  " << SDL_GetError() << "\n\n";
        }
        else
        {
            cout << "\n\n\tAudio device successfully opened for 2 WAV files with length:  "  << wave_len1 
            << ", " << wave_len2 << ".\n\n";
            result = SDL_QueueAudio(dev, wave_buf1, wave_len1);
            if (result != 0)
            {
                cout <<  "\n\n\tUnable to queue audio data.\n\n";
            }
            else
            {
                cout << "\n\n\tAudio data successfully queued.\n\n";
            }
        }
        while (!quit)
        {
            SDL_PauseAudioDevice(dev, 0); /* start audio playing. */
            cout << "\n\n\tPlayed the audio.\n\n";
            SDL_Delay(196000); /* let the audio callback play some sound for 1543 seconds. */
            result = SDL_QueueAudio(dev, wave_buf2, wave_len2);
            if (result != 0)
            {
                cout <<  "\n\n\tUnable to queue audio data.\n\n";
            }
            else
            {
                cout << "\n\n\tAudio data successfully queued.\n\n";
            }
            SDL_PauseAudioDevice(dev, 0); /* start audio playing. */
            SDL_Delay(382000); /* let the audio callback play some sound for 2034 seconds. */
            result = SDL_QueueAudio(dev, wave_buf1, wave_len1);
            if (result != 0)
            {
                cout <<  "\n\n\tUnable to queue audio data.\n\n";
            }
            else
            {
                cout << "\n\n\tAudio data successfully queued.\n\n";
            }
        }
        SDL_CloseAudioDevice(dev);
        cout << "\n\n\tClosed audio device.\n\n";
        SDL_FreeWAV(wave_buf1);
        SDL_FreeWAV(wave_buf2);
    }
    catch(exception exc)
    {
        cout << "\n\n\tError on audio output:  " << exc.what() << "\n\n";
    }
}
