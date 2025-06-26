#pragma once
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
// #include "include/stb/stb_image_write.h"
#include "Camera.h"
#include "ShaderM.h"

class MapChunk {
private:
    float positionX = 0.0;
    float positionY = 0.0;
    float positionZ = 0.0;
    Camera camera;
    float screenWidth, screenHeight;
    int numStrips;
    int numVertPerStrip;
    GLuint terrainVAO, terrainVBO, terrainEBO;
    Shader heightMapShader;
public:
    MapChunk(); // constructor declaration

    void setScreen(float width, float height);

    void setCamera(Camera camera);
    
    void generate();

    void render();

    void destroy();

};