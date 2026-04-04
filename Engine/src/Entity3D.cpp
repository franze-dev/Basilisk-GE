#include "Entity3D.h"
#include "Renderer.h"

namespace basilisk
{
    void Entity3D::Init()
    {
        //TODO: fix copy pasting here
        const auto mat = this->GetMaterial();
        this->UpdateBuffers();

        if (!mat->IsMaterialBuilt())
            mat->BuildShader();

        if (!mat->IsProjectionSent)
        {
            Renderer::GetInstance().LoadProjectionMatrix();
            mat->IsProjectionSent = true;
        }
    }

    void Entity3D::Draw()
    {
        // TODO: fix copy pasting here
        const auto mat = this->GetMaterial();
        auto& renderer = Renderer::GetInstance();

        renderer.UpdateViewMatrix();
        const auto matrix = renderer.GetProjectionMatrix() * renderer.GetViewMatrix() * this->ModelMatrix;
        mat->UpdateGLMatrix(matrix, "matrix");

        renderer.Draw(mat->GetShaderProgram(), buffers.Vao, buffers.AmountIndices);
    }
} // namespace basilisk
