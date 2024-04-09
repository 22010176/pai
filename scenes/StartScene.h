#pragma once

#include <src/Scene.h>
#include <src/GameOptions.h>
#include <src/Entity.h>
#include <src/Utilities.h>

void SS_LoopFunc();

class OptionScene;

class StartScene : public Scene {
private:
    static StartScene instance;
    StartScene(Renderer& renderer);

public:
    static StartScene& Get() { return instance; }

    StartScene(const StartScene&) = delete;
    ~StartScene();

    virtual std::function<void()> GetLoopFunc() const { return SS_LoopFunc; }
};