#pragma once

#include <functional>
#include <string>
#include <map>

#include <src/Renderer.h>
#include <src/Sprite.h>
#include <src/Utilities.h>
#include <src/Manager.h>
#include <src/Entity.h>

class Scene : public Manager<std::string, Entity&> {
protected:
    Renderer& renderer;

public:
    Scene(Renderer& renderer) : renderer(renderer) {}
    ~Scene() { for (const auto& [key, value] : this->pools) value.~Entity(); }

    virtual std::function<void()> GetLoopFunc() const = 0;
    virtual std::function<void(SDL_Event)> GetEventFunc() const = 0;

    Renderer& GetRenderer() const { return this->renderer; }
};