#ifndef MOON_ENGINE_H
#define MOON_ENGINE_H

#include <stdio.h>
#include "raylib.h"

void ME_CreateWindow(int size_x, int size_y, const char *title);
void ME_Render(void);
void ME_Update(void);
void ME_Start(void);
Camera2D InitCamera(Vector2 target, float zoom);


#ifdef MOON_ENGINE_IMPLEMENTATION

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

#endif
#endif