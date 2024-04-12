#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include <src/Manager.h>

class EventManager : public Manager<SDL_EventType, SDL_Event> {
public:
    EventManager() {}
    EventManager(const EventManager&) = delete;
    ~EventManager() {};

    void FetchEvent() {
        Clear();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            AddItem((SDL_EventType)event.type, SDL_Event(event));
        }
    }
};

