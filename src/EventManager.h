#pragma once

#include <vector>

#include <SDL2/SDL.h>

class EventManager {
private:
    std::vector<SDL_Event> events{};
    SDL_Event event;

public:
    EventManager() {}
    EventManager(const EventManager&) = delete;
    ~EventManager() {};

    void FetchEvent() { while (SDL_PollEvent(&this->event)) events.push_back(this->event); }
    SDL_Event GetEvent(SDL_EventType type) const {
        for (const SDL_Event& e : events)
            if (e.type == type) return e;

        return {};
    }
    bool CheckEvent(SDL_EventType type) const {
        for (const SDL_Event& e : events)
            if (e.type == type) return true;
        return false;
    }
    void ClearEvent() { events.clear(); }
};

