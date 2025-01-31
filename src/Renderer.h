#pragma once

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Constant.h"

class Sprite;

class Renderer {
private:
    static Renderer instance;

    SDL_Renderer* renderer;
    SDL_Window* window;
    Renderer(std::string title = "", int width = WIDTH, int height = HEIGHT, std::string icon = "./assets/imgs/icon.jpg");
public:
    static Renderer& Get() { return Renderer::instance; }

    Renderer(const Renderer& renderer) = delete;
    ~Renderer();

    SDL_Renderer* GetRenderer() const {
        return this->renderer;
    }
    SDL_Window* GetWindow() const { return this->window; }

    void Clear() const {
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->renderer);
    }
    void Draw(SDL_Texture* texture, SDL_Rect position, double angle = 0) {
        SDL_RenderCopyEx(instance.GetRenderer(), texture, nullptr, &position, angle, nullptr, SDL_FLIP_NONE);
    }
    void Render() const { SDL_RenderPresent(this->renderer); };
};

