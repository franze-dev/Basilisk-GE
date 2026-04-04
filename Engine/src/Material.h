#pragma once

#include <memory>
#include <string>

#include "Export.h"
#include "Colors.h"
#include "glm/glm.hpp"

namespace basilisk
{
    using SPProc = unsigned int;
    using ShaderProc = unsigned int;

    /// <summary>
    /// This class is in charged of shaders building and compilation.
    /// </summary>
    class BASILISK_API Material
    {
    public:
        /// <summary>
        /// Constructor for material. It is not recommended to use this function, but use New().
        /// </summary>
        /// <param name="isTextured">If the color is supplied by the vertices or if it is supplied by the program (solid color).</param>
        /// <param name="hasFilter">If it has a color filter on top. Use OverrideColorFilter to set the color.</param>
        explicit Material(bool isTextured, bool hasFilter);

        /// <summary>
        /// Constructs materials and returns a shared pointer with the material.
        /// </summary>
        /// <param name="isTextured">If the color is supplied by the vertices or if it is supplied by the program (solid color).</param>
        /// <returns>Shared pointer with new Material</returns>
        static std::shared_ptr<Material> New(bool isTextured, bool hasFilter = false);

        /// <summary>
        /// Sets a color as a filter.
        /// </summary>
        /// <param name="color"></param>
        void OverrideColorFilter(const Color& color) const;

        /// <summary>
        /// Builds and compiles shaders.
        /// </summary>
        void BuildShader();

        /// <summary>
        /// Getter for Shader Program.
        /// </summary>
        /// <returns>Shader Program index.</returns>
        [[nodiscard]] SPProc GetShaderProgram() const;

        /// <summary>
        /// Getter for IsTextured Flag
        /// </summary>
        /// <returns>If the material is set with a texture</returns>
        [[nodiscard]] bool GetIsTextured() const;

        /// <summary>
        /// Sends a matrix to OpenGl.
        /// </summary>
        /// <param name="matrix">Matrix to send to OpenGl.</param>
        /// <param name="name">Name of Matrix in Shader source</param>
        void UpdateGLMatrix(const glm::mat4& matrix, const std::string& name) const;

        /// <summary>
        /// Has the projection matrix been sent.
        /// </summary>
        bool IsProjectionSent = false;

        /// <summary>
        /// Has the view matrix been sent.
        /// </summary>
        bool IsViewSent = false;
        
        bool IsMaterialBuilt();

    private:
        [[noreturn]] static void ShaderCompileError(const ShaderProc& shader);
        [[noreturn]] static void ProgramCompileError(const SPProc& program);
        bool IsMatBuilt = false;
        bool IsTextured;
        bool HasFilter;
        SPProc ShaderProgram = 0;
        static const char* VertexShader;
        static const char* FragShader;
        static const char* FilterFragShader;
        static const char* FragShaderTextureless;
    };
} // namespace basilisk 
