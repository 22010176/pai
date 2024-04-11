#include <src/Entity.h>

Entity::Entity(Renderer& renderer, SDL_Surface* surface, double angle) : Sprite(renderer, surface, angle) { Init(); }
Entity::Entity(Renderer& renderer, SDL_Texture* texture, double angle) : Sprite(renderer, texture, angle) { Init(); }
Entity::Entity(Renderer& renderer, int width, int height, SDL_Color color) : Sprite(renderer, width, height, color) { Init(); }
Entity::~Entity() { for (const auto& tex : GetItems()) SDL_DestroyTexture(tex); }

void Entity::Init() {
    AddSprite("default", this->texture);
    AddSprite("hide", (SDL_Texture*)nullptr);

    SetSprite("default");
}
Entity& Entity::SetSprite(std::string name) {
    if (!HasItem(name)) return AddSprite(name);
    if (GetItem(name) == this->texture) return *this;

    this->texture = GetItem(name);
    SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);

    return *this;
}
Entity& Entity::AddSprite(std::string name, SDL_Texture* texture) {
    if (texture == nullptr || name == "") return *this;

    int w, h; SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    AddItem(name, SDL_CreateTexture(renderer.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h));
    SetSprite(name);
    AddTexture(texture, { 0,0,w,h });

    return *this;
}
Entity& Entity::AddSprite(std::string name, SDL_Surface* surface) {
    if (surface == nullptr || name == "") return *this;

    AddItem(name, SDL_CreateTexture(renderer.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, surface->w, surface->h));
    SetSprite(name);
    AddTexture(surface, { 0,0,surface->w,surface->h });

    return *this;
}

Entity& Entity::AddSprite(std::string name, int width, int height) {
    if (width == 0 || height == 0 || name == "") return *this;

    AddItem(name, SDL_CreateTexture(renderer.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height));
    return SetSprite(name);
}

Entity& Entity::AddSprite(std::string name) {
    if (name == "") return *this;

    SDL_Texture* texture = SDL_CreateTexture(renderer.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->width, this->height);
    AddSprite(name, texture);
    return SetSprite(name);
}
