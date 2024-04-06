#pragma once

#include <src/GameObject.h>
#include <src/Utilities.h>

#include "Scene.h"


class StartScene : public Scene {
private:
    inline static int id = ++Scene::idSeed;
    static StartScene instance;
    StartScene();
public:
    static int GetId() { return id; }
    static StartScene& Get() { return instance; }

    StartScene(const StartScene&) = delete;
    ~StartScene();

    virtual void MainLoop();
};

