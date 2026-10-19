#include <stdio.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Color background = {50u, 50u, 50u, 255u};
Color dark_background = {40u, 40u, 40u, 255u};
Color darker_background = {30u, 30u, 30u, 255u};
Color darkers_background = {25u, 25u, 25u, 255u};

void bar(void)
{
    int position_x = 5;
    int position_y = 5;
    int size_x = 255;
    int size_y = 592;
    DrawRectangle(position_x, position_y, size_x, size_y, dark_background);

    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL,    ColorToInt(dark_background));
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
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    Rectangle button = { 915 - 572, 827 - 242, 90, 25 };

    if (GuiButton(button, "Close"))
    {
        exit(0);
    }
    
}

void Settings_Window(void)
{
    SetConfigFlags(FLAG_WINDOW_TOPMOST);
    InitWindow(776, 612, "Settings");
    SetWindowPosition(572, 242);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(background);
        bar();
        EndDrawing();
    }
    CloseWindow();
    
    
}

int main()
{
    Settings_Window();
}