#pragma once

#include <functional>
#include <string>
#include <map>

#include <src/Renderer.h>
#include <src/Sprite.h>
#include <src/Utilities.h>
#include <src/Manager.h>
#include <src/Entity.h>

class Scene : public Manager<std::string, Entity*> {
protected:
    Renderer* renderer;

public:
    std::vector<std::function<void()>> callbacks;

    Scene(Renderer* renderer) : renderer(renderer) {}
    ~Scene() { for (const auto& [key, value] : this->pools) delete value; }

    virtual void Loop() = 0;
    virtual void Event() = 0;

    Renderer* GetRenderer() const { return this->renderer; }
};