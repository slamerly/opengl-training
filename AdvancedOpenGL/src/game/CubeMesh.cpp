#include "CubeMesh.h"
#include "../engine/Log.h"

void CubeMesh::load() {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  static const GLfloat vertexPositions[] =
  {
          -0.25f,  0.25f, -0.25f,
          -0.25f, -0.25f, -0.25f,
            0.25f, -0.25f, -0.25f,

            0.25f, -0.25f, -0.25f,
            0.25f,  0.25f, -0.25f,
          -0.25f,  0.25f, -0.25f,

            0.25f, -0.25f, -0.25f,
            0.25f, -0.25f,  0.25f,
            0.25f,  0.25f, -0.25f,

            0.25f, -0.25f,  0.25f,
            0.25f,  0.25f,  0.25f,
            0.25f,  0.25f, -0.25f,

            0.25f, -0.25f,  0.25f,
          -0.25f, -0.25f,  0.25f,
            0.25f,  0.25f,  0.25f,

          -0.25f, -0.25f,  0.25f,
          -0.25f,  0.25f,  0.25f,
            0.25f,  0.25f,  0.25f,

          -0.25f, -0.25f,  0.25f,
          -0.25f, -0.25f, -0.25f,
          -0.25f,  0.25f,  0.25f,

          -0.25f, -0.25f, -0.25f,
          -0.25f,  0.25f, -0.25f,
          -0.25f,  0.25f,  0.25f,

          -0.25f, -0.25f,  0.25f,
            0.25f, -0.25f,  0.25f,
            0.25f, -0.25f, -0.25f,

            0.25f, -0.25f, -0.25f,
          -0.25f, -0.25f, -0.25f,
          -0.25f, -0.25f,  0.25f,

          -0.25f,  0.25f, -0.25f,
            0.25f,  0.25f, -0.25f,
            0.25f,  0.25f,  0.25f,

            0.25f,  0.25f,  0.25f,
          -0.25f,  0.25f,  0.25f,
          -0.25f,  0.25f, -0.25f
  };

  // Generate data and put it in buffer object
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

  LOG(Info) << "vertexPositions size " << sizeof(vertexPositions);

  // Setup vertex attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);
}

void CubeMesh::draw() {
  glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CubeMesh::drawTesselation() 
{
  glDrawArrays(GL_PATCHES, 0, 36);
}

void CubeMesh::clean() {
  glDeleteVertexArrays(1, &vao);
}