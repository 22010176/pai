#pragma once

#include <map>
#include <functional>
#include <string>

#include "Sprite.h"
#include "Observer/Observer.h"

class GameObject : public Sprite, public Observer<SDL_Event> {
private:
    SDL_Rect position{ 0,0,0,0 };
    std::map<std::string, Sprite> sprites{};
    std::function<void(GameObject&, SDL_Event&)> updateFunc;

    GameObject& operator=(Sprite& other) {
        this->SetTexture(other.GetTexture());
        this->SetAngle(other.GetAngle());

        return *this;
    }
public:
    GameObject(SDL_Rect position, std::function<void(GameObject&, SDL_Event&)> callback) :
        Sprite({ 0,0,position.w,position.h }), position(position), updateFunc(callback) {}

    SDL_Rect GetPosition() const { return this->position; }
    void SetPosition(SDL_Rect value) { this->position = value; }

    Sprite& GetSprite(std::string type = "") { return type == "" ? *this : sprites.at(type); }
    Sprite& AddSprite(std::string type, Sprite& sprite) {
        sprites.insert({ type,Sprite(sprite) });
        return SetSprite(type);
    }
    Sprite& AddSprite(std::string type, Sprite sprite) {
        sprites.insert({ type,Sprite(sprite) });
        return sprites.at(type);
    }
    Sprite& SetSprite(std::string& type) {
        if (sprites.find(type) == sprites.end()) return *this;
        return *this = sprites.at(type);
    }
    virtual void Update(SDL_Event& message) { updateFunc(*this, message); };
};