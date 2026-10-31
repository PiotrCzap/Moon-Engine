#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <unistd.h>
#include <signal.h>
#include "Moon_Engine.h"

// =============================================================================================================
// COLORS
// =============================================================================================================

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

// =============================================================================================================
// HIERARCHY
// =============================================================================================================

GameObject objects[MAX_OBJECTS];
int object_count = 0;
int actual_object = 0;

void AddGameObject(const char *name, const float pos_x, const float pos_y, const float pos_z, const float size_x, const float size_y, const float size_z)
{
    if (object_count >= MAX_OBJECTS) return;
    
    objects[object_count].ID = object_count;
    snprintf(objects[object_count].name, MAX_NAME_LEN, "Empty Object_ %i", objects[object_count].ID);
    objects[object_count].visible = 1;
    objects[object_count].renderer.color = WHITE;
    objects[object_count].active = 1;
    objects[object_count].renderer.graphic = 0;
    Texture2D texture = { 0 };
    objects[object_count].renderer.sprite = texture;
    objects[object_count].transform.pos_x = pos_x;
    objects[object_count].transform.pos_y = pos_y;
    objects[object_count].transform.pos_z = pos_z;
    objects[object_count].transform.size_x = size_x;
    objects[object_count].transform.size_y = size_y;
    objects[object_count].transform.size_z = size_z;
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

    if (GuiButton(hierarchy_object_list_panel, ""))
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
        AddGameObject("Empty Object_", 10, 10, 10, 100, 100, 100);
    }
    for (unsigned int i = 0; i < object_count; i++)
    {
        int col = i % 6;
        int row = i / 6;
        hierarchy_object_grid(objects[i], 10 + col * 60, (row + 1) * 60, 50, 50);
    }
}

// =============================================================================================================
// FILE MANAGER
// =============================================================================================================

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

// =============================================================================================================
// INSPECTOR
// =============================================================================================================

void inspector(void)
{
    int position_x = 1500;
    int position_y = 24;
    int size_x = 420;
    int size_y = 1057;
    DrawRectangle(position_x, position_y, size_x, size_y, dark_background);

    // Tilebar
    Rectangle inspector_panel_tilebar = {1499, 24, 421, 22};
    DrawRectangle(inspector_panel_tilebar.x, inspector_panel_tilebar.y, inspector_panel_tilebar.width, inspector_panel_tilebar.height, darker_background);
    DrawText("INSPECTOR", inspector_panel_tilebar.x + 4, inspector_panel_tilebar.y + 4, 16, WHITE);

    if (object_count > 0 && actual_object >= 0 && actual_object < object_count)
    {
        GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
        GuiSetStyle(DEFAULT, TEXT_SIZE, 16); 
        Rectangle textbox = { position_x + 50, position_y + 30, 300, 16 };
        
        static bool textBoxEditMode = false;

        if (GuiTextBox(textbox, objects[actual_object].name, MAX_NAME_LEN, textBoxEditMode))
        {
            textBoxEditMode = !textBoxEditMode;
        }
    }

    if (object_count > 0 && actual_object >= 0 && actual_object < object_count)
    {
        GuiSetStyle(DROPDOWNBOX, BASE_COLOR_NORMAL, ColorToInt(darker_background));
        GuiSetStyle(DROPDOWNBOX, BASE_COLOR_FOCUSED, ColorToInt(darkers_background));
        GuiSetStyle(DROPDOWNBOX, BASE_COLOR_PRESSED, ColorToInt(dark_background));
        GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiSetStyle(DROPDOWNBOX, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
        GuiSetStyle(DROPDOWNBOX, BORDER_WIDTH, 0);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 16); 
        Rectangle SpriteOptions_menu_rect = { position_x + 50, position_y + 60, 100, 24 };

        static bool SpriteOptionsEditMode = false;
        static int SpriteOptions_active = 0; // aktualnie wybrana opcja

        // opcje w menu
        const char *SpriteOptions = "Square;Triangle;Circle";

        if (GuiDropdownBox(SpriteOptions_menu_rect, SpriteOptions, &SpriteOptions_active, SpriteOptionsEditMode))
        {
            SpriteOptionsEditMode = !SpriteOptionsEditMode;
            objects[actual_object].renderer.graphic = SpriteOptions_active;
        }
    }
    
}

// =============================================================================================================
// VIEWPORT
// =============================================================================================================

