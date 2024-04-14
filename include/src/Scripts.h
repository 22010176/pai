#pragma once

#include <functional>
#include <vector>

#include <SDL2/SDL.h>

#include <src/Renderer.h>

template <typename T1, typename T2> struct Script {
    bool enable = true;
    const std::function<T1(T2)> callback;
};

void SetRunningState(bool val = true);
bool GetRunningState();

bool CheckCollide(SDL_Point p, SDL_Rect rect);
bool CheckCollide(SDL_Point* p, SDL_Rect* rect);
bool CheckCollide(SDL_Point p, SDL_Rect* rect);
bool CheckCollide(SDL_Point* p, SDL_Rect rect);

template <typename T> T CalcPadding(T a, T b) { return (a - b) / 2; }
SDL_Rect GetMiddle(SDL_Rect a, SDL_Rect b);

Entity* CreateBtn(Renderer* renderer, SDL_Surface* surface, int w, int h, SDL_Color def, SDL_Color hover);

void HoverEffect(Entity* entity);