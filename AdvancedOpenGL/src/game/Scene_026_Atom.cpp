#include "Scene_026_Atom.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_026_Atom::Scene_026_Atom()
{
}

Scene_026_Atom::~Scene_026_Atom() {
    clean();
}

void Scene_026_Atom::setGame(Game *_game) {
    game = _game;
}

void Scene_026_Atom::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
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

    color[0] = Vector4(0.75f, 0.0f, 0.0f, 0.0f);

    for(int i = 1; i < 8; ++i)
    {
        color[i] = Vector4(0.0f, 0.0f, 0.75f, 0.0f);
        transform[i] = Matrix4::createScale(Vector3(0.25f, 0.25f, 0.25f));
    }

    // Generate data and put it in buffer object
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_026_Atom::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_026_Atom::pause() {
}

void Scene_026_Atom::resume() {
}

void Scene_026_Atom::handleEvent(const InputState &inputState) {
}

void Scene_026_Atom::update(float dt) {
    const float t = Timer::getTimeSinceStart() * 0.3f;
    transform[0] = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -10.0f))
        //* Matrix4::createScale(Vector3(1.f, 1.f, 1.f))
        * Matrix4::createScale(Vector3(std::cos(t), std::cos(t), 0.0f))
        * Matrix4::createRotationY(t * Maths::toRadians(45.0f))
        * Matrix4::createRotationX(t * Maths::toRadians(21.0f));
    
    for(int i = 1; i < 8; ++i)
    {
        const float t = i + Timer::getTimeSinceStart() * 0.3f;
        transform[i] = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -10.0f))
            * Matrix4::createScale(Vector3(0.5f, 0.5f, 0.5f))
            * Matrix4::createRotationY(t * Maths::toRadians(45.0f))
            * Matrix4::createRotationX(t * Maths::toRadians(21.0f))
            * Matrix4::createTranslation(Vector3(i * std::cos(3 * t), i * std::sin(3 * t), 0.0f));
    }
}

void Scene_026_Atom::draw()
{
    static const GLfloat bgColor[] = {.75f, .75f, 0.75f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    shader.use();
    shader.setMatrix4("proj_matrix", projection);

    // atom

    for(int i = 0; i < 8; ++i)
    {
        shader.setMatrix4("mv_matrix", transform[i]);
        shader.setVector4f("color_vec", color[i]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