void viewport(void)
{
    Color viewport_color = {60u, 60u, 60u, 255u};
    // viewport
    int position_x = 420;
    int position_y = 24;
    int size_x = 1080;
    int size_y = 576;
    DrawRectangle(position_x, position_y, size_x, size_y, viewport_color);

    static Vector2 view_offset = { 850.0f, 256.0f };
    static float zoom = 1.0f; // camera zoom
    static bool is_dragging = false;

    Rectangle viewport_rect = { position_x, position_y, size_x, size_y };
    Vector2 mouse = GetMousePosition();
    bool mouse_in_viewport = CheckCollisionPointRec(mouse, viewport_rect);

    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        Vector2 delta = GetMouseDelta();
        view_offset.x += delta.x;
        view_offset.y += delta.y;
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0 && mouse_in_viewport)
    {
        Vector2 world_before = {
            (mouse.x - view_offset.x) / zoom,
            (mouse.y - view_offset.y) / zoom
        };

        zoom += wheel * 0.1f * zoom;
        if (zoom < 0.1f) zoom = 0.1f;
        if (zoom > 5.0f) zoom = 5.0f;

        view_offset.x = mouse.x - world_before.x * zoom;
        view_offset.y = mouse.y - world_before.y * zoom;
    }

    BeginScissorMode(position_x, position_y + 22, size_x, size_y - 22);

    for (unsigned int i = 0; i < object_count; i++)
    {
        Vector2 position = { 
            objects[i].transform.pos_x * zoom + view_offset.x,
            objects[i].transform.pos_y * zoom + view_offset.y
        };
        Vector2 size = {
            objects[i].transform.size_x * zoom,
            objects[i].transform.size_y * zoom
        };

        Color color = objects[i].renderer.color;

        
        if (objects[i].renderer.graphic == 0)
        {
            DrawRectangleV(position, size, color);
            //DrawRectangleLines((int)position.x, (int)position.y, (int)size.x, (int)size.y, BLACK);
        }
        if (objects[i].renderer.graphic == 1)
        {
            Vector2 v1 = { position.x + size.x / 2.0f, position.y };
            Vector2 v2 = { position.x, position.y + size.y };
            Vector2 v3 = { position.x + size.x, position.y + size.y };
            
            DrawTriangle(v1, v2, v3, color);
            //DrawTriangleLines(v1, v2, v3, BLACK);
        }
        if (objects[i].renderer.graphic == 2)
        {
            Vector2 center = { position.x + size.x / 2.0f, position.y + size.y / 2.0f };
            float radius = (size.x < size.y ? size.x : size.y) / 2.0f;
            
            DrawCircleV(center, radius, color);
            //DrawCircleLines((int)center.x, (int)center.y, radius, BLACK);
        }
    }

    EndScissorMode();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouse_in_viewport)
    {
        int clicked_index = -1;

        // Sprawdzamy wszystkie obiekty które zostały kliknięte
        for (int i = (int)object_count - 1; i >= 0; i--)
        {
            Rectangle obj_rect = { 
                objects[i].transform.pos_x * zoom + view_offset.x,
                objects[i].transform.pos_y * zoom + view_offset.y,
                objects[i].transform.size_x * zoom,
                objects[i].transform.size_y * zoom
            };

            if (CheckCollisionPointRec(mouse, obj_rect))
            {
                clicked_index = i;
                break;
            }
        }

        if (clicked_index != -1)
        {
            actual_object = objects[clicked_index].ID;
            is_dragging = true;
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        is_dragging = false;
    }

    if (is_dragging && actual_object >= 0 && actual_object < object_count)
    {
        Vector2 delta = GetMouseDelta();

        objects[actual_object].transform.pos_x += delta.x / zoom;
        objects[actual_object].transform.pos_y += delta.y / zoom;
    }

    // tilebar
    int Tilebar_position_x = 420;
    int Tilebar_position_y = 24;
    int Tilebar_size_x = 1080;
    int Tilebar_size_y = 22;
    DrawRectangle(Tilebar_position_x, Tilebar_position_y, Tilebar_size_x, Tilebar_size_y, darker_background);
    DrawText("VIEWPORT", Tilebar_position_x + 4, Tilebar_position_y + 4, 16, WHITE);
}

// =============================================================================================================
// MAIN
// =============================================================================================================

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
        viewport();
        editor_tilebar();
        file_manager();
        inspector();
        hierarchy();
        EndDrawing();

    }
    CloseWindow();
    return 0;
}