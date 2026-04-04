#include "Box.h"

namespace game
{
    Box::Box(glm::vec2 center, glm::vec2 size, basilisk::Color color) : 
        Square(center, size, true, color)
    {
    }

    void Box::Update()
    {
    }

} // namespace game
