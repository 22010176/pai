#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <src/Renderer.h>
#include <src/Events.h>
#include <src/Entity.h>
#include <src/Scene.h>
#include <src/Constant.h>

Renderer renderer("", 1280, 720);
EventManager eventManager;
Scene mainScene(&renderer);

int main(int argc, char* agrv[]) {
    while (GetRunningState()) {
        eventManager.FetchEvent();
        if (eventManager.HasEvent(SDL_QUIT)) SetRunningState(false);

        mainScene.GetMainLoop()(&eventManager);
        SDL_Delay(1000 / 120);
    }

    return 0;
}