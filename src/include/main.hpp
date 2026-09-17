#pragma once

#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "raygui.h"


// =================================================================================================
// Variables
// =================================================================================================

extern bool debug_mode;
extern bool editor_mode;

inline Image window_icon;
extern int window_size_x;
extern int window_size_y;
extern const char* ENGINE_NAME;
extern const char* ENGINE_VERSION;
extern int FPS;
extern bool show_object;

// colors

extern const Color LIGHT_GRAY_COLOR;
extern const Color GRAY_COLOR;
extern const Color DARK_GRAY_COLOR;
extern const Color DARKER_GRAY_COLOR;
extern const Color BLACK_COLOR;

// fonts

extern int font_selected;
extern Font font;

// textures

inline Texture2D null_txt;
inline Texture2D projects_icon;
inline Texture2D learn_icon;
inline Texture2D settings_icon;

typedef void (*ButtonAction)(void);

// Engine draw functions

void Engine_draw_rectangle_shape(const float pos_x, const float pos_y, const float size_x, const float size_y, const Color color);
void Engine_draw_circle_shape(const float pos_x, const float pos_y, const float radius, const Color color);
void Engine_draw_ellipse_shape(const float pos_x, const float pos_y, const float radius_x, const float radius_y, const Color color);
void Engine_draw_rectangle_shape_with_texture(const Texture2D texture, const float pos_x, const float pos_y, const float size_x, const float size_y, float rotation, const Color color);
void Engine_draw_text(const char text[], const float pos_x, const float pos_y, const float font_size, const Color color);
void Engine_draw_text_better(const Font font, const char text[], const Vector2 text_position, const Vector2 text_origin, const float rotation, const float font_size, const float spacing, const Color color);

// Engine loader/unloader functions

void Engine_resource_loader(void);
void Engine_resource_unloader(void);

// debug functions

void print_fps();
void Engine_debug_window();

// hub functions

void Projects_tab();
void Project_window(void);

// editor.cpp

void inspector();
void file_manager();
void hierarchy();
void viewport();
void Engine_add_game_object(const Texture2D texture, const float pos_x, const float pos_y, const float size_x, const float size_y, const float rotation, const Color color, const bool visible);

struct transform
{
    float pos_x, pos_y;
    float size_x, size_y;
    float rotation;
};

struct sprite_renderer
{
    Texture2D texture;
    Color color;
    int visible;
};

struct text_renderer
{
    char *text;
    float font_size;
    Color color;
    bool visible;
};

struct GameObject
{
   char name[32];
   bool isDragging;
   struct transform transform;
   struct sprite_renderer sprite_renderer;
   struct text_renderer text_renderer;
};

extern int selected_object_index; // for class New_GameObject

class New_GameObject
{
public:
    GameObject data;

    // update functions (obsługuje przeciąganie myszką i granice viewportu)
    void Update(bool& is_something_dragging, int index) 
    {
        Rectangle r = { data.transform.pos_x, data.transform.pos_y, data.transform.size_x, data.transform.size_y };

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), r))
        {
            selected_object_index = index; // Selecting Object in Inspector

            if (!is_something_dragging)
            {
                data.isDragging = true;
                is_something_dragging = true;
            }
        }

        // Chwytamy obiekt tylko wtedy, gdy żaden inny nie jest przeciągany
        if (!is_something_dragging && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), r))
        {
            data.isDragging = true;
            is_something_dragging = true;
        }

        // Object dragging
        if (data.isDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 d = GetMouseDelta();
            data.transform.pos_x += d.x;
            data.transform.pos_y += d.y;

            // Opcjonalne: blokada granic Viewportu (300 do 1650, 0 do 700)
            if (data.transform.pos_x < 300.0f) data.transform.pos_x = 300.0f;
            if (data.transform.pos_x > 1650.0f - data.transform.size_x) data.transform.pos_x = 1650.0f - data.transform.size_x;
            if (data.transform.pos_y < 0.0f) data.transform.pos_y = 0.0f;
            if (data.transform.pos_y > 700.0f - data.transform.size_y) data.transform.pos_y = 700.0f - data.transform.size_y;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            data.isDragging = false;
        }
    }

    
    void Draw(bool debug_mode) 
    {
        // draws red outline on object
        if (debug_mode)
        {
            Rectangle debugRec = { 
                data.transform.pos_x - 2.0f, 
                data.transform.pos_y - 2.0f, 
                data.transform.size_x + 4.0f, 
                data.transform.size_y + 4.0f 
            };
            DrawRectangleLinesEx(debugRec, 2.0f, RED);
        }

        // draws texture on object
        Engine_draw_rectangle_shape_with_texture(
            data.sprite_renderer.texture,
            data.transform.pos_x, data.transform.pos_y,
            data.transform.size_x, data.transform.size_y,
            data.transform.rotation, data.sprite_renderer.color
        );
    }
};