#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Export.h"

namespace basilisk
{
    /// <summary>
    /// A class for creating and managing the window.
    /// </summary>
    class BASILISK_API Window
    {
    public:

        Window() = default;
        Window(const char* windowName, const glm::ivec2& size);

        /// <summary>
        /// Getter for the window pointer
        /// </summary>
        /// <returns>The window pointer</returns>
        [[nodiscard]] GLFWwindow* GetWindow() const;
        /// <summary>
        /// Checks if the window should close given the current conditions.
        /// </summary>
        /// <returns>True if it should close, false if it should not</returns>
        [[nodiscard]] bool WindowShouldClose() const;
        /// <summary>
        /// Getter for the size of the window
        /// </summary>
        /// <returns>The size of the window (x = width, y = height)</returns>
        [[nodiscard]] glm::ivec2 GetSize() const;
    
    private:
        GLFWwindow* WindowP = nullptr;
        glm::ivec2 Size = glm::ivec2{0, 0};
    };
} // basilisk 
