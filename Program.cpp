#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <src/Renderer.h>
#include <src/Sprite.h>
#include <Scenes/StartScene.h>

#include "Constant.h"


/* TODO
Update UML diagram
Continue finishing StartScene
- Finish Constructor
- Debug
- Create Test function
*/

int main(int argc, char* argv[]) {
    SDL_Event e;
    bool isRunning = true;

    while (isRunning) {
        StartScene::Get().MainLoop();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
            StartScene::Get().Notify(e);
        }

    }


    return 0;
}