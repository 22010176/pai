#include <src/Sprite.h>
#include <src/Renderer.h>

Sprite::Sprite(Renderer* renderer, SDL_Surface* surface, double angle) : renderer(renderer), width(surface->w), height(surface->h) {
    this->texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
    AddTexture(surface, { 0,0,width,height });
}
Sprite::Sprite(Renderer* renderer, SDL_Texture* texture, double angle) : renderer(renderer) {
    SDL_QueryTexture(texture, nullptr, nullptr, &this->width, &this->height);
    this->texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
    AddTexture(texture, { 0,0,width,height });
}
Sprite::Sprite(Renderer* renderer, int width, int height, SDL_Color color) : renderer(renderer), width(width), height(height) {
    this->texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
    AddTexture({ 0,0,width,height }, color);
}
Sprite::Sprite(const Sprite& sprite) : renderer(sprite.renderer), width(sprite.GetWidth()), height(sprite.GetHeight()) {
    this->texture = sprite.ExportTexture();
    SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
}
Sprite::~Sprite() { SDL_DestroyTexture(this->texture); }

Sprite* Sprite::AddTexture(SDL_Texture* value, SDL_Rect position) {
    SDL_SetRenderTarget(renderer->GetRenderer(), this->texture);
    SDL_RenderCopy(renderer->GetRenderer(), value, nullptr, &position);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    return this;
}
Sprite* Sprite::AddTexture(SDL_Surface* value, SDL_Rect position) {
    SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer->GetRenderer(), value);
    AddTexture(temp, position);

    SDL_DestroyTexture(temp);

    return this;
}
Sprite* Sprite::AddTexture(SDL_Rect value, SDL_Color color) {
    SDL_SetRenderTarget(renderer->GetRenderer(), this->texture);
    SDL_SetRenderDrawColor(renderer->GetRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer->GetRenderer(), &value);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    return this;
}

Sprite* Sprite::AddTexture(int width, SDL_Color color) {
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

    return this;
}

SDL_Texture* Sprite::ExportTexture() const {
    SDL_Texture* texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->width, this->height);

    SDL_SetRenderTarget(renderer->GetRenderer(), texture);
    SDL_RenderCopy(renderer->GetRenderer(), this->texture, nullptr, nullptr);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    return texture;
}