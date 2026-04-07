#include "Polygon.h"

namespace basilisk
{
    Polygon::Polygon(const basilisk::Color& color, bool isSolid) : 
        IsSolid(IsSolid)
    {
        this->Color = color;
    }
} // namespace basilisk
