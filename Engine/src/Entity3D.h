#pragma once
#include "Entity.h"

namespace basilisk
{
    class Entity3D : public Entity
    {
        void Init() override;
        void Draw() override;
    };

} // namespace basilisk
