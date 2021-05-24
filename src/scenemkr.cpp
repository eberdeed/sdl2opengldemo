/**********************************************************
 *   SceneMkr:  A class for managing OpenGL objects.  
 *   This class allows for the loading and changing of skyboxes
 *   as well as calling the Model class for the loading of 3D assets.
 *   In this case the nanosuit and the cyborg.  The
 *   objects and the ideas came from www.learnopengl.com.
 *   Created by: Edward Charles Eberle <eberdeed@eberdeed.net>
 *   03/2020 San Diego, California USA
 * ********************************************************/
#include "../include/scenemkr.h"

//! Assign file names and setup buffers and arrays.
SceneMkr::SceneMkr(int width, int height)
{
    try
    {
        this->width = width;
        this->height = height;
        //FBO = colorTexture = RBO = 0;
        cout <<  "\n\n\tCreating SceneMkr.\n";
        image =  new CreateImage();
        for (int x = 0; x < 4; x++)
        {
            lightItem.position = pointLightPositions[x];
            lightItem.ambient = vec3(0.05f, 0.05f, 0.05f);
            lightItem.diffuse = vec3(1.0f, 1.0f, 1.0f);
            lightItem.specular = vec3(1.0f, 1.0f, 1.0f);
            lightItem.constant = 1.0f;
            lightItem.linear = 0.9f;
            lightItem.quadratic = 0.032f;
            lights.push_back(lightItem);
            spotItem.position = spotLightPositions[x];
            spotItem.direction = getDirection(spotItem.position, vec3(0.0f, 0.0f, 0.0f));
            spotItem.cutOff = 25.0f;
            spotItem.outerCutOff = 30.0f;
            spotItem.ambient = vec3(0.05f, 0.05f, 0.05f);
            spotItem.diffuse = vec3(1.0f, 1.0f, 1.0f);
            spotItem.specular = vec3(1.0f, 1.0f, 1.0f);
            spotItem.constant = 1.0f;
            spotItem.linear = 0.9f;
            spotItem.quadratic = 0.032f; 
            spotLights.push_back(spotItem);
        }
        camRadius = 20.0f;
        cameraPos = vec3(0.0f, 0.0f, camRadius);
        camFocus = vec3(0.0f, 0.0f, 0.0f);
        camera = new Camera(width, height, cameraPos, camFocus);        
        boxmodel = mat4(1.0f);
        boxmodel = scale(boxmodel, vec3(1000.0f, 1000.0f, 1000.0f));
        fnames[0][0] = "/usr/share/openglresources/skyboxes/mp_cloud9/cloud9_rt.tga";
        fnames[0][1] = "/usr/share/openglresources/skyboxes/mp_cloud9/cloud9_lf.tga";
        fnames[0][2] = "/usr/share/openglresources/skyboxes/mp_cloud9/cloud9_up.tga";
        fnames[0][3] = "/usr/share/openglresources/skyboxes/mp_cloud9/cloud9_dn.tga";
        fnames[0][4] = "/usr/share/openglresources/skyboxes/mp_cloud9/cloud9_ft.tga";
        fnames[0][5] = "/usr/share/openglresources/skyboxes/mp_cloud9/cloud9_bk.tga";
        
        fnames[1][0] = "/usr/share/openglresources/skyboxes/ely_hills/hills_rt.tga";
        fnames[1][1] = "/usr/share/openglresources/skyboxes/ely_hills/hills_lf.tga";
        fnames[1][2] = "/usr/share/openglresources/skyboxes/ely_hills/hills_up.tga";
        fnames[1][3] = "/usr/share/openglresources/skyboxes/ely_hills/hills_dn.tga";
        fnames[1][4] = "/usr/share/openglresources/skyboxes/ely_hills/hills_ft.tga";
        fnames[1][5] = "/usr/share/openglresources/skyboxes/ely_hills/hills_bk.tga";
        
        fnames[2][0] = "/usr/share/openglresources/skyboxes/hw_jungle/jungle_rt.tga";
        fnames[2][1] = "/usr/share/openglresources/skyboxes/hw_jungle/jungle_lf.tga";
        fnames[2][2] = "/usr/share/openglresources/skyboxes/hw_jungle/jungle_up.tga";
        fnames[2][3] = "/usr/share/openglresources/skyboxes/hw_jungle/jungle_dn.tga";
        fnames[2][4] = "/usr/share/openglresources/skyboxes/hw_jungle/jungle_ft.tga";
        fnames[2][5] = "/usr/share/openglresources/skyboxes/hw_jungle/jungle_bk.tga";
        
        fnames[3][0] = "/usr/share/openglresources/skyboxes/hw_sahara/sahara_rt.tga";
        fnames[3][1] = "/usr/share/openglresources/skyboxes/hw_sahara/sahara_lf.tga";
        fnames[3][2] = "/usr/share/openglresources/skyboxes/hw_sahara/sahara_up.tga";
        fnames[3][3] = "/usr/share/openglresources/skyboxes/hw_sahara/sahara_dn.tga";
        fnames[3][4] = "/usr/share/openglresources/skyboxes/hw_sahara/sahara_ft.tga";
        fnames[3][5] = "/usr/share/openglresources/skyboxes/hw_sahara/sahara_bk.tga";
        
        fnames[4][0] = "/usr/share/openglresources/skyboxes/lmcity/lmcity_rt.tga";
        fnames[4][1] = "/usr/share/openglresources/skyboxes/lmcity/lmcity_lf.tga";
        fnames[4][2] = "/usr/share/openglresources/skyboxes/lmcity/lmcity_up.tga";
        fnames[4][3] = "/usr/share/openglresources/skyboxes/lmcity/lmcity_dn.tga";
        fnames[4][4] = "/usr/share/openglresources/skyboxes/lmcity/lmcity_ft.tga";
        fnames[4][5] = "/usr/share/openglresources/skyboxes/lmcity/lmcity_bk.tga";
        
        fnames[5][0] = "/usr/share/openglresources/skyboxes/mp_ac/ac_rt.tga";
        fnames[5][1] = "/usr/share/openglresources/skyboxes/mp_ac/ac_lf.tga";
        fnames[5][2] = "/usr/share/openglresources/skyboxes/mp_ac/ac_up.tga";
        fnames[5][3] = "/usr/share/openglresources/skyboxes/mp_ac/ac_dn.tga";
        fnames[5][4] = "/usr/share/openglresources/skyboxes/mp_ac/ac_ft.tga";
        fnames[5][5] = "/usr/share/openglresources/skyboxes/mp_ac/ac_bk.tga";
        
        fnames[6][0] = "/usr/share/openglresources/skyboxes/mp_hexagon/hexagon_rt.tga";
        fnames[6][1] = "/usr/share/openglresources/skyboxes/mp_hexagon/hexagon_lf.tga";
        fnames[6][2] = "/usr/share/openglresources/skyboxes/mp_hexagon/hexagon_up.tga";
        fnames[6][3] = "/usr/share/openglresources/skyboxes/mp_hexagon/hexagon_dn.tga";
        fnames[6][4] = "/usr/share/openglresources/skyboxes/mp_hexagon/hexagon_ft.tga";
        fnames[6][5] = "/usr/share/openglresources/skyboxes/mp_hexagon/hexagon_bk.tga";
        
        fnames[7][0] = "/usr/share/openglresources/skyboxes/ely_nevada/nevada_rt.tga";
        fnames[7][1] = "/usr/share/openglresources/skyboxes/ely_nevada/nevada_lf.tga";
        fnames[7][2] = "/usr/share/openglresources/skyboxes/ely_nevada/nevada_up.tga";
        fnames[7][3] = "/usr/share/openglresources/skyboxes/ely_nevada/nevada_dn.tga";
        fnames[7][4] = "/usr/share/openglresources/skyboxes/ely_nevada/nevada_ft.tga";
        fnames[7][5] = "/usr/share/openglresources/skyboxes/ely_nevada/nevada_bk.tga";
        
        fnames[8][0] = "/usr/share/openglresources/skyboxes/ame_ash/ashcanyon_rt.tga";
        fnames[8][1] = "/usr/share/openglresources/skyboxes/ame_ash/ashcanyon_lf.tga";
        fnames[8][2] = "/usr/share/openglresources/skyboxes/ame_ash/ashcanyon_up.tga";
        fnames[8][3] = "/usr/share/openglresources/skyboxes/ame_ash/ashcanyon_dn.tga";
        fnames[8][4] = "/usr/share/openglresources/skyboxes/ame_ash/ashcanyon_ft.tga";
        fnames[8][5] = "/usr/share/openglresources/skyboxes/ame_ash/ashcanyon_bk.tga";
        
        fnames[9][0] = "/usr/share/openglresources/skyboxes/ely_snow/snow_rt.tga";
        fnames[9][1] = "/usr/share/openglresources/skyboxes/ely_snow/snow_lf.tga";
        fnames[9][2] = "/usr/share/openglresources/skyboxes/ely_snow/snow_up.tga";
        fnames[9][3] = "/usr/share/openglresources/skyboxes/ely_snow/snow_dn.tga";
        fnames[9][4] = "/usr/share/openglresources/skyboxes/ely_snow/snow_ft.tga";
        fnames[9][5] = "/usr/share/openglresources/skyboxes/ely_snow/snow_bk.tga";
        
        fnames[10][0] = "/usr/share/openglresources/skyboxes/hw_glacier/glacier_rt.tga";
        fnames[10][1] = "/usr/share/openglresources/skyboxes/hw_glacier/glacier_lf.tga";
        fnames[10][2] = "/usr/share/openglresources/skyboxes/hw_glacier/glacier_up.tga";
        fnames[10][3] = "/usr/share/openglresources/skyboxes/hw_glacier/glacier_dn.tga";
        fnames[10][4] = "/usr/share/openglresources/skyboxes/hw_glacier/glacier_ft.tga";
        fnames[10][5] = "/usr/share/openglresources/skyboxes/hw_glacier/glacier_bk.tga";
        
        fnames[11][0] = "/usr/share/openglresources/skyboxes/hw_morning/morning_rt.tga";
        fnames[11][1] = "/usr/share/openglresources/skyboxes/hw_morning/morning_lf.tga";
        fnames[11][2] = "/usr/share/openglresources/skyboxes/hw_morning/morning_up.tga";
        fnames[11][3] = "/usr/share/openglresources/skyboxes/hw_morning/morning_dn.tga";
        fnames[11][4] = "/usr/share/openglresources/skyboxes/hw_morning/morning_ft.tga";
        fnames[11][5] = "/usr/share/openglresources/skyboxes/hw_morning/morning_bk.tga";
        
        fnames[12][0] = "/usr/share/openglresources/skyboxes/skybox/right.jpg";
        fnames[12][1] = "/usr/share/openglresources/skyboxes/skybox/left.jpg";
        fnames[12][2] = "/usr/share/openglresources/skyboxes/skybox/top.jpg";
        fnames[12][3] = "/usr/share/openglresources/skyboxes/skybox/bottom.jpg";
        fnames[12][4] = "/usr/share/openglresources/skyboxes/skybox/front.jpg";
        fnames[12][5] = "/usr/share/openglresources/skyboxes/skybox/back.jpg";
        
        fnames[13][0] = "/usr/share/openglresources/skyboxes/mp_dot/dawn-of-time_rt.tga";
        fnames[13][1] = "/usr/share/openglresources/skyboxes/mp_dot/dawn-of-time_lf.tga";
        fnames[13][2] = "/usr/share/openglresources/skyboxes/mp_dot/dawn-of-time_up.tga";
        fnames[13][3] = "/usr/share/openglresources/skyboxes/mp_dot/dawn-of-time_dn.tga";
        fnames[13][4] = "/usr/share/openglresources/skyboxes/mp_dot/dawn-of-time_ft.tga";
        fnames[13][5] = "/usr/share/openglresources/skyboxes/mp_dot/dawn-of-time_bk.tga";
        
        fnames[14][0] = "/usr/share/openglresources/skyboxes/mp_downunder/down-under_rt.tga";
        fnames[14][1] = "/usr/share/openglresources/skyboxes/mp_downunder/down-under_lf.tga";
        fnames[14][2] = "/usr/share/openglresources/skyboxes/mp_downunder/down-under_up.tga";
        fnames[14][3] = "/usr/share/openglresources/skyboxes/mp_downunder/down-under_dn.tga";
        fnames[14][4] = "/usr/share/openglresources/skyboxes/mp_downunder/down-under_ft.tga";
        fnames[14][5] = "/usr/share/openglresources/skyboxes/mp_downunder/down-under_bk.tga";
        
        fnames[15][0] = "/usr/share/openglresources/skyboxes/mp_drakeq/drakeq_rt.tga";
        fnames[15][1] = "/usr/share/openglresources/skyboxes/mp_drakeq/drakeq_lf.tga";
        fnames[15][2] = "/usr/share/openglresources/skyboxes/mp_drakeq/drakeq_up.tga";
        fnames[15][3] = "/usr/share/openglresources/skyboxes/mp_drakeq/drakeq_dn.tga";
        fnames[15][4] = "/usr/share/openglresources/skyboxes/mp_drakeq/drakeq_ft.tga";
        fnames[15][5] = "/usr/share/openglresources/skyboxes/mp_drakeq/drakeq_bk.tga";
        
        fnames[16][0] = "/usr/share/openglresources/skyboxes/mp_druidcove/druidcove_rt.tga";
        fnames[16][1] = "/usr/share/openglresources/skyboxes/mp_druidcove/druidcove_lf.tga";
        fnames[16][2] = "/usr/share/openglresources/skyboxes/mp_druidcove/druidcove_up.tga";
        fnames[16][3] = "/usr/share/openglresources/skyboxes/mp_druidcove/druidcove_dn.tga";
        fnames[16][4] = "/usr/share/openglresources/skyboxes/mp_druidcove/druidcove_ft.tga";
        fnames[16][5] = "/usr/share/openglresources/skyboxes/mp_druidcove/druidcove_bk.tga";
        
        fnames[17][0] = "/usr/share/openglresources/skyboxes/mp_ec/ec_rt.tga";
        fnames[17][1] = "/usr/share/openglresources/skyboxes/mp_ec/ec_lf.tga";
        fnames[17][2] = "/usr/share/openglresources/skyboxes/mp_ec/ec_up.tga";
        fnames[17][3] = "/usr/share/openglresources/skyboxes/mp_ec/ec_dn.tga";
        fnames[17][4] = "/usr/share/openglresources/skyboxes/mp_ec/ec_ft.tga";
        fnames[17][5] = "/usr/share/openglresources/skyboxes/mp_ec/ec_bk.tga";
        
        fnames[18][0] = "/usr/share/openglresources/skyboxes/mp_elemental/elemental_rt.tga";
        fnames[18][1] = "/usr/share/openglresources/skyboxes/mp_elemental/elemental_lf.tga";
        fnames[18][2] = "/usr/share/openglresources/skyboxes/mp_elemental/elemental_up.tga";
        fnames[18][3] = "/usr/share/openglresources/skyboxes/mp_elemental/elemental_dn.tga";
        fnames[18][4] = "/usr/share/openglresources/skyboxes/mp_elemental/elemental_ft.tga";
        fnames[18][5] = "/usr/share/openglresources/skyboxes/mp_elemental/elemental_bk.tga";
        
        fnames[19][0] = "/usr/share/openglresources/skyboxes/mp_fcih/fat-chance-in-hell_rt.tga";
        fnames[19][1] = "/usr/share/openglresources/skyboxes/mp_fcih/fat-chance-in-hell_lf.tga";
        fnames[19][2] = "/usr/share/openglresources/skyboxes/mp_fcih/fat-chance-in-hell_up.tga";
        fnames[19][3] = "/usr/share/openglresources/skyboxes/mp_fcih/fat-chance-in-hell_dn.tga";
        fnames[19][4] = "/usr/share/openglresources/skyboxes/mp_fcih/fat-chance-in-hell_ft.tga";
        fnames[19][5] = "/usr/share/openglresources/skyboxes/mp_fcih/fat-chance-in-hell_bk.tga";
        
        fnames[20][0] = "/usr/share/openglresources/skyboxes/mp_firestorm/fire-storm_rt.tga";
        fnames[20][1] = "/usr/share/openglresources/skyboxes/mp_firestorm/fire-storm_lf.tga";
        fnames[20][2] = "/usr/share/openglresources/skyboxes/mp_firestorm/fire-storm_up.tga";
        fnames[20][3] = "/usr/share/openglresources/skyboxes/mp_firestorm/fire-storm_dn.tga";
        fnames[20][4] = "/usr/share/openglresources/skyboxes/mp_firestorm/fire-storm_ft.tga";
        fnames[20][5] = "/usr/share/openglresources/skyboxes/mp_firestorm/fire-storm_bk.tga";

        fnames[21][0] = "/usr/share/openglresources/skyboxes/mp_gatekeeper/gatekeeper_rt.tga";
        fnames[21][1] = "/usr/share/openglresources/skyboxes/mp_gatekeeper/gatekeeper_lf.tga";
        fnames[21][2] = "/usr/share/openglresources/skyboxes/mp_gatekeeper/gatekeeper_up.tga";
        fnames[21][3] = "/usr/share/openglresources/skyboxes/mp_gatekeeper/gatekeeper_dn.tga";
        fnames[21][4] = "/usr/share/openglresources/skyboxes/mp_gatekeeper/gatekeeper_ft.tga";
        fnames[21][5] = "/usr/share/openglresources/skyboxes/mp_gatekeeper/gatekeeper_bk.tga";
        
        fnames[22][0] = "/usr/share/openglresources/skyboxes/mp_goldrush/goldrush_rt.tga";
        fnames[22][1] = "/usr/share/openglresources/skyboxes/mp_goldrush/goldrush_lf.tga";
        fnames[22][2] = "/usr/share/openglresources/skyboxes/mp_goldrush/goldrush_up.tga";
        fnames[22][3] = "/usr/share/openglresources/skyboxes/mp_goldrush/goldrush_dn.tga";
        fnames[22][4] = "/usr/share/openglresources/skyboxes/mp_goldrush/goldrush_ft.tga";
        fnames[22][5] = "/usr/share/openglresources/skyboxes/mp_goldrush/goldrush_bk.tga";
        
        fnames[23][0] = "/usr/share/openglresources/skyboxes/mp_gritty/gritty-residue_rt.tga";
        fnames[23][1] = "/usr/share/openglresources/skyboxes/mp_gritty/gritty-residue_lf.tga";
        fnames[23][2] = "/usr/share/openglresources/skyboxes/mp_gritty/gritty-residue_up.tga";
        fnames[23][3] = "/usr/share/openglresources/skyboxes/mp_gritty/gritty-residue_dn.tga";
        fnames[23][4] = "/usr/share/openglresources/skyboxes/mp_gritty/gritty-residue_ft.tga";
        fnames[23][5] = "/usr/share/openglresources/skyboxes/mp_gritty/gritty-residue_bk.tga";

        fnames[24][0] = "/usr/share/openglresources/skyboxes/mp_habitual/habitual-pain_rt.tga";
        fnames[24][1] = "/usr/share/openglresources/skyboxes/mp_habitual/habitual-pain_lf.tga";
        fnames[24][2] = "/usr/share/openglresources/skyboxes/mp_habitual/habitual-pain_up.tga";
        fnames[24][3] = "/usr/share/openglresources/skyboxes/mp_habitual/habitual-pain_dn.tga";
        fnames[24][4] = "/usr/share/openglresources/skyboxes/mp_habitual/habitual-pain_ft.tga";
        fnames[24][5] = "/usr/share/openglresources/skyboxes/mp_habitual/habitual-pain_bk.tga";

        fnames[25][0] = "/usr/share/openglresources/skyboxes/mp_marvelous/bloody-marvelous_rt.tga";
        fnames[25][1] = "/usr/share/openglresources/skyboxes/mp_marvelous/bloody-marvelous_lf.tga";
        fnames[25][2] = "/usr/share/openglresources/skyboxes/mp_marvelous/bloody-marvelous_up.tga";
        fnames[25][3] = "/usr/share/openglresources/skyboxes/mp_marvelous/bloody-marvelous_dn.tga";
        fnames[25][4] = "/usr/share/openglresources/skyboxes/mp_marvelous/bloody-marvelous_ft.tga";
        fnames[25][5] = "/usr/share/openglresources/skyboxes/mp_marvelous/bloody-marvelous_bk.tga";
        cout <<  "\n\n\tDefined file names.\n";
    }
    catch(exception exc)
    {
        cout << "\n\n\tError filling sky box array:  " << exc.what() << "\n\n";
    }
    // Setup and compile our shaders
    try 
    {
        skyboxShader = new Shader();
        skyboxShader->initShader(vertexSkyShader, fragmentSkyShader, "demoboxskyboxshader.bin");
        shader = new Shader();
        shader->initShader(objectVertexShader, objectFragmentShader, "demoboxobjshader.bin");
        explodeShader = new Shader();
        explodeShader->initShader(explodeVertex, explodeFragment, "demoboxbanger.bin");
        cloudShader = new Shader();
        cloudShader->initShader(cloudVertex, cloudFragment, "demoboxcloud.bin");
        cout << "\n\n\tCreated shaders.\n";
        if (debug1)
        {
            UniformPrinter printit1(skyboxShader->Program);
            UniformPrinter printit2(shader->Program);
        }
        //! Create the nanosuit object.
        //! The individual item, reused many times.
        item = ModelInfo();
        //! The translation or location information.
        item.location = vec3(5.0f, 5.0f, 0.0f);
        //! The file name.
        item.path = "/usr/share/openglresources/nanosuit/nanosuit.blend";
        vertmodel = mat4(1.0f);
        vertmodel = translate(vertmodel, item.location);
        vertmodel = scale (vertmodel, vec3(0.8f, 0.8f, 0.8f));
        vertmodel = rotate(vertmodel, pi180, vec3(0.0f, 0.0f, 1.0f));
        //! The position and orientation matrix.
        item.model = vertmodel;
        item.idval = 0;
        item.diffOnly = false;
        item.gamma = 5.5f;
        //! Tack it onto the vector.
        modelinfo.push_back(item);
        item = ModelInfo();
        //! The file name.
        item.path = "/usr/share/openglresources/cyborg/cyborg.blend";
        item.location =  vec3(-5.0f, 5.0f, 0.0f);
        vertmodel = mat4(1.0f);
        //! The position and orientation matrix.
        vertmodel = translate(vertmodel, item.location);
        vertmodel = scale (vertmodel, vec3(3.0f, 3.0f, 3.0f));
        vertmodel = rotate(vertmodel, pi180, vec3(0.0f, 0.0f, 1.0f));
        item.model = vertmodel;
        item.diffOnly = false;
        item.idval = 1;
        item.gamma = 2.0f;
        //! Tack it onto the vector.
        modelinfo.push_back(item);
        figure = new Model(modelinfo, shader, explodeShader, cloudShader, 2);
        //! Set up the skybox VAO
        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        //! Create the skybox textures.
        for (int x = 0; x < 26; x++)
        {
            image->createSkyBoxTex(skyMaps[x], fnames[x]);
        }
        cubeMapTexture = skyMaps[0];
    }
    catch(exception exc)
    {
        cout << "\n\n\tError creating SceneMkr:  " << exc.what() << "\n\n";
    }
    intbegin  = chrono::system_clock::now();
}

