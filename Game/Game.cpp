#include "Game.h"

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) :
        BaseGame(windowName, sizeX, sizeY, true), 
        Map("res/assets/map.json", "res/assets/spritesheet.png", {sizeX, sizeY}),
        Player(100.0f, {Map.GetTileSize(), Map.GetTileSize()}, {600.0f, 500.0f}), 
        CollisionBox({0.0f, 0.0f}, {1.0f, 1.0f}, basilisk::Color::Red)
    {
    }

    void Game::Init()
    {
        auto playerMat = basilisk::Material::New(true);
        this->Player.SetMaterial(playerMat);
        this->Player.Init();

        this->Player.MoveUpIA = &this->GetInputSystem().NewInput(basilisk::Keys::W);
        this->Player.MoveLeftIA = &this->GetInputSystem().NewInput(basilisk::Keys::A);
        this->Player.MoveDownIA = &this->GetInputSystem().NewInput(basilisk::Keys::S);
        this->Player.MoveRightIA = &this->GetInputSystem().NewInput(basilisk::Keys::D);

        const auto collisionMat = basilisk::Material::New(false);
        this->CollisionBox.SetMaterial(collisionMat);
        this->CollisionBox.Init();
        this->CollisionBox.SetPosition(Player.GetPosition2D());
        this->CollisionBox.SetScaling(this->Player.GetScale2D());

        this->Map.Init();
        this->Player.map = &this->Map;
    }

    void Game::Update()
    {
        this->Player.Delta = this->GetDelta();
        this->Player.Update();
        this->CollisionBox.SetPosition(this->Player.GetPosition2D());
    }

    void Game::Draw()
    {
        //this->Map.Draw();
        this->CollisionBox.Draw();
        this->Player.Draw();
    }

} // namespace game
