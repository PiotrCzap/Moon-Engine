#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <unistd.h>
#include <signal.h>
#include "Moon_Engine.h"

Color background = {50u, 50u, 50u, 255u};
Color dark_background = {40u, 40u, 40u, 255u};
Color darker_background = {30u, 30u, 30u, 255u};
Color darkers_background = {25u, 25u, 25u, 255u};

int actual_object = 0;

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

GameObject objects[MAX_OBJECTS];
int object_count = 0;


void AddGameObject(const char *name, const float pos_x, const float pos_y, const float pos_z)
{
    if (object_count >= MAX_OBJECTS) return;
    
    objects[object_count].ID = object_count;
    snprintf(objects[object_count].name, MAX_NAME_LEN, "obj %i", objects[object_count].ID);
    objects[object_count].visible = 1;
    objects[object_count].renderer.color = WHITE;
    objects[object_count].active = 1;
    objects[object_count].renderer.graphic = 0;
    Texture2D texture = { 0 };
    objects[object_count].renderer.sprite = texture;
    objects[object_count].transform.x = pos_x;
    objects[object_count].transform.y = pos_y;
    objects[object_count].transform.z = pos_z;
    printf("%s . %i\n", objects[object_count].name, objects[object_count].ID);
    object_count ++;
    
}

void hierarchy_object_grid(const GameObject obj, const int pos_x, const int pos_y, const int size_x, const int size_y)
{
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL,    ColorToInt(background));
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED,   ColorToInt(darker_background));
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED,   ColorToInt(darkers_background));

    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL,  ColorToInt(WHITE));
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(WHITE));
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(WHITE));
    GuiSetStyle(BUTTON, BORDER_WIDTH, 0);

    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL,    ColorToInt(WHITE));
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED,   ColorToInt(WHITE));
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED,   ColorToInt(WHITE));
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32); 

    Rectangle hierarchy_object_list_panel = {pos_x, pos_y, size_x, size_y};

    if (GuiButton(hierarchy_object_list_panel, "O"))
    {
        actual_object = obj.ID;
    }
    
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
        AddGameObject("obiekt", 10, 10, 10);
    }
    for (unsigned int i = 0; i < object_count; i++)
    {
        int col = i % 6;
        int row = i / 6;
        hierarchy_object_grid(objects[i], 10 + col * 60, (row + 1) * 60, 50, 50);
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
    int position_y = 24;
    int size_x = 420;
    int size_y = 1057;
    DrawRectangle(position_x, position_y, size_x, size_y, dark_background);

    // tilebar
    Rectangle inspector_panel_tilebar = {1499, 24, 421, 22};

    DrawRectangle(inspector_panel_tilebar.x, inspector_panel_tilebar.y, inspector_panel_tilebar.width, inspector_panel_tilebar.height, darker_background);
    DrawText("INSPECTOR", inspector_panel_tilebar.x + 4, inspector_panel_tilebar.y + 4, 16, WHITE);

    if (object_count > 0) DrawText(objects[actual_object].name, position_x + 10, position_y + 50, 16, WHITE);
    
    
}

void viewport(void)
{
    Color viewport_color = {60u, 60u, 60u, 255u};
    // viewport
    int position_x = 420;
    int position_y = 24;
    int size_x = 1080;
    int size_y = 576;
    DrawRectangle(position_x, position_y, size_x, size_y, viewport_color);

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