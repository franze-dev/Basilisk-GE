#pragma once
#include "Colors.h"
#include "Entity.h"
#include "CollisionManager.h"

namespace basilisk
{

    /// <summary>
    /// 2D entity, all 2d entities must inherit from this class.
    /// </summary>
    class BASILISK_API Entity2D : public Entity
    {
    public:
        /// <summary>
        /// Getter for rotation angle.
        /// </summary>
        /// <returns>Returns angle with X axis. Clockwise is positive.</returns>
        [[nodiscard]] float GetRotation2D(bool isRads = false) const;

        /// <summary>
        /// Getter for scale vector
        /// </summary>
        /// <returns>Returns 2D scale vector.</returns>
        [[nodiscard]] glm::vec2 GetScale2D() const;

        /// <summary>
        /// Getter for position vector
        /// </summary>
        /// <returns>Returns 2d position vector.</returns>
        [[nodiscard]] glm::vec2 GetPosition2D() const;

        /// <summary>
        /// Setter for rotation angle.
        /// </summary>
        /// <param name="angle">Angle to rotate entity. Clockwise is negative.</param>
        /// <param name="isRads">True if is in radians, false if is in degrees</param>
        virtual void SetRotation(float angle, bool isRads = false);
        /// <summary>
        /// Setter for scale vector.
        /// </summary>
        /// <param name="scaling">Scaling vector.</param>
        virtual void SetScaling(const glm::vec2& scaling);
        /// <summary>
        /// Setter for position vector.
        /// </summary>
        /// <param name="newPosition">Position vector</param>
        virtual void SetPosition(const glm::vec2& newPosition);

        void CollideAndMove(const CollisionManager::CollisionData& data, glm::vec2 newPos);
    protected:
        Entity2D() = default;
        virtual ~Entity2D() = default;

        
    private:
        // These functions are private to make 2D entities use 2D corresponding functions
        [[nodiscard]] glm::vec3 GetPosition() const override;
        [[nodiscard]] glm::vec3 GetScale() const override;
        [[nodiscard]] glm::vec3 GetRotation(bool isRads = false) const override;
    };
} // namespace basilisk
