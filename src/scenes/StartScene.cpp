#include <scenes/StartScene.h>
// #include "OptionScene.h"

Entity* CreateBtn(Renderer* renderer, SDL_Surface* surface, int w, int h, SDL_Color def, SDL_Color hover) {
    SDL_Rect pos = GetMiddle({ 0,0,w,h }, { 0,0,surface->w,surface->h });
    Entity* temp = new Entity(renderer, w, h, def);
    temp->AddTexture(surface, pos);

    temp->AddSprite("hover")
        ->AddTexture({ 0,0,w,h }, hover)
        ->AddTexture(surface, pos);

    temp->SetSprite("default");
    return temp;
}

StartScene::StartScene(Renderer* renderer) : Scene(renderer) {
    SDL_Rect btnSize = { 0,0,350,70 };
    int offset = 50;
    TTF_Font* font = TTF_OpenFont("assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 50);
    TTF_Font* bigFont = TTF_OpenFont("assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 100);

    SDL_Surface* playT = TTF_RenderText_Blended(font, "PLAY", white);
    SDL_Surface* optT = TTF_RenderText_Blended(font, "OPTIONS", white);
    SDL_Surface* quitT = TTF_RenderText_Blended(font, "QUIT", white);
    SDL_Surface* logoT = TTF_RenderText_Blended(bigFont, "CHESS", white);
    SDL_Surface* img = IMG_Load("assets\\imgs\\icon.jpg");

    Entity* playBtn = CreateBtn(renderer, playT, btnSize.w, btnSize.h, green, darkGreen);
    playBtn->SetPos(CalcPadding(WIDTH, btnSize.w), HEIGHT / 2 + offset);
    offset += btnSize.h + 20;

    // Entity& optBtn = CreateBtn(renderer, optT, btnSize.w, btnSize.h, grey, darkGrey);
    // optBtn.SetPos(CalcPadding(WIDTH, btnSize.w), HEIGHT / 2 + offset);
    // offset += btnSize.h + 20;

    // Entity& quitBtn = CreateBtn(renderer, quitT, btnSize.w, btnSize.h, red, darkRed);
    // quitBtn.SetPos(CalcPadding(WIDTH, btnSize.w), HEIGHT / 2 + offset);

    // Entity& imgS = *new Entity(renderer, img);
    // imgS.AddTexture(35, darkBlue);
    // imgS.SetPos({ WIDTH - img->w / 7 - 10,HEIGHT - img->h / 7 - 10,img->w / 7,img->h / 7 });

    // Entity& logo = *new Entity(renderer, logoT, -5);
    // logo.SetPos({ CalcPadding(WIDTH,600),50,600,200 });

    // Entity& cover = *new Entity(renderer, WIDTH, HEIGHT);

    AddItem("playBtn", playBtn);
    // AddItem("optBtn", optBtn);
    // AddItem("quitBtn", quitBtn);
    // AddItem("imgS", imgS);
    // AddItem("logo", logo);

    // this->GetEntity("logo").AddUpdateFunc("mainAnimation", [](Entity& entity) {
    //     static double i = 0;
    //     static SDL_Rect pos = entity.GetPos();

    //     entity.SetPos(pos.x, pos.y + 20 * sin(i * PI), pos.w, pos.h);
    //     i += 0.01;
    //     if (i >= 2.0) i = 0;
    //     });

    // this->GetEntity("quitBtn").AddUpdateFunc("quitEvent", [&](Entity& entity) {
    //     static bool isHover = false;
    //     static SDL_Rect pos = entity.GetPos();

    //     SDL_Point mousePos = renderer.GetMousePos();
    //     isHover = CheckCollide(&pos, &mousePos);

    //     if (isHover && renderer.CheckEvent(SDL_MOUSEBUTTONUP)) renderer.TerminateProgram();
    //     });

    // this->GetEntity("optBtn").AddUpdateFunc("changeOptEvent", [&](Entity& entity) {
    //     static bool isHover = false;
    //     static SDL_Rect pos = entity.GetPos();

    //     SDL_Point mousePos = renderer.GetMousePos();
    //     isHover = CheckCollide(&pos, &mousePos);

    //     if (isHover && renderer.CheckEvent(SDL_MOUSEBUTTONUP)) renderer.SetMainLoop(OptionScene::Get().GetLoopFunc());
    //     });

    // this->GetEntity("optBtn").AddUpdateFunc("changeOptEvent", [&](Entity& entity) {
    //     static bool isHover = false;
    //     static SDL_Rect pos = entity.GetPos();

    //     SDL_Point mousePos = renderer.GetMousePos();

    //     isHover = CheckCollide(&pos, &mousePos);
    //     if (isHover && renderer.CheckEvent(SDL_MOUSEBUTTONUP)) renderer.SetMainLoop(OptionScene::Get().GetLoopFunc());
    //     });

    TTF_CloseFont(font);
    TTF_CloseFont(bigFont);

    SDL_FreeSurface(playT);
    SDL_FreeSurface(optT);
    SDL_FreeSurface(quitT);
    SDL_FreeSurface(logoT);
    SDL_FreeSurface(img);
}
StartScene::~StartScene() {}

void StartScene::Loop() {
    std::cout << "Good " << std::endl;
    for (auto en : GetKeys()) renderer->Draw(GetItem(en));
}
void StartScene::Event() {}