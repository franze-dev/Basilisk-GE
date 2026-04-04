#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>

namespace basilisk
{
    Camera::Camera(Mouse& mouse, Input& inputSystem) : InputSystem(&inputSystem)
    {
        this->ActiveMouse = &mouse;
    }

    Camera::~Camera()
    {
    }

    Camera::Camera(const Camera& other) : InputSystem(other.InputSystem)
    {
        this->ActiveMouse = other.ActiveMouse;
        this->CamData = other.CamData;
        this->Target = other.Target;
        this->MoveFwIA = other.MoveFwIA;
        this->MoveBwIA = other.MoveBwIA;
        this->MoveLeftIA = other.MoveLeftIA;
        this->MoveRightIA = other.MoveRightIA;
    }

    Camera::Camera(Camera&& other) noexcept : InputSystem(other.InputSystem)
    {
        this->ActiveMouse = other.ActiveMouse;
        this->CamData = other.CamData;
        this->Target = other.Target;
        this->MoveFwIA = other.MoveFwIA;
        this->MoveBwIA = other.MoveBwIA;
        this->MoveLeftIA = other.MoveLeftIA;
        this->MoveRightIA = other.MoveRightIA;

        other.InputSystem = nullptr;
        other.ActiveMouse = nullptr;
        other.CamData = CameraData();
        other.Target = TargetData();
        other.MoveFwIA = nullptr;
        other.MoveBwIA = nullptr;
        other.MoveLeftIA = nullptr;
        other.MoveRightIA = nullptr;
    }

    Camera& Camera::operator=(const Camera& other)
    {
        if (this != &other)
        {
            this->ActiveMouse = other.ActiveMouse;
            this->CamData = other.CamData;
            this->Target = other.Target;
            this->MoveFwIA = other.MoveFwIA;
            this->MoveBwIA = other.MoveBwIA;
            this->MoveLeftIA = other.MoveLeftIA;
            this->MoveRightIA = other.MoveRightIA;
        }

        return *this;
    }

    Camera& Camera::operator=(Camera&& other) noexcept
    {
        if (this != &other)
        {
            this->ActiveMouse = other.ActiveMouse;
            this->CamData = other.CamData;
            this->Target = other.Target;
            this->MoveFwIA = other.MoveFwIA;
            this->MoveBwIA = other.MoveBwIA;
            this->MoveLeftIA = other.MoveLeftIA;
            this->MoveRightIA = other.MoveRightIA;

            other.InputSystem = nullptr;
            other.ActiveMouse = nullptr;
            other.CamData = CameraData();
            other.Target = TargetData();
            other.MoveFwIA = nullptr;
            other.MoveBwIA = nullptr;
            other.MoveLeftIA = nullptr;
            other.MoveRightIA = nullptr;
        }

        return *this;
    }

    void Camera::Init()
    {
        this->Target.Ptr = nullptr;
        this->MoveFwIA = &this->InputSystem->NewInput(basilisk::Keys::W);
        this->MoveLeftIA = &this->InputSystem->NewInput(basilisk::Keys::A);
        this->MoveBwIA = &this->InputSystem->NewInput(basilisk::Keys::S);
        this->MoveRightIA = &this->InputSystem->NewInput(basilisk::Keys::D);
    }

    void Camera::Update(float deltaTime)
    {
        Move(deltaTime);
        Look();
    }

    glm::mat4 Camera::GetUpdatedViewMatrix() const
    {
        if (CamData.Mode == CameraMode::ThirdPerson && Target.Ptr != nullptr)
        {
            return glm::lookAt(this->CamData.Pos, Target.Ptr->GetPosition() + CamData.EntityOffset, CamData.Up);
        }

        return glm::lookAt(CamData.Pos, CamData.Pos + CamData.Front, CamData.Up);
    }

    void Camera::Look()
    {
        glm::vec2 offset = ActiveMouse->GetOffset();

        this->CamData.Yaw += offset.x;
        this->CamData.Pitch += offset.y;

        this->CamData.Pitch = std::clamp(this->CamData.Pitch, this->CamData.MinPitch, this->CamData.MaxPitch);

        glm::vec3 direction;

        direction.x = cos(glm::radians(this->CamData.Yaw)) * cos(glm::radians(this->CamData.Pitch));
        direction.y = sin(glm::radians(this->CamData.Pitch));
        direction.z = sin(glm::radians(this->CamData.Yaw)) * cos(glm::radians(this->CamData.Pitch));

        this->CamData.Front = glm::normalize(direction);

        glm::vec3 worldUp = {0.0f, 1.0f, 0.0f};

        this->CamData.Right = glm::normalize(glm::cross(worldUp, CamData.Front));
        this->CamData.Up = glm::cross(CamData.Front, CamData.Right);
    }

    void Camera::Move(float deltaTime)
    {
        float speed = CamData.Speed * deltaTime;

        if (Target.Ptr == nullptr)
            CamData.Mode = CameraMode::FirstPerson;

        switch (CamData.Mode)
        {
        case CameraMode::FirstPerson:
            if (MoveFwIA->IsDown())
                CamData.Pos += CamData.Front * speed;
            if (MoveBwIA->IsDown())
                CamData.Pos -= CamData.Front * speed;
            if (MoveLeftIA->IsDown())
                CamData.Pos -= CamData.Right * speed;
            if (MoveRightIA->IsDown())
                CamData.Pos += CamData.Right * speed;
            break;
        case CameraMode::FirstFollowPerson:
            CamData.Pos = this->Target.Ptr->GetPosition() + CamData.EntityOffset;
            break;
        case CameraMode::ThirdPerson:
            glm::vec3 focusPoint = this->Target.Ptr->GetPosition() + CamData.EntityOffset;
            CamData.Pos = focusPoint - (CamData.Front * CamData.ThirdPersonDistance);
            break;
        default:
            break;
        }
    }

    void Camera::SetEntity(Entity* entity, glm::vec3 offset, bool isFirstPerson)
    {
        this->CamData.Mode = isFirstPerson ? CameraMode::FirstFollowPerson : CameraMode::ThirdPerson;
        this->Target.Ptr = entity;
        this->CamData.EntityOffset = offset;
    }

    void Camera::SwitchToFirstFollowPerson(glm::vec3 offset)
    {
        SwitchToMode(CameraMode::FirstFollowPerson, offset);
    }

    void Camera::SwitchToThirdPerson(glm::vec3 offset)
    {
        SwitchToMode(CameraMode::ThirdPerson, offset);
    }

    void Camera::SwitchToFirstPerson()
    {
        this->Target.Ptr = nullptr;
        this->CamData.EntityOffset = {0, 0, 0};
        this->CamData.Mode = CameraMode::FirstPerson;
    }

    void Camera::SwitchToMode(CameraMode mode, glm::vec3 offset)
    {
        if (this->Target.Ptr == nullptr)
            return;

        this->CamData.EntityOffset = offset;
        this->CamData.Mode = CameraMode::ThirdPerson;
    }

} // namespace basilisk
