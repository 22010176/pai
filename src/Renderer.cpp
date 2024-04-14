#include <src/Entity.h>
#include <src/Renderer.h>

Renderer::Renderer(std::string title, int width, int height, std::string icon) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error Init SDL2" << std::endl;
        this->~Renderer();
        exit(-1);
    }

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
    SDL_SetWindowOpacity(this->window, 0.0);

    if (this->window == nullptr) {
        std::cout << "Error Init Window" << std::endl;
        this->~Renderer();
        exit(-1);
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetWindowOpacity(this->window, 1.0);
    SDL_SetWindowSize(this->window, width, height);
    SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_RenderSetVSync(this->renderer, 1);

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
    SDL_Surface* surface = IMG_Load(icon.c_str());
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

void Renderer::Clear() const {
    SDL_SetRenderTarget(this->renderer, nullptr);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
}
void Renderer::Draw(Entity* sprite) const {
    if (sprite->GetCurrentTexture() == nullptr) return;
    SDL_Rect position = sprite->GetDisplayPos();
    SDL_RenderCopyEx(this->renderer, sprite->GetCurrentTexture(), nullptr, &position, sprite->GetAngle(), nullptr, SDL_FLIP_NONE);
}
void Renderer::Render() const { SDL_RenderPresent(this->renderer); }