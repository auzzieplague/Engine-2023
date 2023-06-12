#include <gtest/gtest.h>
#include "../engine/Engine.h"

TEST(engine, transforms) {
    Component component {};
    glm::vec3 wPos = component.getWorldPosition();
    glm::vec3 ePos = component.getWorldPosition();
    ASSERT_EQ(wPos,ePos) << "Vectors x and y are of unequal length";
}
