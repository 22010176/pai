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
    std::function<void(Entity&)> updateFunc = [](Entity&) {};

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

    Entity& SetUpdateFunc(std::function<void(Entity&)> func = [](Entity&) {}) { this->updateFunc = func; return *this; }
    virtual void Update() { updateFunc(*this); }
};

