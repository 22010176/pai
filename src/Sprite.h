#pragma once

#include <SDL2/SDL.h>

#include "Renderer.h"

class Sprite {
protected:
    static Renderer& renderer;
    SDL_Texture* texture = nullptr;
    double angle = 0;
    bool active = true;
    int width = 0, height = 0;
public:
    Sprite() {}
    Sprite(SDL_Surface* surface, double angle = 0, bool active = true);
    Sprite(SDL_Texture* texture, double angle = 0, bool active = true);
    Sprite(SDL_Rect rect, SDL_Color color = { 0,0,0,0 });
    ~Sprite();

    SDL_Texture* GetTexture() const { return this->texture; }
    Sprite& SetTexture(SDL_Texture* texture) {
        this->texture = texture;
        SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
        return *this;
    }
    Sprite& AddTexture(SDL_Texture* value, SDL_Rect position);
    Sprite& AddTexture(SDL_Surface* value, SDL_Rect position);
    Sprite& AddTexture(SDL_Rect value, SDL_Color color, SDL_Rect position);

    bool GetActive() const { return this->active; }
    Sprite& SetActive(bool value) { this->active = value; return *this; }

    double GetAngle() const { return this->angle; }
    Sprite& SetAngle(double angle) { this->angle = angle; return *this; }

    int GetWidth() const { return this->width; }
    int GetHeight() const { return this->height; }
};


// class Text : public Sprite {
// public:
//     static SDL_Surface* RenderText(TTF_Font* font, std::string content, SDL_Color color = white) { return TTF_RenderText_Solid(font, content.c_str(), color); };
// };