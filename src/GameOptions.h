#pragma once

#include <SDL2/SDL.h>   

#include <src/Renderer.h>
#include <Constant.h>

class GameOptions {
private:
    static GameOptions instance;
    bool fullScene = false;
    int width = WIDTH, height = HEIGHT;

    GameOptions() {}
public:
    static GameOptions& Get() { return instance; }

    ~GameOptions() {}

    bool GetFullScene() const { return this->fullScene; }
    GameOptions& SetFullScene(bool value);

    int GetWidth() const { return this->width; }
    void SetWidth(int value) { this->width = value; }

    int GetHeight() const { return this->height; }
    void SetHeight(int value) { this->height = value; }
};



