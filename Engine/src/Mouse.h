#pragma once
#include "Export.h"
#include "Window.h"

namespace basilisk
{
    class BASILISK_API Mouse
    {
    public:
        explicit Mouse(Window* window);
        void HideCursor();

        //TODO: Center cursor each frame for cam

        glm::vec2 GetOffsetAndReset();

        glm::vec2 LastPos = {0, 0};
        glm::vec2 Offset = {0, 0};
        bool FirstMouse = true;
        float Sensitivity = 0.1f;
        float Fov = 45.0f;
        const float MaxFov = 45.0f;
        const float MinFov = 1.0f;

    private:
        Window* ActiveWindow = nullptr;


    };

} // namespace basilisk
