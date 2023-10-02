#include "Debug.h"
int Debug::m_iteration = 10;
bool Debug::flag = false;

void Debug::FatalError(const char *string) {
    std::cout<<string<<std::endl;
}
