#include <iostream>
#include <functional>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <src/Renderer.h>
#include <src/Events.h>
#include <src/Entity.h>
#include <src/Scene.h>
#include <src/Constant.h>
#include <src/Texture.h>

Renderer renderer("", 1280, 720, "assets\\imgs\\icon.png");
EventManager eventManager;
Scene startScene = Scene(&renderer, NormalLoop);

// cd obj; g++ -c C:\Users\ducmi\Downloads\e\src\*.cpp -IC:\Users\ducmi\Downloads\e\include; cd ..
// g++ -shared -o bin/program obj/*.o -IC:\Users\ducmi\Downloads\e\include -LC:\Users\ducmi\Downloads\e\bin\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer      

int main(int argc, char* agrv[]) {
    InitStartScene(&startScene);

    while (GetRunningState()) {

        eventManager.FetchEvent();
        if (eventManager.HasEvent(SDL_QUIT)) SetRunningState(false);

        renderer.Clear();
        startScene.LoopFunc(&eventManager);
        renderer.Render();

        SDL_Delay(1000 / 60);
    }

    return 0;
}