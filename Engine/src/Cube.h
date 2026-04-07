#pragma once
#include "Polygon.h"

namespace basilisk
{
    class BASILISK_API Cube : public Polygon
    {
    protected:
        Cube(const glm::vec3& center, const glm::vec3& size, bool isSolidColor, basilisk::Color color);

    private:
        /// <summary>
        /// Initializes the vertices that will be used for drawing the square.
        /// </summary>
        void SetVertices() override;

    };

} // namespace basilisk
