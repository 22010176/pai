#include "Renderer.h"
#include "Sprite.h"
Renderer Renderer::instance;

Renderer::Renderer(std::string title, int width, int height, std::string icon) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error Init SDL2" << std::endl;
        this->~Renderer();
        exit(-1);
    }

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
    if (this->window == nullptr) {
        std::cout << "Error Init Window" << std::endl;
        this->~Renderer();
        exit(-1);
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr) {
        std::cout << "Error Init Renderer" << std::endl;
        this->~Renderer();
        exit(-1);
    }

    if (TTF_Init() == -1 || IMG_Init(-1) == 0) {
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
    std::cout << "Finish Clean Up" << std::endl;
}

void Renderer::MainLoop() {
    SDL_Event e;
    while (isRunning) {
        this->Clear();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) this->isRunning = false;


            this->eventFunc(e);
        }

        this->mainLoop();

        this->Render();
        SDL_Delay(1000 / FPS);
    }
}

void Renderer::Draw(Sprite* sprite) {
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

void _Loop() {}
void _Event(SDL_Event&) {}

void Renderer::SetFullScrene() {}