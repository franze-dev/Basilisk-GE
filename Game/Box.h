#pragma once
#include "Basilisk/Square.h"

namespace game
{
    class Box : public basilisk::Square
    {
    public:
        Box(glm::vec2 center, glm::vec2 size, basilisk::Color color);

        void Update() override;
    };

} // namespace game
