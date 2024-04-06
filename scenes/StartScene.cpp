#include "StartScene.h"

StartScene StartScene::instance;

void playBtnFunc(GameObject& obj, SDL_Event& event) {
    std::cout << event.type << std::endl;
}

StartScene::StartScene() : Scene() {
    SDL_Rect size = { 0,0,200,75 };
    TTF_Font* font = TTF_OpenFont("", 50);

    SDL_Surface* surface = TTF_RenderText_Solid(font, "PLAY", white);
    SDL_Rect playPos = { CalcPadding(size.w,surface->w), CalcPadding(size.h,surface->h),surface->w,surface->h };

    GameObject playBtn({ CalcPadding(WIDTH,size.w),HEIGHT / 2,size.w,size.h }, playBtnFunc);
    playBtn.AddSprite("default", Sprite(size, green)).AddTexture(surface, playPos);
    // playBtn.AddSprite("hover", Sprite(size, darkGreen)).AddTexture(surface, playPos);


    Attach(playBtn);

    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
}

StartScene::~StartScene() {
    std::cout << "GOOD______" << std::endl;
}


void StartScene::MainLoop() {
    renderer.Clear();

    for (Observer<SDL_Event>& sp : observers) {
        GameObject& temp = static_cast<GameObject&>(sp);
        renderer.Draw(temp.GetTexture(), temp.GetPosition());

    }

    renderer.Render();
}