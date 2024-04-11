#pragma once

#include <functional>

#include <SDL2/SDL.h>

#include <src/Constant.h>
#include <src/Utilities.h>

class Renderer;

// Display
class Sprite {
protected:
    SDL_Texture* texture;
    Renderer& renderer;
    int width, height;

public:
    Sprite(Renderer& renderer, SDL_Surface* surface, double angle = 0);
    Sprite(Renderer& renderer, SDL_Texture* texture, double angle = 0);
    Sprite(Renderer& renderer, int width, int height, SDL_Color color = { 0,0,0,255 });
    Sprite(const Sprite& sprite);
    ~Sprite();

    SDL_Texture* GetTexture() const { return this->texture; }
    SDL_Texture* ExportTexture() const;
    Sprite& AddTexture(SDL_Texture* value, SDL_Rect position);
    Sprite& AddTexture(SDL_Surface* value, SDL_Rect position);
    Sprite& AddTexture(SDL_Rect value, SDL_Color color);
    Sprite& AddTexture(int outlineWidth, SDL_Color color);

    int GetWidth() const { return this->width; }
    int GetHeight() const { return this->height; }
};
