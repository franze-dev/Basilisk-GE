#pragma once

#include "Buffers.h"
#include "Camera.h"
#include "Export.h"
#include "glm/glm.hpp"

namespace basilisk
{
    class Window;
    class Color;

    using ShaderProc = unsigned int;
    using SPProc = unsigned int;

    /// <summary>
    /// Singleton that is in charge to make the calls to OpenGl for drawing and rendering.
    /// </summary>
    class BASILISK_API Renderer
    {
    public:
#pragma region Loading
        void SetDimensions(const bool is2D);
        /// <summary>
        /// Initializes GLFW.
        /// </summary>
        void InitGLFW();

        /// <summary>
        /// Sets upp which version of OpenGl we are using through hints.
        /// </summary>
        void SetGlVersion();

        /// <summary>
        /// Initializes GLEW.
        /// </summary>
        void InitGL(const bool is2D = false);

        /// <summary>
        /// Loads an orthogonal projection matrix. Should be called once.
        /// </summary>
        void LoadProjectionMatrix();

        /// <summary>
        /// Binds and fills the VBO.
        /// </summary>
        /// <param name="VboID">Id of buffer to fill and bind</param>
        /// <param name="sizeArray">Size of array to fill buffer with</param>
        /// <param name="array">Array of data</param>
        static void BindAndFillVbo(const unsigned int VboID, const int sizeArray, const float array[]);

        /// <summary>
        /// Binds and fills the EBO.
        /// </summary>
        /// <param name="EboID">Id of buffer to fill and bind</param>
        /// <param name="sizeArray">Size of array to fill buffer with</param>
        /// <param name="array">Array of data</param>
        static void BindAndFillEbo(const unsigned int EboId, const int sizeArray, const unsigned int array[]);

        /// <summary>
        /// Sets attribute pointer.
        /// </summary>
        /// <param name="index">Index of value to set</param>
        /// <param name="size">Amount of vertices per value</param>
        /// <param name="strideAmount">Size of stride</param>
        /// <param name="start">Start of value</param>
        static void SetAttribPointer(const int index, const int size, const int strideAmount, const int start);

        void BindBufferDataUV(
            const unsigned int vbo, const int amountVertices, float* arrayData, const int verticesBefore, const int sizeDataInVbo);

#pragma endregion

#pragma region Drawing
        /// <summary>
        /// Generates vertex array object, vertex buffer object and elements buffer object.
        /// </summary>
        /// <param name="buffers">Buffers to pass to OpenGl</param>
        /// <param name="isTextured">Whether is textured or not</param>
        void GenerateVBs(Buffers& buffers, bool isTextured);

        /// <summary>
        /// Draws non-solid color objects.
        /// </summary>
        /// <param name="shaderProg">Process ID from the shader program</param>
        /// <param name="vao">Vertex Array Object</param>
        /// <param name="amountIndices">Amount of indices</param>
        void Draw(const SPProc& shaderProg, unsigned int& vao, int amountIndices) const;

        /// <summary>
        /// Makes Pre-draw calls.
        /// </summary>
        void StartDraw();

        /// <summary>
        /// Makes post draw calls.
        /// </summary>
        void EndDraw() const;

        /// <summary>
        /// Updates the view matrix. This function only works with a unique camera.
        /// </summary>
        void UpdateViewMatrix();

#pragma endregion

#pragma region Getters
        /// <summary>
        /// Only access to the singleton unique instance. If no instance has been created, it creates an instance.
        /// </summary>
        /// <returns>Reference to instance</returns>
        static Renderer& GetInstance();

        /// <summary>
        /// Getter for the up vector of the camera.
        /// </summary>
        /// <returns>Camera's Up Vector</returns>
        [[nodiscard]] glm::vec3 GetCameraUp() const;

        /// <summary>
        /// Getter for the targeted position of the camera.
        /// </summary>
        /// <returns>Camera's targeted position</returns>
        [[nodiscard]] glm::vec3 GetCameraTarget() const;

        /// <summary>
        /// Getter for the position of the camera.
        /// </summary>
        /// <returns>Camera's Position</returns>
        [[nodiscard]] glm::vec3 GetCameraPos() const;

        /// <summary>
        /// Getter for the projection matrix.
        /// </summary>
        /// <returns>Projection Matrix</returns>
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const;

        /// <summary>
        /// Getter for the view matrix.
        /// </summary>
        /// <returns>View Matrix</returns>
        [[nodiscard]] glm::mat4 GetViewMatrix() const;
#pragma endregion

#pragma region Setters
        /// <summary>
        /// Sets the reference for the window that's being rendered
        /// </summary>
        /// <param name="window">Window to work on</param>
        void SetWindowRef(Window& window);

        void SetCameraRef(Camera& camera);


#pragma endregion

        void UpdateCamera(float deltaTime);

        Renderer(const Renderer& other) = delete; // copy constructor
        Renderer(Renderer&& other) = delete; // move constructor
        Renderer& operator=(const Renderer& other) = delete; // copy assignment
        Renderer& operator=(Renderer&& other) = delete; // move assignment

    private:
        Renderer();
        ~Renderer() = default;

        Camera* ActiveCamera = nullptr;
        glm::vec3 FixedCameraPos;
        glm::vec3 FixedCameraUp;
        glm::vec3 FixedCameraTarget;
        bool Is2D = false;

        glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 ViewMatrix = glm::mat4(1.0f);

        Window* Window;
    };


} // namespace basilisk
