#pragma once

#include <src/Scene.h>
#include <src/Entity.h>
#include <src/Utilities.h>

class OptionScene;

class StartScene : public Scene {
private:
    static StartScene instance;
    StartScene(Renderer* renderer);

public:
    static StartScene* Get() { return &instance; }

    StartScene(const StartScene&) = delete;
    ~StartScene();

    void Loop() override;
    void Event() override;
};