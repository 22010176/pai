#pragma once

#include <functional>

#include <src/Manager.h>
#include <src/Entity.h>
#include <src/Renderer.h>
#include <src/Events.h>

class Scene : public Manager<std::string, Entity*> {
private:
    Renderer* renderer;
    std::function<void(EventManager* events)> loopFunc;

public:
    Scene(Renderer* renderer) : renderer(renderer), loopFunc([&](EventManager* events) {}) {}
    ~Scene() { for (auto& [key, en] : pools) en->~Entity(); };

    void SetMainLoop(std::function<void(EventManager* events)>func) { this->loopFunc = func; }
    std::function<void(EventManager* events)> GetMainLoop() const { return loopFunc; }
};

