#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <src/Renderer.h>
#include <src/Entity.h>
#include <src/Utilities.h>
#include <src/Constant.h>
#include <src/EventManager.h>
#include <src/SceneManager.h>

#include <scenes/StartScene.h>

Renderer mainWindow("", WIDTH, HEIGHT, "assets/imgs/icon.jpg");
StartScene StartScene::instance(&mainWindow);

SceneManager scenes;

EventManager events;
bool isRunning = true;

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    scenes.AddItem("startScene", StartScene::Get());
    scenes.SetScene("startScene");

    while (isRunning) {
        events.FetchEvent();
        if (events.HasItem(SDL_QUIT)) isRunning = false;

        scenes.LoopFunc();

        mainWindow.Render();
        SDL_Delay(1000 / FPS);
    }


    return 0;
}
