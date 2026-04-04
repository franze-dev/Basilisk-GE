#include "Mouse.h"

namespace basilisk
{
    static void OnCursorMove(GLFWwindow* window, double posX, double posY)
    {
        Mouse* mouse = static_cast<Mouse*>(glfwGetWindowUserPointer(window));
        if (mouse)
        {
            if (mouse->FirstMouse)
            {
                mouse->LastPos = {posX, posY};
                mouse->FirstMouse = false;
            }

            mouse->Offset = {(posX - mouse->LastPos.x) * mouse->Sensitivity, (mouse->LastPos.y - posY) * mouse->Sensitivity};
            mouse->LastPos = {posX, posY};
        }
    }

    static void OnCursorScroll(GLFWwindow* window, double xOffset, double yOffset)
    {
        Mouse* mouse = static_cast<Mouse*>(glfwGetWindowUserPointer(window));

        mouse->Fov -= (float)yOffset;

        if (mouse->Fov < mouse->MinFov)
            mouse->Fov = mouse->MinFov;
        else if (mouse->Fov > mouse->MaxFov)
            mouse->Fov = mouse->MaxFov;
    }

    Mouse::Mouse(Window* window)
    {
        ActiveWindow = window;

        glfwSetWindowUserPointer(ActiveWindow->GetWindow(), this);
        glfwSetCursorPosCallback(ActiveWindow->GetWindow(), OnCursorMove);
        glfwSetScrollCallback(ActiveWindow->GetWindow(), OnCursorScroll);
    }

    void Mouse::HideCursor()
    {
        glfwSetInputMode(ActiveWindow->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    glm::vec2 Mouse::GetOffset() const
    {
        return Offset;
    }
} // namespace basilisk
