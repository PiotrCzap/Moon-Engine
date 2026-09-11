#include "main.hpp"

void inspector()
{
    Engine_draw_rectangle_shape(0.0f, 0.0f, 300.0f, 700.0f, GRAY_COLOR);
    Engine_draw_text_better(font, "INSPECTOR", (Vector2){10.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 24.0f, 0.0f, WHITE);
}

void file_manager()
{
    Engine_draw_rectangle_shape(0.0f, 700.0f, 1920.0f, 700.0f, DARK_GRAY_COLOR);
    Engine_draw_text_better(font, "FILE MANAGER", (Vector2){10.0f, 710.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 24.0f, 0.0f, WHITE);
}

void hierarchy()
{
    Engine_draw_rectangle_shape(1650.0f, 0.0f, 300.0f, 700.0f, GRAY_COLOR);
    Engine_draw_text_better(font, "HIERARCHY", (Vector2){1660.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 24.0f, 0.0f, WHITE);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL,  0xFFFFFFFF);
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, 0xFFFFFFFF);
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, 0xFFFFFFFF);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 12);
    GuiSetStyle(BUTTON, TEXT_PADDING, 8);
    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, 0);
    GuiSetStyle(BUTTON, BORDER_WIDTH, 0);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL,  ColorToInt(DARK_GRAY_COLOR));
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0x3C3C3CFF);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0x1E1E1EFF);
    GuiSetFont(font);
    if (GuiButton((Rectangle){1660.0f, 40.0f, 50.0f, 25.0f}, "ADD")) {}
}

void viewport()
{
    Engine_draw_rectangle_shape(300.0f, 0.0f, 1350.0f, 700.0f, BLACK_COLOR);
    Engine_draw_text_better(font, "VIEWPORT", (Vector2){310.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 24.0f, 0.0f, WHITE);
}