#include "Mouse.h"

namespace basilisk
{
    static void OnCursorMove(GLFWwindow* window, double posX, double posY)
    {
        Mouse* mouse = static_cast<Mouse*>(glfwGetWindowUserPointer(window));
        if (!mouse)
            return;

        if (!mouse->MoveDetection)
        {
            mouse->MoveDetection = true;
            mouse->LastPos = {posX, posY};
            mouse->Offset = {0.0f, 0.0f};
            return;
        }

        if (mouse->FirstMouse)
        {
            mouse->LastPos = {posX, posY};
            mouse->FirstMouse = false;
        }

        mouse->Offset = {(posX - mouse->LastPos.x) * mouse->Sensitivity, (mouse->LastPos.y - posY) * mouse->Sensitivity};

        mouse->LastPos = {posX, posY};

        mouse->CenterCursor();
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

        CenterCursor();

        FirstMouse = true;
    }

    void Mouse::SetCenteredCursor(bool isCentered)
    {
        IsCentered = isCentered;
    }

    glm::vec2 Mouse::GetOffsetAndReset()
    {
        glm::vec2 temp = Offset;
        Offset = glm::vec2(0.0f, 0.0f);
        return temp;
    }

    void Mouse::CenterCursor()
    {
        if (!IsCentered)
            return;

        MoveDetection = false;

        int width;
        int height;

        glfwGetWindowSize(ActiveWindow->GetWindow(), &width, &height);

        glfwSetCursorPos(ActiveWindow->GetWindow(), width / 2.0f, height / 2.0f);
    }
} // namespace basilisk
