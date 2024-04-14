#pragma once

#include <SDL2/SDL.h>

SDL_Texture* CopyTexture(SDL_Renderer* renderer, SDL_Texture* _src);
SDL_Texture* CreateTexture(SDL_Renderer* renderer, int width, int height);

SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Texture* _src, SDL_Rect* pos);
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Texture* _src, SDL_Rect pos);

SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Surface* _src, SDL_Rect* pos);
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Surface* _src, SDL_Rect pos);

SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Rect* _src, SDL_Color* pos);
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Rect _src, SDL_Color pos);
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Rect* _src, SDL_Color pos);
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Rect _src, SDL_Color* pos);

SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, int width, SDL_Color* color);
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, int width, SDL_Color color);