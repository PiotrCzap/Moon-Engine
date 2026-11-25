#define MOON_ENGINE_IMPLEMENTATION
#include "Moon_Engine.h"

static float player_x = 0.0f;
static float player_y = 0.0f;
static float player_w = 40.0f;
static float player_h = 40.0f;
static float player_speed = 240.0f;

static Camera2D cam;
static float cam_zoom = 1.0f;

void ME_Start(void)
{
    player_x = 0.0f;
    player_y = 0.0f;
    cam = InitCamera((Vector2){ player_x, player_y }, cam_zoom);
}

void ME_Update(void)
{
    float dt = GetFrameTime();

    float dx = 0.0f;
    float dy = 0.0f;

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  dx -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  dy += 1.0f;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    dy -= 1.0f;

    if (dx != 0.0f && dy != 0.0f) {
        dx *= 0.70710678f;
        dy *= 0.70710678f;
    }

    player_x += dx * player_speed * dt;
    player_y += dy * player_speed * dt;

    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f) {
        cam_zoom += wheel * 0.1f;
        if (cam_zoom < 0.25f) cam_zoom = 0.25f;
        if (cam_zoom > 4.0f)  cam_zoom = 4.0f;
    }

    cam = InitCamera((Vector2){ player_x, player_y }, cam_zoom);
}

void ME_Render(void)
{
    BeginMode2D(cam);
        for (int x = -800; x <= 800; x += 50) {
            DrawLine(x, -800, x, 800, DARKGRAY);
        }
        for (int y = -800; y <= 800; y += 50) {
            DrawLine(-800, y, 800, y, DARKGRAY);
        }

        DrawRectangle(
            (int)(player_x - player_w * 0.5f),
            (int)(player_y - player_h * 0.5f),
            (int)player_w,
            (int)player_h,
            SKYBLUE
        );
    EndMode2D();
}

int main(void)
{
    ME_CreateWindow(800, 600, "game");
    return 0;
}