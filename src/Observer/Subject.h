#pragma once

#include <vector>

#include "Observer.h"

template <typename T> class ObserverSubject {
protected:
    std::vector<Observer<T>> observers{};
public:
    ObserverSubject() {}
    ~ObserverSubject() {}
    void Attach(Observer<T>& observer) { this->observers.push_back(observer); }
    void Detach(int id) {
        for (size_t i = 0; i < this->observers.size(); ++i)
            if (observers[i].GetId() == id) observers.erase(observers.begin() + i);
    }
    void Notify(T& type) {
        for (Observer<T>& obs : this->observers) obs.Update(type);
    }
};
