#include <src/Scripts.h>
#include <src/Entity.h>

static bool isRunning = true;

void SetRunningState(bool val) { isRunning = val; }
bool GetRunningState() { return isRunning; }

SDL_Rect GetMiddle(SDL_Rect a, SDL_Rect b) { return { a.x + CalcPadding(a.w,b.w) + b.x, a.y + CalcPadding(a.h,b.h) + b.y,b.w,b.h }; }

bool CheckCollide(SDL_Point* p, SDL_Rect* rect) {
    return rect->x <= p->x && p->x <= rect->x + rect->w
        && rect->y <= p->y && p->y <= rect->y + rect->h;
}
bool CheckCollide(SDL_Point p, SDL_Rect rect) { return CheckCollide(&p, &rect); }
bool CheckCollide(SDL_Point p, SDL_Rect* rect) { return CheckCollide(&p, rect); }
bool CheckCollide(SDL_Point* p, SDL_Rect rect) { return CheckCollide(p, &rect); }

Entity* CreateBtn(Renderer* renderer, SDL_Surface* surface, int w, int h, SDL_Color def, SDL_Color hover) {
    SDL_Rect pos = GetMiddle({ 0,0,w,h }, { 0,0,surface->w,surface->h });

    Entity* temp = new Entity(renderer, w, h);
    temp->AddTexture({ 0,0,w,h }, &def)
        ->AddTexture(surface, &pos);

    temp->AddSprite("hover", w, h)
        ->SetSprite("hover")
        ->AddTexture({ 0,0,w,h }, &hover)
        ->AddTexture(surface, &pos);

    temp->SetSprite();

    temp->AddScript(HoverEffect);

    return temp;
}

void HoverEffect(Entity* entity) {
    SDL_Point mousePos; SDL_GetMouseState(&mousePos.x, &mousePos.y);
    if (!entity->HasItem("hover")) return;

    entity->SetSprite(CheckCollide(&mousePos, entity->GetDisplayPos()) ? "hover" : "default");
}