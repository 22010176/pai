#pragma once

#include <string>
#include <map>
#include <functional>

#include <src/Manager.h>
#include <src/Scene.h>

class SceneManager : public Manager<std::string, Scene*> {
private:
    std::string name;

public:
    SceneManager() {}
    ~SceneManager() {}

    void SetScene(std::string name) { this->name = name; }
    void LoopFunc() {
        GetItem(name)->Loop();
        for (auto& f : GetItem(name)->callbacks) f();
    }
};