#pragma once
#include "Basilisk/Cube.h"

namespace game
{
    class Box : public basilisk::Cube
    {
    public:
        Box(glm::vec3 center, glm::vec3 size, basilisk::Color color);

        void Update() override;
    };

} // namespace game
