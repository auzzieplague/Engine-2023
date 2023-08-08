#pragma once

#include <iostream>


class Debug {
private:
    static int m_iteration;
public:
    static bool flag;

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

    static void throwFileNotFound(const std::string& fileName) {
        throw std::runtime_error("Missing file "+fileName);
    }

    static void throwMissingItem( const std::string& item,const std::string& context ) {
        throw std::runtime_error("expecting item"+item+" in "+context);
    }
};

