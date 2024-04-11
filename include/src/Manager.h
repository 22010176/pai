#pragma once

#include <map>
#include <string>
#include <vector>

template <class T1, class T2>
class Manager {
protected:
    std::map<T1, T2> pools{};

public:
    Manager() {}
    ~Manager() {}

    void AddItem(T1 key, T2 value) { pools.insert({ key,value }); }
    T2& GetItem(T1 key) { return pools.at(key); }
    bool HasItem(T1 key) const { return pools.find(key) != pools.end(); }
    void EraseItem(T1 key) { this->pools.erase(key); }

    std::vector<T2> GetItems() {
        std::vector<T2> res{};
        for (const auto& [key, value] : pools) res.push_back(value);
        return res;
    }
    std::vector<T1> GetKeys() {
        std::vector<T1> res{};
        for (const auto& [key, value] : pools) res.push_back(key);
        return res;
    }

    void Clear() { pools.clear(); }
};