#pragma once
#include "Entity.h"
#include "Input.h"
#include "InputAction.h"
#include "Mouse.h"

namespace basilisk
{
    /// <summary>
    /// A versatile camera that can switch between third person, fly mode or first person.
    /// </summary>
    class BASILISK_API Camera
    {
    public:
        explicit Camera(Mouse& mouse, Input& inputSystem);
        ~Camera();

        /// <summary>
        /// Copy constructor
        /// </summary>
        /// <param name="other">Other BaseGame to copy from</param>
        Camera(const Camera& other);

        /// <summary>
        /// Move Constructor
        /// </summary>
        /// <param name="other">Other BaseGame to move from</param>
        Camera(Camera&& other) noexcept;

        /// <summary>
        /// Copy Assignment
        /// </summary>
        /// <param name="other">Other BaseGame to copy from</param>
        /// <returns>Copied BaseGame</returns>
        Camera& operator=(const Camera& other);

        /// <summary>
        /// Move assignment
        /// </summary>
        /// <param name="other">Other BaseGame to from</param>
        /// <returns>Moved BaseGame</returns>
        Camera& operator=(Camera&& other) noexcept; // move assignment

        /// <summary>
        /// Initializes the camera. Renderer does this call on it's own when you give it the camera reference.
        /// </summary>
        void Init();
        /// <summary>
        /// Updates the camera. It's already called on Renderer.
        /// </summary>
        void Update(float deltaTime);

        /// <summary>
        /// Gets the camera view matrix. Don't use this unless you know what you're doing. It's already used on Renderer.
        /// </summary>
        /// <returns></returns>
        glm::mat4 GetUpdatedViewMatrix() const;

        /// <summary>
        /// Sets an entity as the camera target and accepts an offset.
        /// For first person, the entity position becomes the camera position, so the offset is how far from that point the camera moves
        /// from the entity when following it. For third person, the entity position becomes the camera target, so it can orbit around it.
        /// The offset is how far from the position that targer moves. This is useful if you want the camera to point at the "head" or the
        /// "shoulder" instead of the perfect center of the entity. The camera won't try to delete the entity, it'll remove the reference to
        /// it on destruction.
        /// </summary>
        /// <param name="entity">Entity to follow. If 'nullptr' is provided and it was previously
        /// following an entity, it becomes fly mode</param>
        /// <param name="offset">Offset to move from the entity when following it. Useful for
        /// targetting the "head" or the "shoulder" instead of the very center of an entity.</param>
        void SetEntity(Entity* entity, glm::vec3 offset, bool isFirstPerson);

        /// <summary>
        /// Switches from third to first person without re-entering an entity. If an entity wasn't provided, this does nothing.
        /// </summary>
        /// <param name="offset"></param>
        void SwitchToFirstFollowPerson(glm::vec3 offset);

        /// <summary>
        /// Switches from first to third person without re-entering an entity. If an entity wasn't provided, this does nothing.
        /// </summary>
        /// <param name="offset"></param>
        void SwitchToThirdPerson(glm::vec3 offset = glm::vec3(0, 0, 0));

        /// <summary>
        /// Switches to fly mode. It automatically removes the reference to the previously provided entity.
        /// </summary>
        void SwitchToFirstPerson();

    private:
        enum class CameraMode
        {
            FirstPerson,
            FirstFollowPerson,
            ThirdPerson
        };

        struct CameraData
        {
            CameraData() = default;
            glm::vec3 Pos = {0, 0, 100};
            glm::vec3 Up = {0, 1, 0};
            glm::vec3 Right = {1, 0, 0};
            glm::vec3 Front = {0, 0, -1};
            float Speed = 40.0f;
            float Yaw = -89.0f;
            float Pitch = 0.0f;
            float Roll = 0.0f;
            float MaxPitch = 89.0f;
            float MinPitch = -89.0f;
            float ThirdPersonDistance = 50;
            CameraMode Mode = CameraMode::FirstPerson;
            glm::vec3 EntityOffset = {0.0f, 0.0f, 0.0f};
        };

        struct TargetData
        {
            TargetData() = default;
            Entity* Ptr = nullptr;
            glm::vec3 Pos = {0.0f, 0.0f, 0.0f};
        };

        void SwitchToMode(CameraMode mode, glm::vec3 offset);
        void Look();
        void Move(float deltaTime);

        CameraData CamData;

        TargetData Target;

        Mouse* ActiveMouse;

        Input* InputSystem;

        InputAction* MoveFwIA = nullptr;
        InputAction* MoveBwIA = nullptr;
        InputAction* MoveLeftIA = nullptr;
        InputAction* MoveRightIA = nullptr;
    };

} // namespace basilisk
