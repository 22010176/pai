#pragma once

#include <string>
#include <iostream>
#include <functional>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include <src/EventManager.h>
#include <src/Manager.h> 
#include <src/Constant.h>

class Entity;

class Renderer : public Manager<int, Entity*> {
private:
    EventManager events{};
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    bool isRunning = true;

    std::function<void()> mainLoop = []() {};

public:
    Renderer(std::string title = "", int width = WIDTH, int height = HEIGHT, std::string icon = "");
    Renderer(const Renderer& renderer) = delete;
    ~Renderer();

    SDL_Renderer* GetRenderer() const { return this->renderer; }
    SDL_Window* GetWindow() const { return this->window; }

    void Clear() const;
    void Draw(Entity* sprite);
    void Delete(Entity* sprite);
    void Render();
};

