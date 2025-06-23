#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <string>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#define GLEW_STATIC
#include <GL/gl.h>
#include <GL/glu.h>
#include "Camera.h"
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

    float ORG[3] = {0,0,0};
    float XP[3] = {1,0,0}, XN[3] = {-1,0,0},
YP[3] = {0,1,0}, YN[3] = {0,-1,0},
ZP[3] = {0,0,1}, ZN[3] = {0,0,-1};

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

#define WinWidth 800
#define WinHeight 600

Camera camera = Camera();
float cameraSpeed = 0.01;
// float cameraX = 0.0;
// float cameraY = 0.0;
// float cameraZ = 2.0;

// Initialize OpenGL state
void init() {
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glClearColor(0.1, 0.1, 0.1, 1.0); // Background color

    // Init perspective
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective(80,(double)WinWidth/WinHeight,1,1000);
    glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set projection
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluPerspective(90,(double)WinWidth/WinHeight,1,1000);

    // Set modelview and camera
    camera.update(0);
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    // gluLookAt(cameraX, cameraY, cameraZ,   // eye
    //           0.0, 0.0, 0.0,   // center
    //           0.0, 1.0, 0.0);  // up

              glLineWidth (2.0);


    glBegin (GL_LINES);
      glColor3f (1,0,0);   // X axis is red.
      glVertex3fv (ORG);
      glVertex3fv (XP); 
      glColor3f (0,1,0);   // Y axis is green.
      glVertex3fv (ORG);
      glVertex3fv (YP);
      glColor3f (0,0,1);   // z axis is blue.
      glVertex3fv (ORG);
      glVertex3fv (ZP); 
    glEnd();

    // Draw a simple triangle
    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0); glVertex3f( 0.0,  1.0, 0.0);
        glColor3f(0.0, 1.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
        glColor3f(0.0, 0.0, 1.0); glVertex3f( 1.0, -1.0, 0.0);
    glEnd();

    // glutSwapBuffers();
}

int main (int ArgCount, char **Args)
{
  u32 WindowFlags = SDL_WINDOW_OPENGL;
  SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 100, 100, WinWidth, WinHeight, WindowFlags);
  SDL_GLContext Context = SDL_GL_CreateContext(Window);
  
  b32 Running = 1;
  b32 FullScreen = 0;
  float z = 0.0;

  init();

  while (Running)
  {
    SDL_Event Event;
    while (SDL_PollEvent(&Event))
    {
      if (Event.type == SDL_KEYDOWN)
      {
        switch (Event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            Running = 0;
            break;
          case 'f':
            FullScreen = !FullScreen;
            if (FullScreen)
            {
              SDL_SetWindowFullscreen(Window, WindowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
            }
            else
            {
              SDL_SetWindowFullscreen(Window, WindowFlags);
            }
            break;
          case 'z':
            camera.move(0,0,-cameraSpeed);
            break;
          case 's':
            camera.move(0,0,cameraSpeed);
            break;
          case 'q':
            camera.move(-cameraSpeed,0,0);
            break;
          case 'd':
            camera.move(cameraSpeed,0,0);
            break;
          default:
            break;
        }
      }
      else if (Event.type == SDL_QUIT)
      {
        Running = 0;
      }

    }

    display();

    SDL_GL_SwapWindow(Window);
  }
  return 0;
}