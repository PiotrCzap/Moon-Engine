#include "main.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int window_size_x = 800;
int window_size_y = 600;
const char* ENGINE_NAME = "Moon Engine\0";
const char* ENGINE_VERSION = "Version: 0.0.1\0";
int FPS = 60;

const Color LIGHT_GRAY_COLOR = { 60u, 60u, 60u, 255u };
const Color GRAY_COLOR = { 50u, 50u, 50u, 255u };
const Color DARK_GRAY_COLOR = { 40u, 40u, 40u, 255u };
const Color DARKER_GRAY_COLOR = { 30u, 30u, 30u, 255u };

int font_selected;
Font font;

struct GameObject player;
struct GameObject test_text;

// FUNKCJA PRINTUJĄCA FPSY W KONSOLI
void print_fps(void)
{
    printf("FPS: %d\n", GetFPS());
}

void Engine_resource_loader(void)
{
    // textures
    null_txt = LoadTexture("src/Engine Data/null.png");
    projects_icon = LoadTexture("src/Engine Data/projects icon.png");
    learn_icon = LoadTexture("src/Engine Data/learn icon.png");
    settings_icon = LoadTexture("src/Engine Data/Settings.png");

    // fonts
    //font = LoadFont("src/Engine Data/fonts/Super Jello.ttf");
    //font = LoadFont("src/Engine Data/fonts/SoundWave-Regular.ttf");
    //font = LoadFont("src/Engine Data/fonts/Now Breaks DEMO VERSION.ttf");
}

void Engine_resource_unloader(void)
{
    UnloadTexture(null_txt);
    UnloadTexture(projects_icon);
    UnloadTexture(learn_icon);
    UnloadTexture(settings_icon);
    return UnloadFont(font);
}

// ==================================================
// DRAW FUNCTIONS
// ==================================================

// FUNKCJA RYSUJĄCA KWADRAT/PROSTOKĄT
/**
 * @brief PARAMETRY FUNKCJI "Engine_draw_rectangle_shape"
 * @param pos_x pozycja koła w osi x
 * @param pos_y pozycja koła w osi y
 * @param size_x wielkość koła w osi x
 * @param size_y wielkość koła w osi y
 * @param color kolor koła
 */
void Engine_draw_rectangle_shape(const float pos_x, const float pos_y, const float size_x, const float size_y, const Color color)
{
    DrawRectangle(pos_x, pos_y, size_x, size_y, color);
}

// FUNKCJA RYSUJĄCA KOŁA
/**
 * @brief PARAMETRY FUNKCJI "Engine_draw_circle_shape"
 * @param pos_x pozycja koła w osi x
 * @param pos_y pozycja koła w osi y
 * @param radius wielkość koła
 * @param color kolor koła
 */
void Engine_draw_circle_shape(const float pos_x, const float pos_y, const float radius, const Color color)
{
    DrawCircle(pos_x, pos_y, radius, color);
}

// FUNKCJA RYSUJĄCA ELIPSY
/**
 * @brief PARAMETRY FUNKCJI "Engine_draw_ellipse_shape"
 * @param pos_x pozycja koła w osi x
 * @param pos_y pozycja koła w osi y
 * @param radius_x wielkość koła w osi x
 * @param radius_y wielkość koła w osi y
 * @param color kolor koła
 */
void Engine_draw_ellipse_shape(const float pos_x, const float pos_y, const float radius_x, const float radius_y, const Color color)
{
    DrawEllipse(pos_x, pos_y, radius_x, radius_y, color);
}

// FUNKCJA RYSUJĄCA TEKSTURE
/**
 * @brief PARAMETRY FUNKCJI "Engine_draw_rectangle_shape_with_texture"
 * @param texture tekstura
 * @param pos_x pozycja tekstury w osi x
 * @param pos_y pozycja tekstury w osi y
 * @param size_x wielkość tekstury w osi x
 * @param size_y wielkość tekstury w osi y
 * @param rotation obrót tekstury
 * @param color kolor tekstury
 */
void Engine_draw_rectangle_shape_with_texture(const Texture2D texture, const float pos_x, const float pos_y, const float size_x, const float size_y, float rotation, const Color color)
{
    Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle destRec = { pos_x, pos_y, size_x, size_y };
    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(texture, sourceRec, destRec, origin, rotation, color);
}

// FUNKCJA RYSUJĄCA TEKST
/**
 * @brief PARAMETRY FUNKCJI "draw text"
 * @param text <b>wyświetlany tekst</b>
 * @param pos_x pozycja tekstu w osi x
 * @param pos_y pozycja tekstu w osi y
 * @param font_size wielkość tekstu
 * @param color kolor tekstu
 */
void Engine_draw_text(const char text[], const float pos_x, const float pos_y, const float font_size, const Color color)
{
    DrawText(text, pos_x, pos_y, font_size, color);
}

// FUNKCJA RYSUJĄCA LEPSZY TEKST
/**
 * @brief PARAMETRY FUNKCJI "draw text"
 * @param font czcionka tekstu
 * @param text wyświetlany tekst
 * @param text_position pozycja tekstu > przykład: (Vector2){x, y}
 * @param text_origin punkt centralny tekstu > przykład: (Vector2){x, y}
 * @param rotation obrót tekstu
 * @param font_size wielkość tekstu
 * @param spacing odstępy między literami
 * @param color kolor tekstu
 */
void Engine_draw_text_better(const Font font, const char text[], const Vector2 text_position, const Vector2 text_origin, const float rotation, const float font_size, const float spacing, const Color color)
{
    DrawTextPro(font, text, text_position, text_origin, rotation, font_size, spacing, color);
}
