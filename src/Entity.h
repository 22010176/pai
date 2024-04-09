#pragma once

#include <map>
#include <string>
#include <functional>

#include <SDL2/SDL.h>

#include <src/Renderer.h>
#include <src/Sprite.h>

class Entity : public Sprite {
private:
    std::map <std::string, SDL_Texture*> textures{};
    std::map<std::string, std::function<void(Entity&)>> updateFunc{};

public:
    Entity(Renderer& renderer, SDL_Surface* surface, double angle = 0);
    Entity(Renderer& renderer, SDL_Texture* texture, double angle = 0);
    Entity(Renderer& renderer, SDL_Rect rect, SDL_Color color = { 0,0,0,255 });
    Entity(Renderer& renderer, int width, int height);
    ~Entity();

    void SetSprite(std::string name = "_");
    Entity& AddSprite(std::string name);
    Entity& AddSprite(std::string name, SDL_Texture* texture);
    Entity& AddSprite(std::string name, SDL_Surface* surface);
    Entity& AddSprite(std::string name, int width, int height);

    Entity& AddUpdateFunc(std::string name, std::function<void(Entity&)> func) {
        this->updateFunc[name] = func;
        return *this;
    }
    Entity& RemoveUpdateFunc(std::string name) {
        this->updateFunc.erase(name);
        return *this;
    }
    std::function<void(Entity&)> GetFunc(std::string name) const { return this->updateFunc.at(name); }
    virtual void Update() { for (const auto& [key, value] : this->updateFunc) value(*this); }
};

Entity& CreateBtn(Renderer& renderer, SDL_Surface* surface, int w, int h, SDL_Color color, SDL_Color hoverColor);
// std::function<void(Entity&)> ClickEvent(Renderer& renderer, std::function<void(Entity&)> func);