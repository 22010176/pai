#pragma once

#include <functional>

template <typename T1, typename T2> struct Script {
    bool enable = true;
    const std::function<T1(T2)> callback;
};

void SetRunningState(bool val = true);
bool GetRunningState();