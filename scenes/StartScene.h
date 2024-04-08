#pragma once

#include <src/Scene.h>
#include <src/GameOptions.h>
#include <src/Utilities.h>

void SS_LoopFunc();
void SS_EventFunc(SDL_Event& event);

class StartScene : public Scene {
private:
    static StartScene instance;

public:
    static StartScene& Get() { return instance; }

    StartScene(Renderer& renderer);
    ~StartScene();

    virtual std::function<void()> GetLoopFunc() const { return SS_LoopFunc; }
    virtual std::function<void(SDL_Event&)> GetEventFunc() const { return SS_EventFunc; }
};