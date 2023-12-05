#include "Debug.h"
int Debug::m_iteration = 10;
bool Debug::stopOnError = false;
bool Debug::showDebugMessages = true;

void Debug::FatalError(const char *string) {
    std::cout<<string<<std::endl;
}