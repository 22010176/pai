#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <src/Renderer.h>
#include <src/Sprite.h>

#include "../Test.h"

class SpriteTest : public Test {
public:
    SpriteTest() : Test() {}
    virtual void Main();
};