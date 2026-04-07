#pragma once
#include "Entity3D.h"
#include "Colors.h"

namespace basilisk
{
    class BASILISK_API Polygon : public Entity3D
    {
    public:
        virtual ~Polygon() = default;

    protected:
        explicit Polygon(const basilisk::Color& color, bool isSolid);

        /// <summary>
        /// Initializes the vertices that will be used for drawing.
        /// </summary>
        virtual void SetVertices() = 0;
        bool IsSolid;
    };

} // namespace basilisk
