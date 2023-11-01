#ifndef Scene_001_Atom_H
#define Scene_001_Atom_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_001_Atom : public Scene {
public:
    Scene_001_Atom();
    ~Scene_001_Atom();
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
    GLuint vao;
    GLuint buffer;
    Matrix4 transform[24];
    Matrix4 projection;
    Vector4 color[24];

    Shader shader;
};


#endif //Scene_001_Atom_H
