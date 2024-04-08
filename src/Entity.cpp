#include "Entity.h"

// void __a(Entity&) {}

Entity::Entity(Renderer& renderer, SDL_Surface* surface, double angle) : Sprite(renderer, surface, angle) {
    this->textures.insert({ "_",this->texture });
    this->textures.insert({ "disable",nullptr });
    SetSprite("_");
}
Entity::Entity(Renderer& renderer, SDL_Texture* texture, double angle) : Sprite(renderer, texture, angle) {
    this->textures.insert({ "_",this->texture });
    this->textures.insert({ "disable",nullptr });
    SetSprite("_");
}
Entity::Entity(Renderer& renderer, SDL_Rect rect, SDL_Color color) : Sprite(renderer, rect, color) {
    this->textures.insert({ "_",this->texture });
    this->textures.insert({ "disable",nullptr });
    SetSprite("_");
}
Entity::Entity(Renderer& renderer, int width, int height) : Sprite(renderer, width, height) {
    this->textures.insert({ "_",this->texture });
    this->textures.insert({ "disable",nullptr });
    SetSprite("_");
}
Entity::~Entity() {
    // this->texture = nullptr;
    for (const auto& [key, value] : textures) SDL_DestroyTexture(value);
    std::cout << "Clear Btn" << std::endl;
}

void Entity::SetSprite(std::string name) {
    if (textures.find(name) == textures.end() || textures.at(name) == this->texture) return;
    this->texture = textures.at(name);
    SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
}
Entity& Entity::AddSprite(std::string name, SDL_Texture* texture) {
    if (texture == nullptr || name == "_") return *this;

    int w, h; SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    this->textures[name] = SDL_CreateTexture(renderer.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SetSprite(name);
    AddTexture(texture, { 0,0,w,h });

    return *this;
}
Entity& Entity::AddSprite(std::string name, SDL_Surface* surface) {
    if (surface == nullptr || name == "_") return *this;

    this->textures[name] = SDL_CreateTexture(renderer.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);
    SetSprite(name);
    AddTexture(surface, { 0,0,surface->w,surface->h });

    return *this;
}

Entity& Entity::AddSprite(std::string name, int width, int height) {
    if (width == 0 || height == 0 || name == "_") return *this;

    this->textures[name] = SDL_CreateTexture(renderer.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SetSprite(name);

    return *this;
}

Entity& Entity::AddSprite(std::string name) {
    if (name == "_") return *this;
    this->textures[name] = SDL_CreateTexture(renderer.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SetSprite(name);
    AddTexture(this->textures["_"], { 0,0,width,height });

    return *this;
}

