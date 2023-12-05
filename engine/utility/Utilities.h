#pragma once

#include <chrono>

class Utilities {
public:
    long long currentTime = 1;

    void updateCurrentTime() {
        using namespace std::chrono;
        auto now = high_resolution_clock::now();
        auto timeSinceEpoch = duration_cast<milliseconds>(now.time_since_epoch());
        this->currentTime = timeSinceEpoch.count() / 1000;
    }

};
