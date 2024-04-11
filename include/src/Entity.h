#pragma once

#include <map>
#include <string>
#include <functional>

#include <SDL2/SDL.h>

#include <src/Renderer.h>
#include <src/Manager.h>
#include <src/Sprite.h>

class Entity : public Sprite, public Manager<std::string, SDL_Texture*> {
private:
    double angle = 0;
    SDL_Rect pos{};

    void Init();
public:
    Entity(Renderer& renderer, SDL_Surface* surface, double angle = 0);
    Entity(Renderer& renderer, SDL_Texture* texture, double angle = 0);
    Entity(Renderer& renderer, int width, int height, SDL_Color color = { 0,0,0,255 });
    ~Entity();

    Entity& SetSprite(std::string name = "_");
    Entity& AddSprite(std::string name);
    Entity& AddSprite(std::string name, SDL_Texture* texture);
    Entity& AddSprite(std::string name, SDL_Surface* surface);
    Entity& AddSprite(std::string name, int width, int height);

    double GetAngle() const { return angle; }
    Entity& SetAngle(double angle) { this->angle = angle; return *this; }

    SDL_Rect GetPos() const { return pos; }
    Entity& SetPos(SDL_Rect val) { this->pos = val; return *this; }
    Entity& SetPos(int x, int y) { this->pos.x = x, this->pos.y = y; return *this; }
};

// Entity& CreateBtn(Renderer& renderer, SDL_Surface* surface, int w, int h, SDL_Color color, SDL_Color hoverColor);
// std::function<void(Entity&)> ClickEvent(Renderer& renderer, std::function<void(Entity&)> func);