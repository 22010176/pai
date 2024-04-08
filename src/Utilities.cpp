#include "Utilities.h"

SDL_Texture* WriteText(SDL_Renderer* renderer, TTF_Font* font, std::string const message, SDL_Color color) {
    SDL_Surface* messageSurface = TTF_RenderText_Solid(font, message.c_str(), color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, messageSurface);
    SDL_FreeSurface(messageSurface);

    return texture;
}
SDL_Texture* DrawRect(SDL_Renderer* renderer, int width, int height, SDL_Color color) {
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, *(int*)&color, surface->h * surface->pitch);
    SDL_UnlockSurface(surface);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
}
SDL_Texture* DisplayImage(SDL_Renderer* renderer, std::string const path) {
    SDL_Surface* img = IMG_Load(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

    return texture;
}

SDL_Texture* CreateBtnTex(SDL_Renderer* renderer, SDL_Texture* text, SDL_Color color, int width, int height) {
    int w, h; SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
    SDL_Texture* result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w + width, h + height);

    SDL_Rect fillRect{ 0,0,w + width,h + height }, imgRect{ width / 2,height / 2,w,h };

    SDL_SetRenderTarget(renderer, result);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &fillRect);
    SDL_RenderCopy(renderer, text, NULL, &imgRect);
    SDL_SetRenderTarget(renderer, NULL);

    SDL_DestroyTexture(text);

    return result;
}

std::vector<std::string> SplitStr(std::string s, std::string del) {
    std::vector<std::string> result;
    int start, end = -1 * del.size();

    do {
        start = end + del.size();
        end = s.find(del, start);
        result.push_back(s.substr(start, end - start));
    } while (end != -1);

    return result;
}

bool CheckCollide(SDL_Rect* pos, SDL_Point* point) {
    return pos->y <= point->y && point->y <= pos->y + pos->h
        && pos->x <= point->x && point->x <= pos->x + pos->w;
}

SDL_Rect GetMiddle(const SDL_Rect& r1, const SDL_Rect& r2) {
    return { r1.x + CalcPadding(r1.w,r2.w),r1.y + CalcPadding(r1.h,r2.h),r2.w,r2.h };
}

SDL_Texture* CloneTexture(SDL_Renderer* renderer, SDL_Texture* texture) {
    int w, h; SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    SDL_Texture* res = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

    SDL_SetRenderTarget(renderer, res);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_SetRenderTarget(renderer, nullptr);

    return res;
}

SDL_Texture* CloneTexture(SDL_Renderer* renderer, SDL_Surface* surface) {
    SDL_Texture* res = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);
    SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_SetRenderTarget(renderer, res);
    SDL_RenderCopy(renderer, temp, nullptr, nullptr);
    SDL_SetRenderTarget(renderer, nullptr);

    SDL_DestroyTexture(temp);

    return res;
}