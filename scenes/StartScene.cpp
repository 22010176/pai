#include "StartScene.h"

StartScene::StartScene(Renderer& renderer) : Scene(renderer) {
    SDL_Rect btnSize = { 0,0,350,70 };
    int offset = 50;
    TTF_Font* font = TTF_OpenFont(".\\assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 50);
    TTF_Font* bigFont = TTF_OpenFont(".\\assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 100);

    SDL_Surface* playT = TTF_RenderText_Blended(font, "PLAY", white);
    SDL_Surface* optT = TTF_RenderText_Blended(font, "OPTIONS", white);
    SDL_Surface* quitT = TTF_RenderText_Blended(font, "QUIT", white);
    SDL_Surface* logoT = TTF_RenderText_Blended(bigFont, "CHESS", white);
    SDL_Surface* img = IMG_Load(".\\assets\\imgs\\icon.jpg");

    Entity& playBtn = *new Entity(renderer, btnSize, green);
    playBtn
        .AddTexture(playT, GetMiddle(btnSize, { 0,0,playT->w,playT->h }))
        .SetPos(CalcPadding(GameOptions::Get().GetWidth(), btnSize.w), GameOptions::Get().GetHeight() / 2 + offset);
    offset += btnSize.h + 20;

    Entity& optBtn = *new Entity(renderer, btnSize, grey);
    optBtn
        .AddTexture(optT, GetMiddle(btnSize, { 0,0,optT->w,optT->h }))
        .SetPos(CalcPadding(GameOptions::Get().GetWidth(), btnSize.w), GameOptions::Get().GetHeight() / 2 + offset);
    offset += btnSize.h + 20;

    Entity& quitBtn = *new Entity(renderer, btnSize, red);
    quitBtn
        .AddTexture(quitT, GetMiddle(btnSize, { 0,0,quitT->w,quitT->h }))
        .SetPos(CalcPadding(GameOptions::Get().GetWidth(), btnSize.w), GameOptions::Get().GetHeight() / 2 + offset);

    Entity& imgS = *new Entity(renderer, img);
    imgS
        .AddTexture(35, darkBlue)
        .SetPos({ GameOptions::Get().GetWidth() - img->w / 7 - 10,GameOptions::Get().GetHeight() - img->h / 7 - 10,img->w / 7,img->h / 7 });

    Entity& logo = *new Entity(renderer, logoT, -5);
    logo.SetPos({ CalcPadding(GameOptions::Get().GetWidth(),600),50,600,200 });

    this->AddSprite("playBtn", playBtn);
    this->AddSprite("quitBtn", quitBtn);
    this->AddSprite("optBtn", optBtn);
    this->AddSprite("imgS", imgS);
    this->AddSprite("logo", logo);


    this->GetEntity("logo").SetUpdateFunc([](Entity& entity) {
        static double i = 0;
        static SDL_Rect curPos = entity.GetPos();
        entity.SetPos(entity.GetPos().x, curPos.y + 30 * sin(i * PI), curPos.w, curPos.h);
        i += 0.01;

        if (i >= 2.0) i = 0;
        });

    TTF_CloseFont(font);
    TTF_CloseFont(bigFont);

    SDL_FreeSurface(playT);
    SDL_FreeSurface(optT);
    SDL_FreeSurface(quitT);
    SDL_FreeSurface(logoT);
    SDL_FreeSurface(img);
}
StartScene::~StartScene() { for (const auto& a : this->sprites) a.second.~Entity(); }

void SS_LoopFunc() {
    StartScene::Get().GetRenderer().Draw(&StartScene::Get().GetEntity("playBtn"));
    StartScene::Get().GetRenderer().Draw(&StartScene::Get().GetEntity("quitBtn"));
    StartScene::Get().GetRenderer().Draw(&StartScene::Get().GetEntity("optBtn"));
    StartScene::Get().GetRenderer().Draw(&StartScene::Get().GetEntity("imgS"));
    StartScene::Get().GetRenderer().Draw(&StartScene::Get().GetEntity("logo"));
}
void SS_EventFunc(SDL_Event& event) {
}