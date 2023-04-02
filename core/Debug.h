#pragma once
#include <iostream>

class Debug {
public:
    template<typename T>
    static void show(T value) {
        std::cout << value << std::endl;
    }
};
