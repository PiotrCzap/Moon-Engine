#pragma once

#include "raylib.h"
#include <stdio.h>
#include <sys/resource.h>
#include "raygui.h"

// =================================================================================================
// Zmienne
// =================================================================================================

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

// console debug functions

void print_fps();

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
   struct transform transform;
   struct sprite_renderer sprite_renderer;
   struct text_renderer text_renderer;
};