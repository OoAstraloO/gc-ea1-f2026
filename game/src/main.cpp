#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include <array>
#include <vector>

constexpr float BALL_RADIUS = 25.0f;
constexpr Vector2 GRAVITY = { 0.0f, 100.0f };

struct Ball
{
    Vector2 position;
    Vector2 velocity;
	float gravity_scale;
	bool enabled = true;
};

int main()
{
    InitWindow(800, 800, "Game");
    InitAudioDevice();
    SetTargetFPS(60);

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

    Vector2 ball_position = ball_launch_position;
    Vector2 ball_velocity = Vector2Zeros;

    float ball_gravity_scale = 0.0f;

	std::vector<Ball> balls;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        if (IsKeyPressed(KEY_SPACE)) 
        {
            Ball ball;

			ball.position = ball_launch_position;
			ball.velocity = Vector2Rotate(Vector2UnitX, -30.0f * DEG2RAD) * 200.0f;
			ball.gravity_scale = 1.0f;
			balls.push_back(ball);
        }
         
        for (Ball& ball : balls)
        {
            ball.velocity += GRAVITY * dt * ball.gravity_scale;
            ball.position += ball.velocity * dt;

            if (ball.position.y >= ground.y) 
            {
                ball.enabled = false;
            }
        }
        
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangleRec(ground, BEIGE);
        DrawRectangleRec(platform, GRAY);

        DrawCircleV(ball_launch_position, BALL_RADIUS, DARKGRAY);

        DrawCircleV(GetMousePosition(), 20.0f, RED);

        for (const Ball& ball:balls)
        {
            if (ball.enabled == true) 
            {
                DrawCircleV(ball.position, BALL_RADIUS, SKYBLUE);

            }
        }

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
