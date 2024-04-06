#include "SpriteTest.h"

void SpriteTest::Main() {
    SDL_Surface* surfaceTest = IMG_Load("./assets/imgs/icon.jpg");

    Sprite surfaceSprite(surfaceTest);
    // SDL_FreeSurface(surfaceTest);

    SDL_Rect surfacePosition{ 0,0,40,50 };
    SDL_Rect rectPosition{ 40,40,30,40 };
    Sprite rectSprite({ 0,0,30,40 }, { 255,255,0,255 });

    rectSprite.AddTexture(surfaceSprite.GetTexture(), { 5,5,25,20 });

    SDL_Event event;
    bool isRunning = true;

    while (isRunning) {
        Renderer::Get().Clear();

        SDL_RenderCopy(Renderer::Get().GetRenderer(), surfaceSprite.GetTexture(), NULL, &surfacePosition);
        SDL_RenderCopy(Renderer::Get().GetRenderer(), rectSprite.GetTexture(), NULL, &rectPosition);

        Renderer::Get().Render();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;

        }
        SDL_Delay(1000 / FPS);
        isRunning = false;
    }
}