#ifndef MOON_ENGINE_H
#define MOON_ENGINE_H

#include <stdio.h>
#include "raylib.h"

void ME_CreateWindow(int size_x, int size_y, const char *title);
void ME_Render(void); // Draws the current frame
void ME_Update(void); // In Every Frame
void ME_Start(void); // Called once
Camera2D InitCamera(Vector2 target, float zoom);

#define USE_ECS
#define USE_OOP

#ifdef MOON_ENGINE_IMPLEMENTATION

#if defined(USE_ECS)
    
#elif defined(USE_OOP)
    void Sprite2D(const Texture2D texture, const Vector2 position, const Vector2 size, const float rotation, const bool flip_h, const bool flip_v)
#else
    #error "Define USE_ECS or USE_OOP before including Moon_Engine.h"
#endif

void ME_CreateWindow(const int size_x, const int size_y, const char *title)
{
    InitWindow(size_x, size_y, title);
    SetTargetFPS(60);

    ME_Start();

    while (!WindowShouldClose())
    {
        ME_Update();

        BeginDrawing();
            ClearBackground(BLACK);
            ME_Render();
        EndDrawing();
    }

    CloseWindow();
}

Camera2D InitCamera(Vector2 target, float zoom)
{
    Camera2D camera = {0};
    camera.target = target;
    camera.offset = (Vector2){
        GetScreenWidth() * 0.5f,
        GetScreenHeight() * 0.5f
    };
    camera.rotation = 0.0f;
    camera.zoom = (zoom > 0.01f) ? zoom : 1.0f;
    return camera;
}

void Sprite2D(const Texture2D texture, const Vector2 position, const Vector2 size, const float rotation, const bool flip_h, const bool flip_v) // Object with texture
{
    Rectangle source = {
        0.0f,
        0.0f,
        (float)texture.width,
        (float)texture.height
    };
    if (flip_h) source.width  = -source.width;
    if (flip_v) source.height = -source.height;
    Rectangle dest = {
        position.x,
        position.y,
        size.x,
        size.y
    };
    Vector2 origin = {
        size.x * 0.5f,
        size.y * 0.5f
    };
    DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
}

typedef struct
{
    Texture2D texture;
    Vector2 position;
    Vector2 size;
    float rotation;
    bool flip_h;
    bool flip_v;

} Entity;


#endif
#endif