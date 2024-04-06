#include "Renderer.h"

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
    std::cout << "Finish Clean Up" << std::endl;
}
