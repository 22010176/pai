#pragma once

#include <map>
#include <string>

#include <SDL2/SDL.h>

#include <src/Renderer.h>
#include <src/Sprite.h>

class Entity : public Sprite {
private:
    std::map <std::string, SDL_Texture*> textures{};

public:
    Entity(SDL_Surface* surface, double angle = 0);
    Entity(SDL_Texture* texture, double angle = 0);
    Entity(SDL_Rect rect, SDL_Color color = { 0,0,0,255 });
    Entity(int width, int height);
    ~Entity();

    void SetSprite(std::string name = "_");
    Entity& AddSprite(std::string name);
    Entity& AddSprite(std::string name, SDL_Texture* texture);
    Entity& AddSprite(std::string name, SDL_Surface* surface);
    Entity& AddSprite(std::string name, int width, int height);
};