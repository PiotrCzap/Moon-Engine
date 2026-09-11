#include "main.hpp"
#include "raygui.h"

// =================================================================================================
// FUNKCJA GŁÓWNA
// =================================================================================================

int main(void)
{
    window_size_x = 800;
    window_size_y = 600;
    FPS = 60;
    InitWindow(window_size_x, window_size_y, ENGINE_NAME);
    window_icon = LoadImage("src/Engine Data/icon.png");
    font = LoadFont("src/Engine Data/fonts/Super Jello.ttf");
    SetWindowIcon(window_icon);
    SetTargetFPS(FPS);
    Engine_resource_loader();
    

while (!WindowShouldClose())
{
        // ==========================================
        // UPDATE
        // ==========================================

        print_fps();

        // ==========================================
        // RENDER
        // ==========================================

        BeginDrawing();
        
            ClearBackground(BLACK);
            Project_window();
            

        EndDrawing();
    }
    UnloadImage(window_icon);
    Engine_resource_unloader();
    CloseWindow();
    return 0;
}