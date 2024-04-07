#include "Sprite.h"
#include "Renderer.h"
Renderer* Sprite::renderer = &Renderer::Get();

Sprite::Sprite(SDL_Surface* surface, double angle) : angle(angle), width(surface->w), height(surface->h) {
    this->texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
    AddTexture(surface, { 0,0,width,height });
}
Sprite::Sprite(SDL_Texture* texture, double angle) : angle(angle) {
    SDL_QueryTexture(texture, nullptr, nullptr, &this->width, &this->height);
    this->texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
    AddTexture(texture, { 0,0,width,height });
}
Sprite::Sprite(SDL_Rect rect, SDL_Color color) : pos(rect), width(rect.w), height(rect.h) {
    this->texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
    AddTexture(rect, color);
}
Sprite::Sprite(int width, int height) : width(width), height(height) {
    this->texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
}
Sprite::~Sprite() { SDL_DestroyTexture(this->texture); }

Sprite& Sprite::AddTexture(SDL_Texture* value, SDL_Rect position) {
    SDL_SetRenderTarget(renderer->GetRenderer(), this->texture);
    SDL_RenderCopy(renderer->GetRenderer(), value, nullptr, &position);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    return *this;
}
Sprite& Sprite::AddTexture(SDL_Surface* value, SDL_Rect position) {
    SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer->GetRenderer(), value);
    AddTexture(temp, position);

    return *this;
}
Sprite& Sprite::AddTexture(SDL_Rect value, SDL_Color color) {
    SDL_SetRenderTarget(renderer->GetRenderer(), this->texture);
    SDL_SetRenderDrawColor(renderer->GetRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer->GetRenderer(), &value);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    return *this;
}

Sprite& Sprite::AddTexture(int width, SDL_Color color) {
    SDL_Rect s[]{
        { 0,0,this->width,width },
        { 0,this->height - width,this->width,width },
        { 0,0,width,this->height },
        { this->width - width,0,width,this->width },
    };

    SDL_SetRenderTarget(renderer->GetRenderer(), this->texture);
    SDL_SetRenderDrawColor(renderer->GetRenderer(), color.r, color.g, color.b, color.a);
    for (SDL_Rect& rect : s) SDL_RenderFillRect(renderer->GetRenderer(), &rect);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    return *this;
}