#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <src/Renderer.h>
#include <src/Entity.h>
#include <src/Utilities.h>
#include <src/GameOptions.h>

#include <scenes/StartScene.h>
#include <Constant.h>

Renderer mainWindow("", WIDTH, HEIGHT, "./assets/imgs/icon.jpg");
StartScene StartScene::instance(mainWindow);

int main(int argc, char* argv[]) {

    mainWindow.SetMainLoop(StartScene::Get().GetLoopFunc());
    mainWindow.SetEventFunc(StartScene::Get().GetEventFunc());
    mainWindow.MainLoop();

    return 0;
}
