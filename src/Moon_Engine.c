#include <stdio.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <unistd.h>
#include <signal.h>

Color background = {50u, 50u, 50u, 255u};
Color dark_background = {40u, 40u, 40u, 255u};
Color darker_background = {30u, 30u, 30u, 255u};
Color darkers_background = {25u, 25u, 25u, 255u};

void settings_window(void)
{
    if (fork() == 0)
    {
        execl("./settings", "settings", (char *)NULL);
        _exit(1);
    }
}

void editor_tilebar(void)
{
    int position_x = 0;
    int position_y = 0;
    int size_x = 1920;
    int size_y = 24;
    DrawRectangle(position_x, position_y, size_x, size_y, darker_background);
}

void hierarchy(void)
{
    Rectangle hierarchy_panel = {0, 24, 420, 576};
    DrawRectangle(hierarchy_panel.x, hierarchy_panel.y, hierarchy_panel.width, hierarchy_panel.height, dark_background);

    // tilebar

    Rectangle hierarchy_panel_tilebar = {0, 24, 420, 22};
    DrawRectangle(hierarchy_panel_tilebar.x, hierarchy_panel_tilebar.y, hierarchy_panel_tilebar.width, hierarchy_panel_tilebar.height, darker_background);

    DrawText("HIERARCHY", hierarchy_panel_tilebar.x + 4, hierarchy_panel_tilebar.y + 4, 16, WHITE);
    
    // more options
    
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL,    ColorToInt((Color){ 0, 0, 0, 0 }));
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED,   ColorToInt((Color){ 255, 255, 255, 40 }));
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED,   ColorToInt((Color){ 255, 255, 255, 80 }));

    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL,  ColorToInt(WHITE));
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(WHITE));
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(WHITE));
    GuiSetStyle(BUTTON, BORDER_WIDTH, 0);

    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL,    ColorToInt(WHITE));
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED,   ColorToInt(WHITE));
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED,   ColorToInt(WHITE));
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32); 

    Rectangle button = { 398, 28, 18, 18 };
    if (GuiButton(button, "+"))
    {
        settings_window();
    }
}

void file_manager(void)
{
    int position_x = 0;
    int position_y = 600;
    int size_x = 1500;
    int size_y = 480;
    DrawRectangle(position_x, position_y, size_x, size_y, dark_background);

    // tilebar
    int Tilebar_position_x = 0;
    int Tilebar_position_y = 600;
    int Tilebar_size_x = 1500;
    int Tilebar_size_y = 22;
    DrawRectangle(Tilebar_position_x, Tilebar_position_y, Tilebar_size_x, Tilebar_size_y, darker_background);
    DrawText("FILE MANAGER", Tilebar_position_x + 4, Tilebar_position_y + 4, 16, WHITE);
}

void inspector(void)
{
    int position_x = 1500;
    int position_y = 23;
    int size_x = 420;
    int size_y = 1057;
    DrawRectangle(position_x, position_y, size_x, size_y, dark_background);

    // tilebar
    Rectangle inspector_panel_tilebar = {1499, 24, 421, 22};

    DrawRectangle(inspector_panel_tilebar.x, inspector_panel_tilebar.y, inspector_panel_tilebar.width, inspector_panel_tilebar.height, darker_background);
    DrawText("INSPECTOR", inspector_panel_tilebar.x + 4, inspector_panel_tilebar.y + 4, 16, WHITE);

}

void viewport(void)
{
    // viewport
    int position_x = 420;
    int position_y = 24;
    int size_x = 1080;
    int size_y = 576;
    DrawRectangle(position_x, position_y, size_x, size_y, BLACK);

    // tilebar
    int Tilebar_position_x = 420;
    int Tilebar_position_y = 24;
    int Tilebar_size_x = 1080;
    int Tilebar_size_y = 22;
    DrawRectangle(Tilebar_position_x, Tilebar_position_y, Tilebar_size_x, Tilebar_size_y, darker_background);
    DrawText("VIEWPORT", Tilebar_position_x + 4, Tilebar_position_y + 4, 16, WHITE);
}

int main(void)
{
    InitWindow(1920, 1080, "Moon Engine");
    SetTargetFPS(60);
    ToggleFullscreen();
    while (!WindowShouldClose())
    {
        ClearBackground(BLACK);
        BeginDrawing();
        DrawRectangle(0, 0, 1920, 1080, background);
        editor_tilebar();
        viewport();
        file_manager();
        inspector();
        hierarchy();
        EndDrawing();
        
    }
    CloseWindow();
    return 0;    
}