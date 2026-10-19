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

// hierarchy panel
Rectangle hierarchy_dock_left  = { 1, 24, 420, 1056 };
Rectangle hierarchy_dock_right = { 1500, 24, 420, 1056 };
Rectangle hierarchy_dock_full  = { 1500, 24, 420, 1056 };
Rectangle hierarchy_dock_half  = { 1500, 24, 420, 579 };

Rectangle hierarchy_panel = { 1500, 24, 420, 1056 }; 

// inspector panel

Rectangle inspector_dock_left = { 0, 24, 420, 576};
Rectangle inspector_dock_right = { 1500, 24, 420, 576};

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
    static Rectangle hierarchy_panel = { 1500, 24, 420, 1056 };
    DrawRectangleRec(hierarchy_panel, dark_background);

    // tilebar
    int Tilebar_position_x = 1500;
    int Tilebar_position_y = 24;
    Rectangle tilebar = { hierarchy_panel.x, hierarchy_panel.y, hierarchy_panel.width, 22 };
    DrawRectangleRec(tilebar, darker_background);
    DrawText("HIERARCHY", tilebar.x + 4, tilebar.y + 4, 16, WHITE);
    int button_size = 18;
    Rectangle more_button = { hierarchy_panel.x + 400, hierarchy_panel.y + 3, button_size, button_size };
    static int show_docking = 0;
    if (GuiButton(more_button, "+"))
    {
        show_docking = 1;
    }

    if (show_docking)
    {
        DrawRectangle(hierarchy_panel.x + 293, hierarchy_panel.y + 26, 120, 120, darker_background);

        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL,  ColorToInt(GRAY));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(LIGHTGRAY));
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(DARKGRAY));
        GuiSetStyle(BUTTON, BORDER_WIDTH, 0);

        if (GuiButton((Rectangle){ hierarchy_panel.x + 301, hierarchy_panel.y + 32, 40, 70 }, ""))
        {
            show_docking = 0;
            hierarchy_panel = hierarchy_dock_left;
        }
        if (GuiButton((Rectangle){ hierarchy_panel.x + 365, hierarchy_panel.y + 32, 40, 70 }, ""))
        {
            show_docking = 0;
            hierarchy_panel = hierarchy_dock_right;
        }
        if (GuiButton((Rectangle){ hierarchy_panel.x + 301, hierarchy_panel.y + 106, 50, 34 }, ""))
        {
            show_docking = 0;
            hierarchy_panel.height = hierarchy_dock_full.height;
        }
        if (GuiButton((Rectangle){ hierarchy_panel.x + 355, hierarchy_panel.y + 106, 50, 34 }, ""))
        {
            show_docking = 0;
            hierarchy_panel.height = hierarchy_dock_half.height;
        }
    }

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
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24); 

    Rectangle button = { hierarchy_panel.x + 350, hierarchy_panel.y + 3, 18, 18 };
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
    int position_x = 0;
    int position_y = 24;
    int size_x = 420;
    int size_y = 576;
    DrawRectangle(position_x, position_y, size_x, size_y, dark_background);

    // tilebar
    int Tilebar_position_x = 0;
    int Tilebar_position_y = 24;
    int Tilebar_size_x = 420;
    int Tilebar_size_y = 22;
    DrawRectangle(Tilebar_position_x, Tilebar_position_y, Tilebar_size_x, Tilebar_size_y, darker_background);
    DrawText("INSPECTOR", Tilebar_position_x + 4, Tilebar_position_y + 4, 16, WHITE);

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