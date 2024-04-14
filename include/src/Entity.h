#pragma once

#include <map>
#include <string>
#include <functional>

#include <SDL2/SDL.h>

#include <src/Manager.h>
#include <src/Scripts.h>

class Renderer;

class Entity : public Manager<std::string, SDL_Texture*> {
private:
    SDL_Texture* texture = nullptr;
    Renderer* renderer = nullptr;
    int width{}, height{};

    double angle{};
    SDL_Rect pos{};

    std::vector<Script<void, Entity*>*> scripts;

    SDL_Texture* CreateTexture(int width, int height) const;

public:
    Entity(Renderer* renderer, SDL_Surface* surface);
    Entity(Renderer* renderer, SDL_Texture* texture);
    Entity(Renderer* renderer, int width, int height);
    Entity(const Entity& sprite);
    ~Entity();

    Entity* SetSprite(std::string name);
    Entity* AddSprite(std::string name, SDL_Texture* texture);
    Entity* AddSprite(std::string name, SDL_Surface* surface);
    Entity* AddSprite(std::string name, int width, int height);

    SDL_Texture* ExportCurrentTexture() const;
    SDL_Texture* GetCurrentTexture() const { return this->texture; }

    Entity* AddTexture(SDL_Texture* texture, SDL_Rect position);
    Entity* AddTexture(SDL_Texture* texture, SDL_Rect* position);

    Entity* AddTexture(SDL_Surface* surface, SDL_Rect position);
    Entity* AddTexture(SDL_Surface* surface, SDL_Rect* position);

    Entity* AddTexture(SDL_Rect rect, SDL_Color color);
    Entity* AddTexture(SDL_Rect rect, SDL_Color* color);
    Entity* AddTexture(SDL_Rect* rect, SDL_Color color);
    Entity* AddTexture(SDL_Rect* rect, SDL_Color* color);

    Entity* AddTexture(int outlineSize, SDL_Color color);
    Entity* AddTexture(int outlineSize, SDL_Color* color);

    double GetAngle() const { return angle; }
    Entity* SetAngle(double angle) { this->angle = angle; return this; }

    SDL_Rect GetDisplayPos() const { return pos; }
    Entity* SetDisplayPos(SDL_Rect val) { this->pos = val; return this; }
    Entity* SetDisplayPos(SDL_Rect* val) { this->pos = *val; return this; }
    Entity* SetDisplayPos(int x, int y) { this->pos.x = x, this->pos.y = y; return this; }

    int GetCurrentTextureWidth() const { return this->width; }
    int GetCurrentTextureHeight() const { return this->height; }

    Script<void, Entity*>* AddScripts(std::function<void(Entity*)> callback);
    Script<void, Entity*>* SetScriptState(Script<void, Entity*>* script, bool state);
    void RunScripts() { for (auto& f : scripts) if (f->enable) f->callback(this); }
};

