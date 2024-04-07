#pragma once

#include <SDL2/SDL.h>

#include <Constant.h>
#include <src/Utilities.h>

class Renderer;

class Sprite {
protected:
    static Renderer* renderer;

    SDL_Texture* texture = nullptr;
    SDL_Rect pos{};
    double angle = 0;
    bool active = true;
    int width{}, height{};

public:
    Sprite(SDL_Surface* surface, double angle = 0);
    Sprite(SDL_Texture* texture, double angle = 0);
    Sprite(SDL_Rect rect, SDL_Color color = { 0,0,0,255 });
    Sprite(int width, int height);
    ~Sprite();

    SDL_Texture* GetTexture() const { return this->texture; }
    Sprite& AddTexture(SDL_Texture* value, SDL_Rect position);
    Sprite& AddTexture(SDL_Surface* value, SDL_Rect position);
    Sprite& AddTexture(SDL_Rect value, SDL_Color color);
    Sprite& AddTexture(int outlineWidth, SDL_Color color);

    bool GetActive() const { return this->active; }
    Sprite& SetActive(bool value) { this->active = value; return *this; }

    double GetAngle() const { return this->angle; }
    Sprite& SetAngle(double angle) { this->angle = angle; return *this; }

    SDL_Rect GetPos() const { return this->pos; }
    Sprite& SetPos(const SDL_Rect& rect) { this->pos = rect; return *this; }
    Sprite& SetPos(int x, int y, int w = 0, int h = 0) {
        this->pos = { x,y,w == 0 ? this->width : w,h == 0 ? this->height : h };
        return *this;
    }

    int GetWidth() const { return this->width; }
    int GetHeight() const { return this->height; }
};
