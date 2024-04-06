#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <src/Sprite.h>
#include <src/Renderer.h>
#include <src/Utilities.h>
#include <Constant.h>

std::function <void()> scene;

int main(int argc, char* argv[]) {
    SDL_Rect btnSize = { 0,0,250,70 };
    int offset = 50;
    TTF_Font* font = TTF_OpenFont(".\\assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 50);
    TTF_Font* bigFont = TTF_OpenFont(".\\assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 100);

    SDL_Surface* playT = TTF_RenderText_Solid(font, "Test", white);
    SDL_Surface* optT = TTF_RenderText_Solid(font, "OPTIONS", white);
    SDL_Surface* quitT = TTF_RenderText_Solid(font, "QUIT", white);
    SDL_Surface* logoT = TTF_RenderText_Solid(bigFont, "CHESS", white);
    SDL_Surface* img = IMG_Load(".\\assets\\imgs\\icon.jpg");

    Sprite playBtn(btnSize, green);
    playBtn
        .AddTexture(playT, GetMiddle(btnSize, { 0,0,playT->w,playT->h }))
        .SetPos({ CalcPadding(WIDTH,btnSize.w),HEIGHT / 2 + offset,btnSize.w,btnSize.h });
    offset += btnSize.h + 20;

    Sprite optBtn(btnSize, grey);
    optBtn
        .AddTexture(optT, GetMiddle(btnSize, { 0,0,optT->w,optT->h }))
        .SetPos({ CalcPadding(WIDTH,btnSize.w),HEIGHT / 2 + offset,btnSize.w,btnSize.h });
    offset += btnSize.h + 20;

    Sprite quitBtn(btnSize, red);
    quitBtn
        .AddTexture(quitT, GetMiddle(btnSize, { 0,0,quitT->w,quitT->h }))
        .SetPos({ CalcPadding(WIDTH,btnSize.w),HEIGHT / 2 + offset,btnSize.w,btnSize.h });


    Sprite imgS(img);
    imgS.SetPos({ WIDTH - img->w / 7 - 10,HEIGHT - img->h / 7 - 10,img->w / 7,img->h / 7 });

    Sprite logo(logoT, -10);
    logo.SetPos({ CalcPadding(WIDTH,500),50,500,200 });

    bool isRunning = true;
    SDL_Event event;
    while (isRunning) {
        Renderer::Get().Clear();

        // put in StartScreen function
        Renderer::Get().Draw(&playBtn);
        Renderer::Get().Draw(&optBtn);
        Renderer::Get().Draw(&quitBtn);
        Renderer::Get().Draw(&imgS);
        Renderer::Get().Draw(&logo);

        Renderer::Get().Render();


        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;

            default:
                break;
            }
        }
        SDL_Delay(1000 / FPS);
    }

    SDL_FreeSurface(playT);
    SDL_FreeSurface(optT);
    SDL_FreeSurface(quitT);
    SDL_FreeSurface(logoT);
    SDL_FreeSurface(img);

    TTF_CloseFont(font);
    return 0;
}