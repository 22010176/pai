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


Entity& CreateBtn(Renderer& renderer, SDL_Surface* surface, int w, int h, SDL_Color color, SDL_Color hoverColor) {
    const std::function<void(Entity&)> hoverFunc = [&](Entity& entity) {
        SDL_Point mousePos = renderer.GetMousePos();
        SDL_Rect rectPos = entity.GetPos();

        if (CheckCollide(&rectPos, &mousePos)) entity.SetSprite("hover");
        else entity.SetSprite();
        };


    std::function<void(Entity&)> clickFunc = [&](Entity& entity) {
        static double ratio = 0.95;
        static std::map<Entity*, SDL_Rect> pos;
        static bool isClick = false;

        SDL_Point mousePos = renderer.GetMousePos();
        if (pos.find(&entity) == pos.end()) pos[&entity] = entity.GetPos();

        SDL_Rect& pos_ = pos.at(&entity);
        if (renderer.CheckEvent(SDL_MOUSEBUTTONDOWN)) isClick = true;
        else if (renderer.CheckEvent(SDL_MOUSEBUTTONUP)) isClick = false;

        if (isClick && CheckCollide(&pos_, &mousePos)) {
            int w_ = pos_.w * ratio, h_ = pos_.h * ratio;
            entity.SetPos(pos_.x + CalcPadding(pos_.w, w_), pos_.y + CalcPadding(pos_.h, h_), w_, h_);
        }
        else entity.SetPos(pos_);
        };


    SDL_Rect pos = GetMiddle({ 0,0,w,h }, { 0,0,surface->w,surface->h });
    Entity& btn = *new Entity(renderer, w, h);
    btn
        .AddTexture({ 0,0,w,h }, color)
        .AddTexture(surface, pos);
    btn
        .AddSprite("hover", w, h)
        .AddTexture({ 0,0,w,h }, hoverColor)
        .AddTexture(surface, pos);

    btn.AddUpdateFunc("HoverEvent", hoverFunc);
    btn.AddUpdateFunc("ClickEvent", clickFunc);

    return btn;
}

// std::function<void(Entity&)> ClickEvent(Renderer& renderer, std::function<void(Entity&)> func) {
//     return [&](Entity& entity) {
//         static bool isClick = false;

//         SDL_Point mousePos = renderer.GetMousePos();
//         static SDL_Rect pos = entity.GetPos();

//         if (renderer.CheckEvent(SDL_MOUSEBUTTONDOWN) && CheckCollide(&pos, &mousePos)) {
//             isClick = true;
//             return;
//         }

//         if (isClick && renderer.CheckEvent(SDL_MOUSEBUTTONUP)) func(entity);
//         };
// }