//! delete the skybox array and index buffer.
SceneMkr::~SceneMkr()
{
    cout << "\n\n\tDestroying SceneMkr.\n\n";
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
    glDeleteTextures(26, skyMaps);
    delete figure;
    delete camera;
    delete image;
    delete skyboxShader;
    delete shader;
    delete explodeShader;
    delete cloudShader;
}
//! Draw the scene.
void SceneMkr::drawScene(int width, int height)
{
    try
    {
        this->width = width;
        this->height = height;
        intend = chrono::system_clock::now();
        delta = (float)
        //! Use timing to create a cameraSpeed variable.
        chrono::duration_cast<chrono::milliseconds>(intend -
        intbegin).count();
        interval = (int) delta;
        delta /= 100.0f;
        float thetacam = delta * onedegree;
        // Calculate the camera positon and front of camera values.
        cameraPos.x = camRadius * sin(thetacam);
        cameraPos.y = (camRadius / 2.0f) * sin(thetacam * 2.0f);
        cameraPos.z = camRadius * cos(thetacam);
        if (debug1)
        {
            cout << "\n\tDelta " << delta << " thetacam " << thetacam 
            << " interval " << interval << " interval % 5000 "  << interval % 5000;
        }
        if (interval > (count * NUM_MILLISECS))
        {
            count++;
            changeSkyBox();
        }
        if (count > 100000)
        {
          count  = 1;
        }
        camera->resizeView(width, height);
        camera->setPosition(cameraPos);
        camera->getEulerAngles();
        view = camera->getViewMatrix(); //! render
        projection = camera->getPerspective();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        skyboxShader->Use();
        skyboxShader->setMat4("view", view);
        skyboxShader->setMat4("projection", projection);
        skyboxShader->setMat4("model", boxmodel);
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
        skyboxShader->setInt("skybox", 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        glBindVertexArray(0);
        
        //! Pass into the shader the light definitions.
        shader->Use();
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
        shader->setInt("SkyBoxOne", 1);
        shader->setInt("debug", 0);
        for (int x = 0; x < modelinfo.size(); x++)
        {
            figure->Draw(x, view, projection, modelinfo, lights, spotLights, cameraPos);
        }
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
       
        if (debug1)
        {
            cout << "\n\n\tScreen dimensions:  " << width << ", " << height << "\n\n";
        }
    }
    catch(exception exc)
    {
        cout << "\n\n\tError drawing scene:  " << exc.what() << "\n\n";
    }
}

void SceneMkr::changeSkyBox()
{
    cout << "\n\n\tLooking at skybox " << val << ".\n\n";
    cubeMapTexture = skyMaps[val++];
    if (val >= 26)
    {
        val = 0;
    }
    
}
        
vec3 SceneMkr::getDirection(vec3 viewer, vec3 viewed)
{
    vec3 tmpval = normalize(viewed - viewer);
    cout << "\n\tViewer:  ";
    printVec3(viewer);
    cout <<  "  Viewed:  ";
    printVec3(viewed);
    cout << "  Direction:  ";
    printVec3(tmpval);
    cout << "\n";
    return(tmpval);
}

void SceneMkr::printVec3(vec3 vecVal)
{
    cout << "  3 Float Vector:  ";
    for  (int x = 0; x < 3; x++)
    {
        cout << vecVal[x] << ", ";
    }
}


