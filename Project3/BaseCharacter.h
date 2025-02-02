
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"
#include "raymath.h"
class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive(){return alive;};
    void setAlive(bool isAlive){alive = isAlive;};

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    Vector2 velocity{};
    int windowWidth{};
    int windowHeight{};
    float width{};
    float height{};
    float rightLeft{1.f};
    float runningTime{};
    int frame{};
    float speed{0.12f};
    const int maxFrames{6};
    const float updatetime = 1.0f / 12.0f;
    const float scale{4.0f};
    

private:
bool alive{true};
};

#endif