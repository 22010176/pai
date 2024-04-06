#pragma once


template <typename T> class Observer {
private:
    inline static int idSeed = 0;
    int id;
public:
    Observer() : id(++idSeed) {}

    virtual void Update(T& message) = 0;
    int GetId() const { return id; }
};
