#include <src/Entity.h>
#include <src/Renderer.h>
#include <src/Scripts.h>

SDL_Texture* Entity::CreateTexture(int width, int height) const {
    SDL_Texture* texture = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    return texture;
}

Entity::Entity(Renderer* renderer, SDL_Surface* surface) : renderer(renderer) {
    AddSprite("default", surface);
    SetSprite();
}
Entity::Entity(Renderer* renderer, SDL_Texture* texture) : renderer(renderer) {
    AddSprite("default", texture);
    SetSprite();
}
Entity::Entity(Renderer* renderer, int width, int height) : renderer(renderer) {
    AddSprite("default", width, height);
    SetSprite();
}
Entity::Entity(const Entity& sprite) : renderer(sprite.renderer) {
    AddSprite("default", sprite.GetCurrentTexture());
    SetSprite();
}
Entity::~Entity() {
    for (auto& s : scripts) delete s;
    for (auto& [key, tex] : pools) SDL_DestroyTexture(tex);
    std::cout << "Clear Entity" << std::endl;
}

SDL_Texture* Entity::ExportCurrentTexture() const {
    SDL_Texture* texture = CreateTexture(width, height);

    SDL_SetRenderTarget(renderer->GetRenderer(), texture);
    SDL_RenderCopy(renderer->GetRenderer(), this->texture, nullptr, nullptr);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    return texture;
}
Entity* Entity::SetSprite(std::string name) {
    if (!HasItem(name)) return this;

    this->texture = GetItem(name);
    SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);

    return this;
}
Entity* Entity::AddSprite(std::string name, SDL_Texture* texture) {
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SDL_Texture* temp = CreateTexture(width, height);

    SDL_SetRenderTarget(renderer->GetRenderer(), temp);
    SDL_RenderCopy(renderer->GetRenderer(), texture, nullptr, nullptr);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    AddItem(name, temp);

    return this;
}
Entity* Entity::AddSprite(std::string name, SDL_Surface* surface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->GetRenderer(), surface);
    AddSprite(name, texture);
    SDL_DestroyTexture(texture);

    return this;
}
Entity* Entity::AddSprite(std::string name, int width, int height) { AddItem(name, CreateTexture(width, height)); return this; }
Entity* Entity::AddTexture(SDL_Texture* texture, SDL_Rect position) { AddTexture(texture, &position); return this; }
Entity* Entity::AddTexture(SDL_Texture* texture, SDL_Rect* position) {
    SDL_SetRenderTarget(renderer->GetRenderer(), this->texture);
    SDL_RenderCopy(renderer->GetRenderer(), texture, nullptr, position);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    return this;
}

Entity* Entity::AddTexture(SDL_Surface* surface, SDL_Rect position) { AddTexture(surface, &position); return this; }
Entity* Entity::AddTexture(SDL_Surface* surface, SDL_Rect* position) {
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer->GetRenderer(), surface);
    AddTexture(tex, position);
    SDL_DestroyTexture(tex);

    return this;
}
Entity* Entity::AddTexture(SDL_Rect rect, SDL_Color color) { AddTexture(&rect, &color); return this; }
Entity* Entity::AddTexture(SDL_Rect rect, SDL_Color* color) { AddTexture(&rect, color); return this; }
Entity* Entity::AddTexture(SDL_Rect* rect, SDL_Color color) { AddTexture(rect, &color); return this; }
Entity* Entity::AddTexture(SDL_Rect* rect, SDL_Color* color) {
    SDL_SetRenderTarget(renderer->GetRenderer(), this->texture);
    SDL_SetRenderDrawColor(renderer->GetRenderer(), color->r, color->g, color->b, color->a);
    SDL_RenderFillRect(renderer->GetRenderer(), rect);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    return this;
}

Entity* Entity::AddTexture(int outlineSize, SDL_Color color) { AddTexture(outlineSize, &color); return this; }
Entity* Entity::AddTexture(int outlineSize, SDL_Color* color) {
    SDL_Rect s[]{
        { 0,0,this->width,outlineSize },
        { 0,this->height - outlineSize,this->width,outlineSize },
        { 0,0,outlineSize,this->height },
        { this->width - outlineSize,0,outlineSize,this->width },
    };

    SDL_SetRenderTarget(renderer->GetRenderer(), this->texture);
    SDL_SetRenderDrawColor(renderer->GetRenderer(), color->r, color->g, color->b, color->a);
    for (SDL_Rect& rect : s) SDL_RenderFillRect(renderer->GetRenderer(), &rect);
    SDL_SetRenderTarget(renderer->GetRenderer(), nullptr);

    return this;
}

Script<void, Entity*>* Entity::AddScript(std::function<void(Entity*)> callback) {
    Script<void, Entity*>* script = new Script<void, Entity*>{ true,callback };
    scripts.push_back(script);

    return script;
}
Script<void, Entity*>* Entity::SetScriptState(Script<void, Entity*>* script, bool state) {
    for (size_t i = 0; i < scripts.size(); ++i) if (scripts.at(i) == script) {
        script->enable = state;
        return script;
    }

    return nullptr;
}