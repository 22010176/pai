#pragma once

#include <string>
#include <vector>
#include <map>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// #define max(a, b)                               (a) > (b) ? (a) : (b)
// #define min(a, b)                               (a) < (b) ? (a) : (b)
#define CalcPadding(width, innerWidth)          ((width) - (innerWidth)) / 2 

std::vector<std::string> SplitStr(std::string s, std::string del = " ");
bool CheckCollide(SDL_Rect* pos, SDL_Point* point);

SDL_Texture* WriteText(SDL_Renderer* renderer, TTF_Font* font, std::string const message, SDL_Color color);
SDL_Texture* DrawRect(SDL_Renderer* renderer, int width, int height, SDL_Color color = { 255,255,255,255 });
SDL_Texture* DisplayImage(SDL_Renderer* renderer, std::string const path);
SDL_Texture* CreateBtnTex(SDL_Renderer* renderer, SDL_Texture* text, SDL_Color color, int width = 10, int height = 10);

SDL_Rect GetMiddle(const SDL_Rect& r1, const SDL_Rect& r2);

SDL_Texture* CloneTexture(SDL_Renderer* renderer, SDL_Texture* texture);
SDL_Texture* CloneTexture(SDL_Renderer* renderer, SDL_Surface* texture);

