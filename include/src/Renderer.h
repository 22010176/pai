#pragma once

#include <string>
#include <iostream>
#include <functional>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <src/Manager.h> 
#include <src/Constant.h>

class Entity;

class Renderer {
private:
    SDL_Renderer* renderer{};
    SDL_Window* window{};

public:
    Renderer(std::string title, int width, int height, std::string icon = "");
    Renderer(const Renderer& renderer) = delete;
    ~Renderer();

    SDL_Renderer* GetRenderer() const { return this->renderer; }
    SDL_Window* GetWindow() const { return this->window; }

    void Clear() const;
    void Draw(Entity* sprite) const;
    void Render() const;
};
