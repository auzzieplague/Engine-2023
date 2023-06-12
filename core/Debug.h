#pragma once

#include <iostream>


class Debug {
private:
    static int m_iteration;
public:
    template<typename T>
    static void show(T value) {
        std::cout << value << std::endl;
    }

    static void nextIteration() {
        m_iteration++;
    };

    static void setIteration(int iteration) {
        m_iteration = iteration;
    };

    static int getIteration() {
        return m_iteration;
    }

    static void resetIteration() {
        m_iteration = 0;
    };

};

