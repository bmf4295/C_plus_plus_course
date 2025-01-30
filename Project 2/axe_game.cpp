#include "raylib.h"

int main()
{

    // Window dimensions
    int width = 800;
    int height = 450;
    // circle initial position
    int circleX = 200;
    int circleY = height / 2;
    int radius = 25;
    // circle edges
    int l_circle_x = circleX - radius;
    int r_circle_x = circleX + radius;
    int u_circle_y = circleY - radius;
    int b_circle_y = circleY + radius;

    // axe position
    int axeX = width / 2;
    int axeY = 0;
    int axeLength = 50;
    int direction = 10;
    // axe edges
    int l_axe_x = axeX;
    int r_axe_x = axeX + axeLength;
    int u_axe_y = axeY;
    int b_axe_y = axeY + axeLength;

    bool collision_with_axe{
                            (b_axe_y >= u_circle_y) && 
                            (u_axe_y <= b_circle_y) && 
                            (r_axe_x >= l_circle_x) && 
                            (l_axe_x <= r_circle_x)
                            };

    InitWindow(width, height, "Axe Game");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (collision_with_axe)
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }
        else
        {
            //update edges
            l_circle_x = circleX - radius;
            r_circle_x = circleX + radius;
            u_circle_y = circleY - radius;
            b_circle_y = circleY + radius;

            l_axe_x = axeX;
            r_axe_x = axeX + axeLength;
            u_axe_y = axeY;
            b_axe_y = axeY + axeLength;
           
           //update collision 
           collision_with_axe=
                            (b_axe_y >= u_circle_y) && 
                            (u_axe_y <= b_circle_y) && 
                            (r_axe_x >= l_circle_x) && 
                            (l_axe_x <= r_circle_x);

            DrawCircle(circleX, circleY, radius, BLUE);
            DrawRectangle(axeX, axeY, axeLength, axeLength, RED);

            // move axe
            axeY += direction;
            if (axeY > height || axeY < 0)
            {
                direction = -direction;
            }

            // Start of Game Logic
            if (IsKeyDown(KEY_D) && circleX < width)
            {
                circleX += 10;
            }
            else if (IsKeyDown(KEY_A) && circleX > 0)
            {
                circleX -= 10;
            }
            if (IsKeyDown(KEY_W) && circleY > 0)
            {
                circleY -= 10;
            }
            if (IsKeyDown(KEY_S) && circleY < height)
            {
                circleY += 10;
            }

            
            // if(){
            //     collision_with_axe = true;
            // }

        }

        // End of Game Logic
        EndDrawing();
    }
}