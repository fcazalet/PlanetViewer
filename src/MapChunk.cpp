#include "MapChunk.h"
#include "ShaderM.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

MapChunk::MapChunk() {}

void MapChunk::setScreen(float width, float height) {
  this->screenWidth = width;
  this->screenHeight = height;
}

void MapChunk::setCamera(Camera *camera) { this->camera = camera; }

void MapChunk::generate() {
  heightMapShader =
      Shader("../assets/vertex_shader.vs", "../assets/fragment_shader.fs");
  // load height map texture
  int width, height, nChannels;

  stbi_set_flip_vertically_on_load(true); // WIthout this, image is reversed
  unsigned char *data = stbi_load("../assets/europe_heightmap.png", &width,
                                  &height, &nChannels, 0);
  // vertex generation
  std::vector<float> vertices;
  float yScale = 32.0f / 256.0f,
        yShift = 16.0f; // apply a scale+shift to the height data
  for (unsigned int i = 0; i < height; i++) {
    for (unsigned int j = 0; j < width; j++) {
      // retrieve texel for (i,j) tex coord
      unsigned char *texel = data + (j + width * i) * nChannels;
      // raw height at coordinate
      unsigned char y = texel[0];

      // vertex
      vertices.push_back(-height / 2.0f + i);       // v.x
      vertices.push_back((int)y * yScale - yShift); // v.y
      vertices.push_back(-width / 2.0f + j);        // v.z
    }
  }
  stbi_image_free(data);

  // index generation
  numStrips = height - 1;
  numVertPerStrip = width * 2;
  std::vector<unsigned int> indices;
  for (unsigned int i = 0; i < height - 1;
       i++) // for each row a.k.a. each strip
  {
    for (unsigned int j = 0; j < width; j++) // for each column
    {
      for (unsigned int k = 0; k < 2; k++) // for each side of the strip
      {
        indices.push_back(j + width * (i + k));
      }
    }
  }
  std::cout << "image reader and index ready" << std::endl;
  // register VAO
  glGenVertexArrays(1, &terrainVAO);
  glBindVertexArray(terrainVAO);

  glGenBuffers(1, &terrainVBO);
  glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(float), // size of vertices buffer
               &vertices[0],                    // pointer to first element
               GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  glGenBuffers(1, &terrainEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               indices.size() * sizeof(unsigned int), // size of indices buffer
               &indices[0], // pointer to first element
               GL_STATIC_DRAW);
  std::cout << "Buffers ready" << std::endl;
}

void MapChunk::render() {
  // be sure to activate shader when setting uniforms/drawing objects
  heightMapShader.use();

  glm::mat4 viewMatrix = camera->GetViewMatrix();
  glm::mat4 projection = camera->getPerspective();
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 mvp = projection * viewMatrix * model;
  heightMapShader.setMat4("uMVP", mvp);

  // draw mesh
  glBindVertexArray(terrainVAO);
  // render the mesh triangle strip by triangle strip - each row at a time
  for (unsigned int strip = 0; strip < numStrips; ++strip) {
    glDrawElements(GL_TRIANGLE_STRIP, // primitive type
                   numVertPerStrip,   // number of indices to render
                   GL_UNSIGNED_INT,   // index data type
                   (void *)(sizeof(unsigned int) * numVertPerStrip *
                            strip)); // offset to starting index
  }
}

void MapChunk::destroy() {
  glDeleteVertexArrays(1, &terrainVAO);
  glDeleteBuffers(1, &terrainVBO);
  glDeleteBuffers(1, &terrainEBO);
}