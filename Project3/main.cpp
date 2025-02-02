#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    // window width and height
    int windowDimensions[2]{384, 384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash");
    Texture2D map = LoadTexture("nature_tileset/map.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    // character class instance
    Character knight = Character(windowDimensions[0], windowDimensions[1]);
    // enemies
    Enemy goblin{Vector2{800.f, 300.5}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy goblin2{Vector2{400.f, 200.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy goblin3{Vector2{500.f, 700.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")};
    Enemy *enemies[]{&goblin, &goblin2, &goblin3};

    for (Enemy *enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    Prop props[2]{
        Prop{
            Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture("nature_tileset/Log.png")}};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLUE);
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // draw props
        for (auto p : props)
        {
            p.Render(knight.getWorldPos());
        };

        if (!knight.getAlive())
        { // dead
            DrawText("Game Over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        { // alive
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());

        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowDimensions[0] > map.width * mapScale ||
            knight.getWorldPos().y + windowDimensions[1] > map.height * mapScale)
        {
            knight.undoMovement();
        };

        // check prop collision
        for (auto p : props)
        {
            if (CheckCollisionRecs(p.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        };

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }
        EndDrawing();
    }
}