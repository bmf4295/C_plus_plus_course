#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, float windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    data.runningTime += deltaTime;
    if (data.runningTime > data.updateTime)
    {
        data.runningTime = 0.0;
        // animation
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    float windowDimensions[2] = {512, 380};
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");
    SetTargetFPS(60);
    bool collision{};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};

    Texture2D middleGround = LoadTexture("textures/back-buildings.png");
    float mgX{};

    Texture2D foreGround = LoadTexture("textures/foreground.png");
    float fgX{};

    // scarfy aniimation inits
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0.0;
    scarfyData.rec.y = 0.0;
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.runningTime = 0.0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.frame = 0;
    // other scarfy inits
    int velocity = 0;
    bool isInAir = false;
    const int jumpVelocity = -600; // pixels/s/s
    // acceleration of gravity
    const int gravity = 1000; // pixels/s/s

    // nebula data
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    int numOfNebs = 3;
    int nebVelocity = -200;
    AnimData nebulae[numOfNebs]{};

    for (int i = 0; i < numOfNebs; i++)
    {
        nebulae[i].rec = {0.0, 0.0, nebula.width / 8.0f, nebula.height / 8.0f};
        nebulae[i].pos = {windowDimensions[0] + (300 * i), windowDimensions[1] - nebulae[i].rec.height};
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
    }

    float finishLine{nebulae[numOfNebs - 1].pos.x};

    // neb animation
    // nebula velocity in pixels/sec

    while (!WindowShouldClose())
    {

        const float dT = GetFrameTime();

        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);
        bgX -= 20 * dT;
        // scroll background
        if (bgX <= -background.width * 2)
        {
            bgX = 0.0;
        }
        // scroll middleground
        mgX -= 40 * dT;
        if (mgX <= -middleGround.width * 2)
        {
            mgX = 0.0;
        }
        // scroll foreground
        fgX -= 80 * dT;
        if (fgX <= -foreGround.width * 2)
        {
            fgX = 0.0;
        }
        // draw background
        Vector2 bg1Pos{bgX, 0.0};
        Vector2 bg2Pos{bgX + background.width * 2, 0.0};

        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        // draw middleground
        Vector2 mg1Pos{mgX, 0.0};
        Vector2 mg2Pos{mgX + middleGround.width * 2, 0.0};

        DrawTextureEx(middleGround, mg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(middleGround, mg2Pos, 0.0, 2.0, WHITE);

        // draw middleground
        Vector2 fg1Pos{fgX, 0.0};
        Vector2 fg2Pos{fgX + foreGround.width * 2, 0.0};

        DrawTextureEx(foreGround, fg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(foreGround, fg2Pos, 0.0, 2.0, WHITE);

        // ground check
        if (isOnGround(scarfyData, windowDimensions[1]))
        {
            // its on the ground
            isInAir = false;
            velocity = 0;
        }
        else
        {
            // add gravity
            isInAir = true;
            velocity += gravity * dT;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }
        // update nebulae position
        for (int i = 0; i < numOfNebs; i++)
        {
            nebulae[i].pos.x += nebVelocity * dT;
        }

        // update finish line position
        finishLine += nebVelocity * dT;

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // scarfy animation update;
        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        // animate nebulae
        for (int i = 0; i < numOfNebs; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        for (AnimData nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2 * pad,
                nebula.rec.height - 2 * pad};
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height};

            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }
        
        if (collision)
        {
            // lose the game
            DrawText("Game Over!", windowDimensions[0] / 4, windowDimensions[1] / 2, 40, RED);
        }
        else if (scarfyData.pos.x >= finishLine)
        {
            //Win the game
             DrawText("You Win!", windowDimensions[0] / 4, windowDimensions[1] / 2, 40, BLUE);
        }
        else
        {
            // draw nebulae
            for (int i = 0; i < numOfNebs; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }
            // draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }

        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(middleGround);
    UnloadTexture(foreGround);
    CloseWindow();
};
