#pragma once

#include <SDL2/SDL.h>

#include <src/Manager.h>

class EventManager : protected Manager<SDL_EventType, SDL_Event> {
private:
public:
    void FetchEvent() {
        Clear();

        SDL_Event event;
        while (SDL_PollEvent(&event)) AddItem((SDL_EventType)event.type, SDL_Event(event));
    }

    SDL_Event* GetEvent(SDL_EventType type) {
        if (HasEvent(type)) return &GetItem(type);
        return nullptr;
    }
    bool HasEvent(SDL_EventType type) const { return HasItem(type); }
};