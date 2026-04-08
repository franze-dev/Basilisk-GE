#include "Game.h"

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) :
        BaseGame(windowName, sizeX, sizeY, false), 
        CollisionBox({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, basilisk::Color::Red), 
        Mouse(GetWindowPtr()),
        Camera(Mouse, this->GetInputSystem())
    {
        this->SetCameraRef(Camera);
    }

    void Game::Init()
    {
        const auto collisionMat = basilisk::Material::New(false);
        this->CollisionBox.SetMaterial(collisionMat);
        this->CollisionBox.Init();

        Camera.SetEntity(&this->CollisionBox, {0.0f, 0.0f, 0.0f}, false);
    }

    void Game::Update()
    {
        Camera.Update(this->GetDelta());
    }

    void Game::Draw()
    {
        this->CollisionBox.Draw();
    }

} // namespace game
