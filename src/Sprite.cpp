#include "Sprite.h"
#include "Renderer.h"
Renderer* Sprite::renderer = &Renderer::Get();

Sprite::Sprite(SDL_Surface* surface, double angle) : angle(angle), width(surface->w), height(surface->h) {
    this->texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    AddTexture(surface, { 0,0,width,height });
}
Sprite::Sprite(SDL_Texture* texture, double angle) : angle(angle) {
    SDL_QueryTexture(texture, nullptr, nullptr, &this->width, &this->height);
    this->texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    AddTexture(texture, { 0,0,width,height });
}
Sprite::Sprite(SDL_Rect rect, SDL_Color color) : width(rect.w), height(rect.h) {
    this->texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    AddTexture(rect, color, { 0,0,width,height });
}
Sprite::~Sprite() {
    SDL_DestroyTexture(this->texture);
    std::cout << "Finish free sprite" << std::endl;
}

Sprite& Sprite::SetTexture(SDL_Texture* texture) {
    this->texture = texture;
    SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
    return *this;
}

Sprite& Sprite::AddTexture(SDL_Texture* value, SDL_Rect position) {
    SDL_SetRenderTarget(renderer->GetRenderer(), this->texture);
    SDL_RenderCopy(renderer->GetRenderer(), value, nullptr, &position);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    // if (_del) SDL_DestroyTexture(texture);

    return *this;
}
Sprite& Sprite::AddTexture(SDL_Surface* value, SDL_Rect position) {
    SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer->GetRenderer(), value);
    AddTexture(temp, position);

    // if (_del) SDL_FreeSurface(value);

    return *this;
}
Sprite& Sprite::AddTexture(SDL_Rect value, SDL_Color color, SDL_Rect position) {
    SDL_SetRenderTarget(renderer->GetRenderer(), this->texture);
    SDL_SetRenderDrawColor(renderer->GetRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer->GetRenderer(), &value);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    return *this;
}