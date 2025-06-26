#include "Camera.h"
#include <GL/gl.h>
#include <GL/glu.h>

Camera::Camera(){
    cameraX = 67.0f;
    cameraY = 627.5f;
    cameraZ = 169.9f;
    // 0.0f, 1.0f, 0.0f),
    //           -128.1f, -42.4f
}

void Camera::move(float x, float y, float z){
    this->cameraX += x;
    this->cameraY += y;
    this->cameraZ += z;
}

void Camera::update(float delta){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ,   // eye
              0.0, 0.0, 0.0,   // center
              0.0, 1.0, 0.0);  // up
}