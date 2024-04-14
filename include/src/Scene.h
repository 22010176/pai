#pragma once

#include <functional>

#include <src/Manager.h>
#include <src/Entity.h>
#include <src/Renderer.h>
#include <src/Events.h>

class Scene : public Manager<std::string, Entity*> {
private:
    Renderer* renderer;
    std::function<void(Scene*, EventManager* events)> loop;

public:
    Scene(Renderer* renderer, std::function<void(Scene*, EventManager*)> func = [](Scene*, EventManager*) {}) : renderer(renderer), loop(func) {}
    ~Scene() { for (auto& [key, en] : pools) en->~Entity(); };

    void LoopFunc(EventManager* events) { loop(this, events); };
    Renderer* GetRenderer() const { return renderer; }
};

void InitStartScene(Scene* scene);


void NormalLoop(Scene* scene, EventManager* events);