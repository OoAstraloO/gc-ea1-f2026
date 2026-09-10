#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

constexpr float BALL_RADIUS = 25.0f;

int main()
{
    InitWindow(800, 800, "Game");
    InitAudioDevice();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Rectangle ground;
        ground.x = 0;
        ground.y = 700;
        ground.width = GetScreenWidth();
        ground.height = 20.0f;

        Rectangle platform;
        platform.x = 100.0f;
        platform.y = ground.y - 100.0f;
        platform.width = 50.0f;
        platform.height = 100.0f;

        Vector2 ball_launch_position;
        ball_launch_position.x = platform.x + BALL_RADIUS;
        ball_launch_position.y = platform.y - BALL_RADIUS;

        BeginDrawing();
            ClearBackground(WHITE);
            DrawRectangleRec(ground, BEIGE);
            DrawRectangleRec(platform, GRAY);
            DrawCircleV(ball_launch_position, BALL_RADIUS, DARKGRAY);

            DrawCircleV(GetMousePosition(), 20.0f, RED);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
