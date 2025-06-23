#pragma once
#include <GL/gl.h>
#include <GL/glu.h>

class Camera {
private:
    float cameraX = 0;
    float cameraY = 0;
    float cameraZ = 1;
public:
    Camera(); // constructor declaration

    void move(float x, float y, float z);

    void update(float delta);
};