#pragma once

#include <string>
#include <map>
#include <functional>

#include <src/Scene.h>

class SceneManager {
private:
    std::map<std::string, Scene&> scenes;
    std::string name;
public:
    SceneManager() {};
    ~SceneManager() {};

    void AddScene(std::string name, Scene& scene) { this->scenes.insert({ name, scene }); }
    void SetScene(std::string name) { this->name = name; };
    Scene& GetScene() { return scenes.at(name); }
    Scene& GetScene(std::string name) { return scenes.at(name); }
};