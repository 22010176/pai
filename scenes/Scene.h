#pragma once

#include <src/Renderer.h>
#include <src/Observer/Subject.h>

class Scene : public ObserverSubject<SDL_Event> {
protected:
    inline static int idSeed = 0;
    Renderer& renderer = Renderer::Get();
public:
    Scene() : ObserverSubject() {}
    ~Scene() {}
    virtual void MainLoop() = 0;
};
