#include "Box.h"

namespace game
{
    Box::Box(glm::vec3 center, glm::vec3 size, basilisk::Color color) : 
        Cube(center, size, true, color)
    {
    }

    void Box::Update()
    {
    }

} // namespace game
