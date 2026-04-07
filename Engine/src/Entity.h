#pragma once

#include <spdlog/spdlog.h>

#include "Export.h"
#include "Material.h"
#include "glm/glm.hpp"
#include "Buffers.h"

namespace basilisk
{
    enum class Axis : char
    {
        X,
        Y,
        Z
    };

    /// <summary>
    /// Represents an entity within the engine. All entities should inherit from this class.
    /// </summary>
    class BASILISK_API Entity
    {
    public:
        Entity() = default;
        virtual ~Entity();
        
#pragma region Abstracts
        /// <summary>
        /// Initializes the entity. Should be called inside an implemented Init call from base game.
        /// </summary>
        virtual void Init() = 0;

        /// <summary>
        /// Updates the entity. Should be called inside an implemented Update call from base game.
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// Draws the entity. Should be called inside an implemented Draw call from base game.
        /// </summary>
        virtual void Draw() = 0;
        
#pragma endregion

#pragma region Setters
        /// <summary>
        /// Sets and rotates an entity.
        /// </summary>
        /// <param name="angle">Angle to rotate the entity, clockwise</param>
        /// <param name="rotationAxis">Axis to which rotate</param> 
        /// <param name="isRads">True if angle is in radians, false if in degrees</param>
        void SetRotation(float angle, const Axis& rotationAxis, bool isRads);

        /// <summary>
        /// Sets scale vector and scales accordingly.
        /// </summary>
        /// <param name="scaling">Saling Vector</param>
        void SetScaling(const glm::vec3& scaling);

        /// <summary>
        /// Scales in a particular axis and updates the scaling vector.
        /// </summary>
        /// <param name="scale">New size in a particular axis.</param>
        /// <param name="scalingAxis">Axis to which scale</param>
        void SetScaling(float scale, const Axis& scalingAxis);

        /// <summary>
        /// Moves entity to a particular position.
        /// </summary>
        /// <param name="newPosition">Position to which to move entity</param>
        void SetPosition(const glm::vec3& newPosition);


        /// <summary>
        /// Links a material to this entity
        /// </summary>
        /// <param name="material">Shared_ptr of material to link</param>
        void SetMaterial(const std::shared_ptr<Material>& material);

#pragma endregion

#pragma region Getters
        /// <summary>
        /// Getter for the position vector.
        /// </summary>
        /// <returns>Position vector</returns>
        [[nodiscard]] virtual glm::vec3 GetPosition() const;

        /// <summary>
        /// Getter for the position vector.
        /// </summary>
        /// <returns>Position vector</returns>
        [[nodiscard]] virtual glm::vec3 GetScale() const;

        /// <summary>
        /// Getter for the Rotation vector.
        /// </summary>
        /// <returns>Rotation vector</returns>
        [[nodiscard]] virtual glm::vec3 GetRotation(bool isRads = false) const;

        /// <summary>
        /// Returns a Shared pointer to a material object
        /// </summary>
        /// <returns>Shared pointer to a Material object</returns>
        [[nodiscard]] std::shared_ptr<Material> GetMaterial() const;

        /// <summary>
        /// Gets a matrix with the model.
        /// </summary>
        /// <returns>Matrix model</returns>
        [[nodiscard]] glm::mat4 GetModelMatrix() const;
        
#pragma endregion
        
        bool IsActive = true;

    protected:
        /// <summary>
        /// Regenerates buffers with data
        /// </summary>
        void UpdateBuffers();

        /// <summary>
        /// Generates an array of fixed size in runtime for vertices.
        /// </summary>
        /// <param name="vertices">Array with vertices</param>
        /// <param name="amountVertices">Amount of vertices</param>
        void FillVertices(float vertices[], int amountVertices);

        /// <summary>
        /// Generates an array of fixed size in runtime for indices.
        /// </summary>
        /// <param name="indices">Array with indices</param>
        /// <param name="amountIndices">Amount of indices</param>
        void FillIndices(unsigned int indices[], int amountIndices);
        
        glm::mat4 ModelMatrix = glm::mat4(1.0f);

        glm::mat4 TranslateMatrix = glm::mat4(1.0f);
        glm::mat4 ScaleMatrix = glm::mat4(1.0f);
        glm::mat4 RotationMatrix = glm::mat4(1.0f);
        Buffers buffers;

        Color Color = Color::Red;
        glm::vec2 PreviousPos = {0.0f, 0.0f};

    private:
        void UpdateRotationMatrix();
        void UpdateTranslateMatrix();
        
        void UpdateModelMatrix();
        
        std::shared_ptr<Material> Mat = nullptr;

        glm::vec3 Position = {0, 0, 0};
        glm::vec3 Scaling = {1, 1, 1};
        glm::vec3 Rotation = {0, 0, 0};
    };
} // basilisk 
