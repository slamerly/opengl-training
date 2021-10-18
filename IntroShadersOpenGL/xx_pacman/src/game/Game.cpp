#include "../engine/Game.h"
#include "../engine/Texture.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

Game::Game() : isRunning(false), windowWidth(0), windowHeight(0) {}

Game::~Game() {}

void Game::init(int screenWidth, int screenHeight) {
    windowWidth = screenWidth;
    windowHeight = screenHeight;
    isRunning = true;
}

void Game::load() {
    std::srand((int) std::time(nullptr));

    // Setup OpenGL
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Setup shader
    shader.compileVertexShader();
    shader.compileFragmentShader();
    shader.createShaderProgram();

    // Setup 3D scene
    projection = Matrix4::createPerspectiveFOV(70.0f, windowWidth, windowHeight, 0.1f, 1000.0f);
    shader.use();
    shader.setMatrix4("proj_matrix", projection);
    level.load("assets/level.txt");
    staticCubes = level.populateStatic();
    for(auto& cube : staticCubes) {
        cube.updateTransform();
    }
}

void Game::handleInputs() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
                break;

            default:
                break;
        }
    }
}

void Game::update(float dt) {

}

void Game::render() {
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    for(auto& cube:staticCubes) {
        cube.draw(shader);
    }
}

void Game::clean() {
    for(auto& cube:staticCubes) {
        cube.clean();
    }
}