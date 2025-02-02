#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_teture, Texture2D run_texture);
    virtual void tick(float deltaTime) override;
    void setTarget(Character* t) { target = t; };
    virtual Vector2 getScreenPos() override;

private:
    Character *target;
    float damagePerSec{10.f};
    float radius{25.f};
};