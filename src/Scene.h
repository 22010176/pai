#pragma once

#include <functional>
#include <string>
#include <map>

#include <src/Renderer.h>
#include <src/Sprite.h>
#include <src/Utilities.h>
#include <src/Entity.h>

class Scene {
protected:
    Renderer& renderer;
    std::map<std::string, Entity&> sprites{};

public:
    Scene(Renderer& renderer) : renderer(renderer) {}
    ~Scene() { for (const auto& a : this->sprites) a.second.~Entity(); }

    virtual std::function<void()> GetLoopFunc() const = 0;

    Renderer& GetRenderer() const { return this->renderer; }
    std::map<std::string, Entity&> GetSprites() const { return sprites; }

    Scene& AddSprite(std::string name, Entity& entity) {
        sprites.insert({ name,entity });
        return *this;
    }
    void RemmoveSprite(std::string name) { if (this->sprites.find(name) != this->sprites.end()) this->sprites.erase(name); }
    Entity& GetEntity(std::string name) { return this->sprites.at(name); }
};

// Entity& CreateBtn(Renderer& renderer, SDL_Surface* surface, int w, int h, SDL_Color color, SDL_Color hoverColor);