#pragma once
#include "Entity.h"

namespace basilisk
{
    class BASILISK_API Entity3D : public Entity
    {
    public:
        void Init() override;
        void Draw() override;
    };

} // namespace basilisk
