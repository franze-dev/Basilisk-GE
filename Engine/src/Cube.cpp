#include "Cube.h"

namespace basilisk
{
    Cube::Cube(const glm::vec3& center, const glm::vec3& size, bool isSolidColor, basilisk::Color color) : Polygon(color, isSolidColor)
    {
        this->SetPosition(center);
        this->SetScaling(size);

        Cube::SetVertices();

        unsigned int indices[]{
            //FACE FRONT
            0, 1, 3, // first triangle
            1, 2, 3, // second triangle
            //FACE BACK
            4, 5, 7, // first triangle
            5, 6, 7, // second triangle
            //FACE LEFT
            8, 9, 11, // first triangle
            9, 10, 11, // second triangle
            //FACE RIGHT
            12, 13, 15, // first triangle
            13, 14, 15, // second triangle
            //FACE BOTTOM
            16, 17, 19, // first triangle
            17, 18, 19, // second triangle
            //FACE TOP
            20, 21, 23, // first triangle
            21, 22, 23, // second triangle
        };

        this->FillIndices(indices, sizeof(indices));
    }


    void Cube::SetVertices()
    {
        constexpr int amountFaces = 6;
        constexpr int amountVert = 4;
        constexpr int amountDim = 3;
        std::array<float, amountFaces * amountVert*(amountDim + Color::ColorParamsAmount)> vertices;

        Color::Normalize color = Color::Normalize({255, 0, 0, 1});

        if (this->IsSolid)
            color = Color::Normalize(this->Color);

        //@formatter:off
        vertices = {
            // FACE FRONT
            0.5f, 0.5f, 0.5f, color.R, color.G, color.B, color.A, // top right
            0.5f, -0.5f, 0.5f, color.R, color.G, color.B, color.A, // bottom right
            -0.5f, -0.5f, 0.5f, color.R, color.G, color.B, color.A, // bottom left
            -0.5f, 0.5f, 0.5f, color.R, color.G, color.B, color.A, // top left
            // FACE BACK
            0.5f, 0.5f, -0.5f, color.R, color.G, color.B, color.A, // top right
            0.5f, -0.5f, -0.5f, color.R, color.G, color.B, color.A, // bottom right
            -0.5f, -0.5f, -0.5f, color.R, color.G, color.B, color.A, // bottom left
            -0.5f, 0.5f, -0.5f, color.R, color.G, color.B, color.A, // top left
            // FACE LEFT
            -0.5f, 0.5f, -0.5f, color.R, color.G, color.B, color.A, // top right
            -0.5f, -0.5f, -0.5f, color.R, color.G, color.B, color.A, // bottom right
            -0.5f, -0.5f, 0.5f, color.R, color.G, color.B, color.A, // bottom left
            -0.5f, 0.5f, 0.5f, color.R, color.G, color.B, color.A, // top left
            // FACE RIGHT
            0.5f, 0.5f, -0.5f, color.R, color.G, color.B, color.A, // top right
            0.5f, -0.5f, -0.5f, color.R, color.G, color.B, color.A, // bottom right
            0.5f, -0.5f, 0.5f, color.R, color.G, color.B, color.A, // bottom left
            0.5f, 0.5f, 0.5f, color.R, color.G, color.B, color.A, // top left
            // FACE BOTTOM
            0.5f, -0.5f, -0.5f, color.R, color.G, color.B, color.A, // top right
            0.5f, -0.5f, 0.5f, color.R, color.G, color.B, color.A, // bottom right
            -0.5f, -0.5f, 0.5f, color.R, color.G, color.B, color.A, // bottom left
            -0.5f, -0.5f, -0.5f, color.R, color.G, color.B, color.A, // top left
            // FACE TOP
            0.5f, 0.5f, -0.5f, color.R, color.G, color.B, color.A, // top right
            0.5f, 0.5f, 0.5f, color.R, color.G, color.B, color.A, // bottom right
            -0.5f, 0.5f, 0.5f, color.R, color.G, color.B, color.A, // bottom left
            -0.5f, 0.5f, -0.5f, color.R, color.G, color.B, color.A // top left
        };
        //@formatter:on

        this->FillVertices(vertices.data(), sizeof(vertices));
    }
} // namespace basilisk
