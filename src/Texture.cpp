#include <src/Texture.h>

SDL_Texture* CopyTexture(SDL_Renderer* renderer, SDL_Texture* _src) {
    int width, height; SDL_QueryTexture(_src, nullptr, nullptr, &width, &height);
    SDL_Texture* texture = CreateTexture(renderer, width, height);

    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderCopy(renderer, _src, nullptr, nullptr);
    SDL_SetRenderTarget(renderer, nullptr);

    return texture;
}
SDL_Texture* CreateTexture(SDL_Renderer* renderer, int width, int height) {
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    return texture;
}

SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Texture* _src, SDL_Rect* pos) {
    SDL_SetRenderTarget(renderer, _dst);
    SDL_RenderCopy(renderer, _src, nullptr, pos);
    SDL_SetRenderTarget(renderer, nullptr);

    return _dst;
}
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Texture* _src, SDL_Rect pos) { return AddTexture(renderer, _dst, _src, &pos); }

SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Surface* _src, SDL_Rect* pos) {
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, _src);
    AddTexture(renderer, _dst, tex, pos);
    SDL_DestroyTexture(tex);

    return _dst;
}
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Surface* _src, SDL_Rect pos) { return AddTexture(renderer, _dst, _src, &pos); }

SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Rect* _src, SDL_Color* color) {
    SDL_SetRenderTarget(renderer, _dst);
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderFillRect(renderer, _src);
    SDL_SetRenderTarget(renderer, nullptr);

    return _dst;
}
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Rect _src, SDL_Color color) { return AddTexture(renderer, _dst, &_src, &color); }
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Rect* _src, SDL_Color color) { return AddTexture(renderer, _dst, _src, &color); }
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, SDL_Rect _src, SDL_Color* color) { return AddTexture(renderer, _dst, &_src, color); }

SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, int width, SDL_Color* color) {
    int w, h; SDL_QueryTexture(_dst, nullptr, nullptr, &w, &h);
    SDL_Rect s[]{
        { 0,0,w,width },
        { 0,h - width,w,width },
        { 0,0,width,h },
        { w - width,0,width,w },
    };

    SDL_SetRenderTarget(renderer, _dst);
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    for (SDL_Rect& rect : s) SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderTarget(renderer, nullptr);

    return _dst;
}
SDL_Texture* AddTexture(SDL_Renderer* renderer, SDL_Texture* _dst, int width, SDL_Color color) { return AddTexture(renderer, _dst, width, &color); }
