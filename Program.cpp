#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <src/Renderer.h>
#include <src/Sprite.h>
#include <src/Utilities.h>
#include <src/GameOptions.h>

#include <Constant.h>

void DrawStartScene() {
    SDL_Rect btnSize = { 0,0,350,70 };
    int offset = 50;
    TTF_Font* font = TTF_OpenFont(".\\assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 50);
    TTF_Font* bigFont = TTF_OpenFont(".\\assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 100);

    SDL_Surface* playT = TTF_RenderText_Blended(font, "PLAY", white);
    SDL_Surface* optT = TTF_RenderText_Blended(font, "OPTIONS", white);
    SDL_Surface* quitT = TTF_RenderText_Blended(font, "QUIT", white);
    SDL_Surface* logoT = TTF_RenderText_Blended(bigFont, "CHESS", white);
    SDL_Surface* img = IMG_Load(".\\assets\\imgs\\icon.jpg");

    Sprite playBtn(btnSize, green);
    playBtn
        .AddTexture(playT, GetMiddle(btnSize, { 0,0,playT->w,playT->h }))
        .SetPos(CalcPadding(GameOptions::Get().GetWidth(), btnSize.w), GameOptions::Get().GetHeight() / 2 + offset);
    offset += btnSize.h + 20;

    Sprite optBtn(btnSize, grey);
    optBtn
        .AddTexture(optT, GetMiddle(btnSize, { 0,0,optT->w,optT->h }))
        .SetPos(CalcPadding(GameOptions::Get().GetWidth(), btnSize.w), GameOptions::Get().GetHeight() / 2 + offset);
    offset += btnSize.h + 20;

    Sprite quitBtn(btnSize, red);
    quitBtn
        .AddTexture(quitT, GetMiddle(btnSize, { 0,0,quitT->w,quitT->h }))
        .SetPos(CalcPadding(GameOptions::Get().GetWidth(), btnSize.w), GameOptions::Get().GetHeight() / 2 + offset);

    Sprite imgS(img);
    imgS
        .AddTexture(35, darkBlue)
        .SetPos({ GameOptions::Get().GetWidth() - img->w / 7 - 10,GameOptions::Get().GetHeight() - img->h / 7 - 10,img->w / 7,img->h / 7 });

    Sprite logo(logoT, -5);
    logo.SetPos({ CalcPadding(GameOptions::Get().GetWidth(),600),50,600,200 });

    SDL_FreeSurface(playT);
    SDL_FreeSurface(optT);
    SDL_FreeSurface(quitT);
    SDL_FreeSurface(logoT);
    SDL_FreeSurface(img);

    TTF_CloseFont(font);
    TTF_CloseFont(bigFont);

    //     Renderer::Get().Draw(&playBtn);
    // Renderer::Get().Draw(&optBtn);
    // Renderer::Get().Draw(&quitBtn);
    // Renderer::Get().Draw(&imgS);
    // Renderer::Get().Draw(&logo);
}

void OptionsScene() {
    TTF_Font* font = TTF_OpenFont(".\\assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 35);
    TTF_Font* nfont = TTF_OpenFont(".\\assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 45);
    TTF_Font* tfont = TTF_OpenFont(".\\assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 70);

    SDL_Surface* backT = TTF_RenderText_Blended(font, "<", white);
    SDL_Surface* optT = TTF_RenderText_Blended(tfont, "OPTIONS", white);
    SDL_Surface* fullScene = TTF_RenderText_Blended(nfont, "Full-screen", white);

    Sprite optionBg(WIDTH, GameOptions::Get().GetHeight());
    optionBg
        .AddTexture({ 0,0,WIDTH,GameOptions::Get().GetHeight() }, darkGrey)
        .SetPos(0, 0);

    Sprite optionsText(optT->w, optT->h);
    optionsText
        .AddTexture({ 0,0,optT->w,optT->h }, darkGrey)
        .AddTexture(optT, { 0,0,optT->w,optT->h })
        .SetPos(50, 50)
        .SetAngle(-10);

    Sprite backBtn(45, 45);
    backBtn
        .AddTexture(backT, { CalcPadding(45,backT->w),CalcPadding(45,backT->h),backT->w,backT->h })
        .AddTexture(3, white)
        .SetPos(10, 10);

    Sprite fullS(fullScene->w, fullScene->h);
    fullS
        .AddTexture({ 0,0,fullScene->w,fullScene->h }, darkGrey)
        .AddTexture(fullScene, { 0,0,fullScene->w,fullScene->h })
        .SetPos(100, 200);

    Sprite checkBox(30, 30);
    checkBox
        .AddTexture({ 0,0,30,30 }, white)
        .AddTexture(3, black)
        .SetPos(fullS.GetPos().x + fullS.GetPos().w + 500, fullS.GetPos().y + CalcPadding(fullS.GetHeight(), 30));

    SDL_FreeSurface(backT);
    SDL_FreeSurface(optT);
    SDL_FreeSurface(fullScene);
    TTF_CloseFont(font);
    TTF_CloseFont(nfont);
    TTF_CloseFont(tfont);

    //

    // Renderer::Get().Draw(&optionBg);
    // Renderer::Get().Draw(&backBtn);
    // Renderer::Get().Draw(&fullS);
    // Renderer::Get().Draw(&optionsText);
    // Renderer::Get().Draw(&checkBox);
}

int main(int argc, char* argv[]) {
    // Renderer::Get().SetMainLoop(StartScene::Get().MainLoop());
    // Renderer::Get().SetEventFunc(StartScene::Get().EventFunc());

    // int* a = new int;
    // int& b = *a;
    // std::cout << &b << " " << a;

    Renderer::Get().MainLoop();


    return 0;
}
