#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <vector>
#include <string>
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#define GLEW_STATIC
#include <GL/gl.h>
#include <GL/glu.h>
#include "MapChunk.h"
#include "Camera.h"
#include "Camera2.h"
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;


float ORG[3] = {0,0,0};
float XP[3] = {1,0,0}, XN[3] = {-1,0,0},
  YP[3] = {0,1,0}, YN[3] = {0,-1,0},
  ZP[3] = {0,0,1}, ZN[3] = {0,0,-1};

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

#define WinWidth 800
#define WinHeight 600

Camera* camera;
Camera2 camera2(glm::vec3(67.0f, 627.5f, 169.9f),
              glm::vec3(0.0f, 1.0f, 0.0f),
              -128.1f, -42.4f);
float cameraSpeed = 10;
bool Mousefirst  = true;
bool MouseMotion = false;
MapChunk mapChunk;

// timing
float deltaTime = 0.0f;
Uint32 lastFrame = SDL_GetTicks();

// Initialize OpenGL state
void init() {

    // glewExperimental = GL_TRUE; 
    glewInit();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glClearColor(0.1, 0.1, 0.1, 1.0); // Background color

    // Init perspective
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
    camera->fovy = 80;
    camera->aspect = (double)WinWidth/WinHeight;
    camera->zNear = 1;
    camera->zFar = 1000;
		gluPerspective(camera->fovy,camera->aspect,camera->zNear,camera->zFar);
    glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->update(0);
    mapChunk.render();
    
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
}

int main (int ArgCount, char **Args)
{
  u32 WindowFlags = SDL_WINDOW_OPENGL;
  SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 100, 100, WinWidth, WinHeight, WindowFlags);
  SDL_GLContext Context = SDL_GL_CreateContext(Window);
  SDL_SetRelativeMouseMode(SDL_TRUE);
  
  b32 Running = 1;
  b32 FullScreen = 0;
  float z = 0.0;

  camera = new Camera();

  init();

  mapChunk.setCamera(camera);
  mapChunk.setScreen(WinWidth, WinHeight);
  mapChunk.generate();

  while (Running)
  {
    time_t seconds = time (NULL);
    Uint32 currentFrame = SDL_GetTicks();
    deltaTime = (currentFrame - lastFrame) / 1000.0f;
    lastFrame = currentFrame;
    // printf("FPS: %f", 1.0/deltaTime);

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
            // camera.move(0,0,-cameraSpeed);
            camera->move(FORWARD, deltaTime);
            camera2.ProcessKeyboard(FORWARD2, deltaTime);
            break;
          case 's':
            camera->move(BACKWARD, deltaTime);
            break;
          case 'q':
            camera->move(LEFT, deltaTime);
            break;
          case 'd':
            camera->move(RIGHT, deltaTime);
            break;
          case 'e':
            camera->move(UP, deltaTime);
            break;
          case 'a':
            camera->move(DOWN, deltaTime);
            break;
          default:
            break;
        }
      }
      else if (Event.type == SDL_MOUSEMOTION) {
        MouseMotion = true;
        int MouseRelX, MouseRelY;
        if (!Mousefirst) {
          MouseRelX = Event.motion.xrel;
          MouseRelY = Event.motion.yrel;
        } else {
          Mousefirst = false;
          MouseRelX = 0;
          MouseRelY = 0;
        }

        if (MouseMotion) {
          MouseMotion = false;
          camera->moveMouse(MouseRelX, MouseRelY);
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

  mapChunk.destroy();
  return 0;
}