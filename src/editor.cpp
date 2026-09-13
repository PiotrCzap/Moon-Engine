#include "include/main.hpp"

bool show_object = false; // Object is visible

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
    float start_pos = 100.0f;

    Engine_draw_rectangle_shape(1650.0f, 0.0f, 300.0f, 700.0f, GRAY_COLOR);
    Engine_draw_text_better(font, "HIERARCHY", (Vector2){1660.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 24.0f, 0.0f, WHITE);

    // button styles
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

    static bool button_clicked = false;

    if (GuiButton((Rectangle){1660.0f, 40.0f, 50.0f, 25.0f}, "ADD")) {
        if (!button_clicked) 
        {
            if (count < 1000) 
            {
                all_objs[count] = (GameObject){"object_", false, {900.0f, 300.0f, 100.0f, 100.0f, 0.0f}, {null_txt, WHITE, 1}, {0}};
                count++;
            }
            button_clicked = true;
        }
    } 
    else 
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) 
        {
            button_clicked = false;
        }
    }
}

void viewport()
{
    Engine_draw_rectangle_shape(300.0f, 0.0f, 1350.0f, 700.0f, BLACK_COLOR);
    Engine_draw_text_better(font, "VIEWPORT", (Vector2){310.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 24.0f, 0.0f, WHITE);

    for (int i = 0; i < count; i++) 
    {
        Rectangle r = { all_objs[i].transform.pos_x, all_objs[i].transform.pos_y, all_objs[i].transform.size_x, all_objs[i].transform.size_y };

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), r))
            all_objs[i].isDragging = true;

        if (all_objs[i].isDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
        {
            Vector2 d = GetMouseDelta();
            all_objs[i].transform.pos_x += d.x;
            all_objs[i].transform.pos_y += d.y;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            all_objs[i].isDragging = false;

        if (debug_mode)
        {
            Rectangle debugRec = { 
                all_objs[i].transform.pos_x - 2.0f, 
                all_objs[i].transform.pos_y - 2.0f, 
                all_objs[i].transform.size_x + 4.0f, 
                all_objs[i].transform.size_y + 4.0f 
            };
            DrawRectangleLinesEx(debugRec, 2.0f, RED);
        }

        Engine_draw_rectangle_shape_with_texture(
            all_objs[i].sprite_renderer.texture,
            all_objs[i].transform.pos_x, all_objs[i].transform.pos_y,
            all_objs[i].transform.size_x, all_objs[i].transform.size_y,
            all_objs[i].transform.rotation, all_objs[i].sprite_renderer.color
        );
    }
}