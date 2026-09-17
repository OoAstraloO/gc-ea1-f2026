#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include <array>
#include <vector>

constexpr float BALL_RADIUS = 25.0f;
constexpr Vector2 GRAVITY = { 0.0f, 100.0f };

// Creates a struct to hold all information each ball needs
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

	// Sets the balls launch position to be on top of the platform
    Vector2 ball_launch_position;
    ball_launch_position.x = platform.x + BALL_RADIUS;
    ball_launch_position.y = platform.y - BALL_RADIUS;

	// Sets the balls initial velocity to be zero
    Vector2 ball_position = ball_launch_position;
    Vector2 ball_velocity = Vector2Zeros;

	// Sets the balls gravity scale to be zero so it doesn't fall until launched
    float ball_gravity_scale = 0.0f;

	// Creates a vector to hold all the balls that are launched
	std::vector<Ball> balls;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

		// Creates a new ball and launches it when the space key is pressed
        if (IsKeyPressed(KEY_SPACE)) 
        {
            Ball ball;
			ball.position = ball_launch_position;
			ball.velocity = Vector2Rotate(Vector2UnitX, -30.0f * DEG2RAD) * 200.0f;
			ball.gravity_scale = 1.0f;
			balls.push_back(ball);
        }
        
		// Updates the position and velocity of each ball in the vector
        for (Ball& ball : balls)
        {
            ball.velocity += GRAVITY * dt * ball.gravity_scale;
            ball.position += ball.velocity * dt;

			// Disables the ball when it hits the ground
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

		// Draws all the balls in the vector that are enabled
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
