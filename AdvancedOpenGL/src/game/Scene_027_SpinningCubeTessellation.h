//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_027_SpinningCubeTessellation_H
#define Scene_027_SpinningCubeTessellation_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"

#include "CubeObject.h"

class CubeMesh;

class Scene_027_SpinningCubeTessellation : public Scene {
public:
    Scene_027_SpinningCubeTessellation();
    ~Scene_027_SpinningCubeTessellation();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

private:
    Game *game;
    CubeMesh* cubeMesh;
    GLuint vao;
    //GLuint buffer;
    Matrix4 transform;
    Matrix4 projection;
    Shader shader;

    vector<CubeObject> cubes;
    float newXPosition { 0 };
};


#endif //Scene_027_SpinningCubeTessellation_H
