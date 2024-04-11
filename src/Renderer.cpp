#include "Renderer.h"
#include "Sprite.h"



Renderer::Renderer(std::string title, int width, int height, std::string icon) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error Init SDL2" << std::endl;
        this->~Renderer();
        exit(-1);
    }

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
    SDL_SetWindowOpacity(this->window, 0.0);

    if (this->window == nullptr) {
        std::cout << "Error Init Window" << std::endl;
        this->~Renderer();
        exit(-1);
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetWindowOpacity(this->window, 1.0);

    if (this->renderer == nullptr) {
        std::cout << "Error Init Renderer" << std::endl;
        this->~Renderer();
        exit(-1);
    }

    if (TTF_Init() == -1 || IMG_Init(-1) == 0 || Mix_Init(-1) == 0) {
        std::cout << "Error Init Library" << std::endl;
        this->~Renderer();
        exit(-1);
    }

    std::cout << "Successful initialize library!" << std::endl;

    if (icon == "") return;
    SDL_Surface* surface = IMG_Load("./assets/imgs/icon.jpg");
    SDL_SetWindowIcon(this->window, surface);

    SDL_FreeSurface(surface);
    std::cout << "Successfull initialize program's icon!" << std::endl;
}
Renderer::~Renderer() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    std::cout << "Finish clear renderer" << std::endl;
}

void Renderer::MainLoop() {
    while (isRunning) {
        this->Clear();
        events.FetchEvent();

        if (events.CheckEvent(SDL_QUIT)) this->isRunning = false;

        this->mainLoop();

        this->Render();
        events.ClearEvent();

        SDL_Delay(1000 / FPS);
    }
}

void Renderer::Draw(Sprite* sprite) {
    if (sprite->GetTexture() == nullptr) return;

    sprite->Update();

    SDL_Rect pos = sprite->GetPos();
    if (sprite->GetAngle() == 0.0) {
        SDL_RenderCopy(renderer, sprite->GetTexture(), nullptr, &pos);
        return;
    }
    SDL_RenderCopyEx(renderer, sprite->GetTexture(), nullptr, &pos, sprite->GetAngle(), nullptr, SDL_FLIP_NONE);
}

void Renderer::Clear() const {
    SDL_SetRenderTarget(this->renderer, nullptr);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
}

void Renderer::SetFullScrene() {}