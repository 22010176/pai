#include <src/Scene.h>
#include <src/Texture.h>
#include <src/Scripts.h>

#include <cmath>

void LogoAnimation(Entity* entity) {
    static double i = 0;
    static SDL_Rect pos = entity->GetDisplayPos();

    entity->SetDisplayPos(pos.x, pos.y + 20 * sin(i * 3.141592));
    i += 0.01;
    if (i >= 2.0) i = 0;
}

void InitStartScene(Scene* scene) {
    int width, height; SDL_GetWindowSize(scene->GetRenderer()->GetWindow(), &width, &height);

    SDL_Rect btnSize = { 0,0,350,70 };
    int offset = 50;
    TTF_Font* font = TTF_OpenFont("assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 50);
    TTF_Font* bigFont = TTF_OpenFont("assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 100);

    SDL_Surface* playT = TTF_RenderText_Blended(font, "PLAY", white);
    Entity* playBtn = CreateBtn(scene->GetRenderer(), playT, btnSize.w, btnSize.h, green, darkGreen);
    playBtn->SetDisplayPos(GetMiddle({ 0,0,width,height }, { 0,offset,btnSize.w,btnSize.h }));
    offset += btnSize.h + 20;

    SDL_Surface* optT = TTF_RenderText_Blended(font, "OPTIONS", white);
    Entity* optBtn = CreateBtn(scene->GetRenderer(), optT, btnSize.w, btnSize.h, grey, darkGrey);
    optBtn->SetDisplayPos(GetMiddle({ 0,0,width,height }, { 0,offset,btnSize.w,btnSize.h }));
    offset += btnSize.h + 20;

    SDL_Surface* quitT = TTF_RenderText_Blended(font, "QUIT", white);
    Entity* quitBtn = CreateBtn(scene->GetRenderer(), quitT, btnSize.w, btnSize.h, red, darkRed);
    quitBtn->SetDisplayPos(GetMiddle({ 0,0,width,height }, { 0,offset,btnSize.w,btnSize.h }));

    SDL_Surface* img = IMG_Load("assets\\imgs\\icon.png");
    Entity* imgS = new Entity(scene->GetRenderer(), img);
    imgS->AddTexture(35, darkBlue)
        ->SetDisplayPos({ width - img->w / 7 - 10,height - img->h / 7 - 10,img->w / 7,img->h / 7 });

    SDL_Surface* logoT = TTF_RenderText_Blended(bigFont, "CHESS", white);
    Entity* logo = new Entity(scene->GetRenderer(), logoT);
    logo->SetDisplayPos({ CalcPadding<int>(width,600),50,600,200 })
        ->SetAngle(-10);


    logo->AddScript(LogoAnimation);

    // Entity& cover = *new Entity(renderer, WIDTH, HEIGHT);
    scene->AddItem("playBtn", playBtn);
    scene->AddItem("playBtn", playBtn);
    scene->AddItem("optBtn", optBtn);
    scene->AddItem("quitBtn", quitBtn);
    scene->AddItem("imgS", imgS);
    scene->AddItem("logo", logo);

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

void NormalLoop(Scene* scene, EventManager* events) {
    for (auto& value : scene->GetItems()) {
        value->RunScripts();
        scene->GetRenderer()->Draw(value);
    }
}