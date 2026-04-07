#include "Shape.h"

namespace basilisk
{
    Shape::Shape(const basilisk::Color& color, const bool isSolid) : 
        IsSolid(isSolid)
    {
        this->Color = color;
    }
} // namespace basilisk
