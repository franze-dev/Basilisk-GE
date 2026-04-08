#include "Entity.h"

#include <spdlog/spdlog.h>

#include "Renderer.h"
#include "glm/gtc/type_ptr.hpp"
#include "Buffers.h"
#include "Log.h"

namespace basilisk
{
    
    Entity::~Entity()
    {
        delete[] this->buffers.Vertices;
        delete[] this->buffers.Indices;
    }

    void Entity::Init()
    {
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

    void Entity::Draw()
    {
        const auto mat = this->GetMaterial();
        auto& renderer = Renderer::GetInstance();

        renderer.UpdateViewMatrix();
        const auto matrix = renderer.GetProjectionMatrix() * renderer.GetViewMatrix() * this->ModelMatrix;
        mat->UpdateGLMatrix(matrix, "matrix");

        renderer.Draw(mat->GetShaderProgram(), buffers.Vao, buffers.AmountIndices);
    }

    void Entity::SetRotation(float angle, const Axis& rotationAxis, const bool isRads)
    {
        if (!isRads)
        {
            angle = glm::radians(angle);
        }

        switch (rotationAxis)
        {
        case Axis::X:
            this->Rotation.x = angle;
            break;
        case Axis::Y:
            this->Rotation.y = angle;
            break;
        default:
            this->Rotation.z = angle;
            break;
        }

        UpdateRotationMatrix();
        UpdateModelMatrix();
    }

    void Entity::SetScaling(const glm::vec3& scaling)
    {
        this->Scaling = scaling;
        this->ScaleMatrix = glm::scale(glm::mat4(1.0f), this->Scaling);
        UpdateModelMatrix();
    }

    void Entity::SetScaling(const float scale, const Axis& scalingAxis)
    {
        switch (scalingAxis)
        {
        case Axis::X:
            this->Scaling.x = scale;
            break;
        case Axis::Y:
            this->Scaling.y = scale;
            break;
        case Axis::Z:
            this->Scaling.z = scale;
            break;

        }

        SetScaling(this->Scaling);
    }

    void Entity::SetPosition(const glm::vec3& newPosition)
    {
        this->Position = newPosition;

        UpdateTranslateMatrix();
        UpdateModelMatrix();
    }

    void Entity::SetMaterial(const std::shared_ptr<Material>& material)
    {
        this->Mat = material;
    }

    glm::vec3 Entity::GetPosition() const
    {
        return this->Position;
    }

    glm::vec3 Entity::GetScale() const
    {
        return this->Scaling;
    }

    glm::vec3 Entity::GetRotation(const bool isRads) const
    {
        if (!isRads)
        {
            return glm::degrees(this->Rotation);
        }
        return this->Rotation;
    }

    std::shared_ptr<Material> Entity::GetMaterial() const
    {
        if (!Mat)
        {
            Log::Get()->error("Material has not being assigned. Must be set before this call");
            abort();
        }
        return Mat;

    }

    glm::mat4 Entity::GetModelMatrix() const
    {
        return this->ModelMatrix;
    }

    void Entity::UpdateBuffers()
    {
        Renderer::GetInstance().GenerateVBs(buffers, this->Mat->GetIsTextured());
    }

    void Entity::FillVertices(float vertices[], const int amountVertices)
    {
        delete[] this->buffers.Vertices;

        this->buffers.Vertices = new float[amountVertices];

        for (int i = 0; i < amountVertices; ++i)
        {
            this->buffers.Vertices[i] = vertices[i];
        }

        this->buffers.AmountVertices = amountVertices;
    }

    void Entity::FillIndices(unsigned int indices[], const int amountIndices)
    {
        delete[] buffers.Indices;

        this->buffers.Indices = new unsigned int[amountIndices];

        for (int i = 0; i < amountIndices; ++i)
        {
            this->buffers.Indices[i] = indices[i];
        }

        this->buffers.AmountIndices = amountIndices;
    }

    void Entity::UpdateRotationMatrix()
    {
        this->RotationMatrix = glm::mat4(1.0f);

        this->RotationMatrix = glm::rotate(this->RotationMatrix, this->Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

        this->RotationMatrix = glm::rotate(this->RotationMatrix, this->Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

        this->RotationMatrix = glm::rotate(this->RotationMatrix, this->Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void Entity::UpdateTranslateMatrix()
    {
        this->TranslateMatrix = glm::translate(glm::mat4(1.0f), this->Position);
    }

    void Entity::UpdateModelMatrix()
    {
        this->ModelMatrix = this->TranslateMatrix * this->RotationMatrix * this->ScaleMatrix;
    }
} // namespace basilisk
