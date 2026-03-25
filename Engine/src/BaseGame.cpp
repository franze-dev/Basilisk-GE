#include "BaseGame.h"

#include <chrono>
#include <glm/glm.hpp>

#include "Log.h"
#include "Renderer.h"
#include "Window.h"

namespace basilisk
{

    BaseGame::BaseGame(const char* windowName, const int sizeX, const int sizeY, const bool is2D) :
        Renderer(Renderer::GetInstance()), X(sizeX), Y(sizeY), InputSystem(nullptr)
    {
        
        Log::Get()->info("Loading Basilisk Engine");
        
        this->Renderer.InitGLFW();

        this->Renderer.SetGlVersion();

        this->Window = new basilisk::Window(windowName, glm::ivec2(sizeX, sizeY));

        this->WindowName = windowName;

        this->Renderer.InitGL(is2D);

        this->Renderer.SetWindowRef(*this->Window);

        this->InputSystem = Input(this->Window);
        
        Log::Get()->info("Loading Complete");

    }

    BaseGame::~BaseGame()
    {
        delete this->Window;
    }

    BaseGame::BaseGame(const BaseGame& other) :
        Renderer(Renderer::GetInstance()), X(other.X), Y(other.Y), InputSystem(nullptr)
    {

        this->WindowName = other.WindowName;
        this->Window = new basilisk::Window(other.WindowName, glm::vec2(other.X, other.Y));
        this->Renderer.SetWindowRef(*this->Window);
        this->InputSystem = Input(this->Window);

    }

    BaseGame::BaseGame(BaseGame&& other) noexcept :
        Renderer(Renderer::GetInstance()), X(other.X), Y(other.Y), InputSystem(nullptr)
    {

        this->WindowName = other.WindowName;
        this->Window = other.Window;
        other.Window = nullptr;
        other.X = 0;
        other.Y = 0;
        other.WindowName = "";
        this->Renderer.SetWindowRef(*this->Window);
        this->InputSystem = Input(this->Window);

    }

    BaseGame& BaseGame::operator=(const BaseGame& other)
    {

        if (this != &other)
        {
            this->X = other.X;
            this->Y = other.Y;
            this->WindowName = other.WindowName;
            this->Window = new basilisk::Window(other.WindowName, glm::vec2(other.X, other.Y));
            Renderer.SetWindowRef(*this->Window);
            this->InputSystem = Input(this->Window);
        }

        return *this;

    }

    BaseGame& BaseGame::operator=(BaseGame&& other) noexcept
    {

        if (this != &other)
        {
            this->X = other.X;
            this->Y = other.Y;
            this->WindowName = other.WindowName;
            this->Window = other.Window;

            other.Window = nullptr;
            other.X = 0;
            other.Y = 0;
            other.WindowName = "";

            Renderer.SetWindowRef(*this->Window);
            this->InputSystem = Input(this->Window);
        }

        return *this;
    }

    void BaseGame::Run()
    {
        this->Init();
        auto old = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> now = old;

        Log::Get()->info("Running game...");
        while (!this->WindowShouldClose())
        {
            this->InputSystem.UpdateInputs();

            now = std::chrono::system_clock::now();
            this->Delta = std::chrono::duration<float>(now - old).count();
            old = now;

            this->Update();
            this->Renderer.StartDraw();
            this->Draw();
            this->Renderer.EndDraw();

        }

        this->Close();
    }

    bool BaseGame::WindowShouldClose() const
    {
        return this->Window->WindowShouldClose();
    }

    void BaseGame::Close() const
    {
        glfwTerminate();
    }

    float BaseGame::GetDelta()
    {
        return this->Delta;
    }

    Input& BaseGame::GetInputSystem()
    {
        return this->InputSystem;
    }
} // namespace basilisk
