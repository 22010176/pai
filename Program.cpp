#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <src/Renderer.h>
#include <src/Entity.h>
#include <src/Utilities.h>
#include <src/GameOptions.h>
// #include <src/SceneManager.h>

#include <scenes/StartScene.h>
#include <scenes/OptionScene.h>
#include <Constant.h>

Renderer mainWindow("", WIDTH, HEIGHT, "assets/imgs/icon.jpg");
// SceneManager scenes;

StartScene StartScene::instance(mainWindow);
OptionScene OptionScene::instance(mainWindow);

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    // scenes.AddScene("startScene", StartScene::Get());
    // scenes.AddScene("optionScene", OptionScene::Get());


    mainWindow.SetMainLoop(StartScene::Get().GetLoopFunc());
    mainWindow.MainLoop();

    return 0;
}
