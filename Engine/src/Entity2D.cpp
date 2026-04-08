#include "Entity2D.h"

#include "Entity.h"
#include "Renderer.h"

namespace basilisk
{
    float Entity2D::GetRotation2D(const bool isRads) const
    {
        return GetRotation(isRads).z;
    }

    glm::vec2 Entity2D::GetScale2D() const
    {
        return GetScale();
    }

    glm::vec2 Entity2D::GetPosition2D() const
    {
        return GetPosition();
    }

    void Entity2D::SetRotation(const float angle, const bool isRads)
    {
        this->Entity::SetRotation(angle, Axis::Z, isRads);
    }

    void Entity2D::SetScaling(const glm::vec2& scaling)
    {
        this->Entity::SetScaling({scaling.x, scaling.y, 1.0f});
    }

    void Entity2D::SetPosition(const glm::vec2& newPosition)
    {
        this->PreviousPos = this->GetPosition2D();
        this->Entity::SetPosition({newPosition.x, newPosition.y, 0.0f});
    }

    glm::vec3 Entity2D::GetPosition() const
    {
        return Entity::GetPosition();
    }

    glm::vec3 Entity2D::GetScale() const
    {
        return Entity::GetScale();
    }

    glm::vec3 Entity2D::GetRotation(const bool isRads) const
    {
        return Entity::GetRotation(isRads);
    }

    void Entity2D::CollideAndMove(const CollisionManager::CollisionData& data, glm::vec2 newPos)
    {
        if (data.HorizontalDir != CollisionManager::CollisionDir::NONE)
            newPos.x = this->PreviousPos.x;

        if (data.VerticalDir != CollisionManager::CollisionDir::NONE)
            newPos.y = this->PreviousPos.y;

        this->SetPosition(newPos);
    }

} // namespace basilisk
