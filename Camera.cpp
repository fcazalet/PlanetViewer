#include "Camera.h"

Camera::Camera(){

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