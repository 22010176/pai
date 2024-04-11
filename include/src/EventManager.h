#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include <src/Manager.h>

class EventManager : public Manager<SDL_EventType, SDL_Event> {
private:
    SDL_Event event;

public:
    EventManager() {}
    EventManager(const EventManager&) = delete;
    ~EventManager() {};

    void FetchEvent() {
        Clear();
        while (SDL_PollEvent(&this->event))
            AddItem((SDL_EventType)this->event.type, SDL_Event(event));
    }
};

