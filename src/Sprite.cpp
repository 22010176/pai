#include "Sprite.h"

// Renderer& Sprite::renderer = Renderer::Get();

Sprite::Sprite(SDL_Surface* surface, double angle, bool active) : angle(angle), active(active) {
    this->texture = SDL_CreateTexture(Renderer::Get().GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);
    this->width = surface->w, this->height = surface->h;
    AddTexture(surface, { 0,0,width,height });
}
Sprite::Sprite(SDL_Texture* texture, double angle, bool active) {
    SDL_QueryTexture(texture, nullptr, nullptr, &this->width, &this->height);
    this->texture = SDL_CreateTexture(Renderer::Get().GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    AddTexture(texture, { 0,0,width,height });
}
Sprite::Sprite(SDL_Rect rect, SDL_Color color) : width(rect.w), height(rect.h) {
    this->texture = SDL_CreateTexture(Renderer::Get().GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    AddTexture(rect, color, { 0,0,width,height });
}
Sprite::~Sprite() {
    SDL_DestroyTexture(this->texture);
    std::cout << "Finish free sprite" << std::endl;
}

Sprite& Sprite::AddTexture(SDL_Texture* value, SDL_Rect position) {
    SDL_SetRenderTarget(Renderer::Get().GetRenderer(), this->texture);
    SDL_RenderCopy(Renderer::Get().GetRenderer(), value, nullptr, &position);
    SDL_SetRenderTarget(Renderer::Get().GetRenderer(), nullptr);

    return *this;
}
Sprite& Sprite::AddTexture(SDL_Surface* value, SDL_Rect position) {
    SDL_Texture* temp = SDL_CreateTextureFromSurface(Renderer::Get().GetRenderer(), value);
    AddTexture(temp, position);
    SDL_DestroyTexture(temp);

    return *this;
}
Sprite& Sprite::AddTexture(SDL_Rect value, SDL_Color color, SDL_Rect position) {
    SDL_SetRenderTarget(Renderer::Get().GetRenderer(), this->texture);
    SDL_SetRenderDrawColor(Renderer::Get().GetRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(Renderer::Get().GetRenderer(), &value);
    SDL_SetRenderTarget(Renderer::Get().GetRenderer(), nullptr);

    return *this;
}