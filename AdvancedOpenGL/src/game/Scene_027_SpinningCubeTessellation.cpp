//
// Created by gaetz on 04/12/2019.
//

#include "Scene_027_SpinningCubeTessellation.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

#include "CubeMesh.h"


Scene_027_SpinningCubeTessellation::Scene_027_SpinningCubeTessellation()
{
}

Scene_027_SpinningCubeTessellation::~Scene_027_SpinningCubeTessellation() {
    clean();
}

void Scene_027_SpinningCubeTessellation::setGame(Game *_game) {
    game = _game;
}

void Scene_027_SpinningCubeTessellation::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), SHADER_TECS(SHADER_NAME), SHADER_TESE(SHADER_NAME), "", SHADER_ID(SHADER_NAME));
    //Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), SHADER_TECS(SHADER_NAME), SHADER_TESE(SHADER_NAME), SHADER_GEOM(SHADER_NAME), SHADER_ID(SHADER_NAME));
    //Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glPatchParameteri(GL_PATCH_VERTICES, 4);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);

    cubeMesh = new CubeMesh();
    cubeMesh->load();

/*
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

    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    */

    /*
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    */

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));

    //shader.setFloat("tessLevelInner", 3);
    //shader.setFloat("tessLevelOuter", 3);

    cubes.emplace_back(0.0f, 0.0f, cubeMesh);
}

void Scene_027_SpinningCubeTessellation::clean() {
    cubeMesh->clean();
    delete cubeMesh;
    //glDeleteVertexArrays(1, &vao);
}

void Scene_027_SpinningCubeTessellation::pause() {
}

void Scene_027_SpinningCubeTessellation::resume() {
}

void Scene_027_SpinningCubeTessellation::handleEvent(const InputState &inputState) {
}

void Scene_027_SpinningCubeTessellation::update(float dt) {
    
    for (auto& cube : cubes) {
        cube.update();
    }
   /*
   const float t = Timer::getTimeSinceStart() * 0.3f;
    transform = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -7.5f))
        * Matrix4::createRotationY(t * Maths::toRadians(45.0f))
        * Matrix4::createRotationX(t * Maths::toRadians(21.0f))
        * Matrix4::createTranslation(Vector3(Maths::sin(2.1f * t) * 2.0f, Maths::cos(1.7f * t) * 2.0f, Maths::sin(1.3f * t) * Maths::cos(1.5f * t) * 2.0f));
    */
}

void Scene_027_SpinningCubeTessellation::draw() {

    //static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    static const GLfloat bgColor[] = {0.f, 0.f, 0.f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);
    shader.use();
    shader.setMatrix4("proj_matrix", projection);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (auto& cube : cubes) {
        //shader.setMatrix4("mv_matrix", transform);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        cube.drawTesselation(shader);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
