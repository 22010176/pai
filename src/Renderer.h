#pragma once

#include <string>
#include <iostream>
#include <functional>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include <src/Sprite.h>
#include <src/EventManager.h>
#include "Constant.h"

class Sprite;

class Renderer {
private:
    EventManager events{};
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    bool isRunning = true;

    std::function<void()> mainLoop = []() {};
    std::function<void(SDL_Event&)> eventFunc = [](SDL_Event&) {};

public:
    Renderer(std::string title = "", int width = WIDTH, int height = HEIGHT, std::string icon = "");
    Renderer(const Renderer& renderer) = delete;
    ~Renderer();

    SDL_Renderer* GetRenderer() const { return this->renderer; }
    SDL_Window* GetWindow() const { return this->window; }

    void Clear() const;
    void Draw(Sprite* sprite);
    void Render() const { SDL_RenderPresent(this->renderer); };

    SDL_Point GetMousePos() const { int x, y; SDL_GetMouseState(&x, &y); return { x,y }; }

    void MainLoop();
    void SetMainLoop(std::function<void()> mainLoop = []() {}) { this->mainLoop = mainLoop; }
    void SetEventFunc(std::function<void(SDL_Event&)> eventFunc = [](SDL_Event&) {}) { this->eventFunc = eventFunc; }

    SDL_Event GetEvent(SDL_EventType type) const { return this->events.GetEvent(type); }
    bool CheckEvent(SDL_EventType type) const { return this->events.CheckEvent(type); }

    void TerminateProgram() { this->isRunning = false; }
    void SetFullScrene();
};

