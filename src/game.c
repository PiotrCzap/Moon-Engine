#define USE_OOP
#define MOON_ENGINE_IMPLEMENTATION
#include "Moon_Engine.h"

Entity player;
Texture2D sprite;

void ME_Start()
{
    sprite = LoadTexture("src/sprite 1.png");
    player.texture = sprite;
    player.size = (Vector2){32.0f, 32.0f};
    player.position = (Vector2){400.0f, 400.0f};
}

void ME_Render()
{
    Sprite2D(player.texture, (Vector2){player.position.x, player.position.y}, (Vector2){player.size.x, player.size.y}, 0.0f, false, false);
}



void ME_Update()
{
    float dt = GetFrameTime();
    if (IsKeyDown(KEY_A))
    {
        player.position.x -= 500.0f * dt;
    }
    if (IsKeyDown(KEY_D))
    {
        player.position.x += 500.0f * dt;
    }
    if (IsKeyDown(KEY_W))
    {
        player.position.y -= 500.0f * dt;
    }
    if (IsKeyDown(KEY_S))
    {
        player.position.y += 500.0f * dt;
    }
    
}

int main(void)
{
    ME_CreateWindow(800, 600, "game");
    return 0;
}