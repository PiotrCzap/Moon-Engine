#include "main.hpp"
#include "raygui.h"

int tabs = 0;

void Projects_tab()
{
    tabs = 1;
}

void Learn_tab()
{
    tabs = 2;
}

void Settings_window()
{
    tabs = 3;
}



void Project_window(void)
{
    Engine_draw_rectangle_shape(0.0f, 0.0f, 800.0f, 600.0f, GRAY_COLOR);
    Engine_draw_rectangle_shape(0.0f, 0.0f, 256.0f, 600.0f, DARK_GRAY_COLOR);

    // texts

    Engine_draw_text_better(font, ENGINE_NAME, (Vector2){10.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 32.0f, 2.0f, WHITE);
    Engine_draw_text_better(font, ENGINE_VERSION, (Vector2){10.0f, 580.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 16.0f, 2.0f, WHITE);

    // Buttons

    //Engine_button(Projects_tab, "PROJECTS", 15.0f, 60.0f, 70.0f, 70.0f, 200.0f, 40.0f);
    //Engine_button(Learn_tab, "LEARN", 15.0f, 120.0f, 60.0f, 130.0f, 200.0f, 40.0f);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL,  0xFFFFFFFF);
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, 0xFFFFFFFF);
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, 0xFFFFFFFF);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    GuiSetStyle(BUTTON, TEXT_PADDING, 10);
    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, 0);
    GuiSetStyle(BUTTON, BORDER_WIDTH, 0);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL,  0x323232FF);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0x3C3C3CFF);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0x1E1E1EFF);
    GuiSetFont(font);
    if (GuiButton((Rectangle){15.0f, 60.0f, 190.0f, 40.0f}, "   PROJECTS")) { Projects_tab(); }
    if (GuiButton((Rectangle){15.0f, 120.0f, 190.0f, 40.0f}, "LEARN   ")) { Learn_tab(); }
    if (GuiButton((Rectangle){15.0f, 180.0f, 190.0f, 40.0f}, "  SETTINGS ")) { Settings_window(); }

    
    

    Engine_draw_rectangle_shape_with_texture(projects_icon, 25.0f, 65.0f, 30.0f, 30.0f, 0.0f, WHITE);
    Engine_draw_rectangle_shape_with_texture(learn_icon, 25.0f, 124.0f, 30.0f, 30.0f, 0.0f, WHITE);
    Engine_draw_rectangle_shape_with_texture(settings_icon, 20.0f, 180.0f, 40.0f, 40.0f, 0.0f, WHITE);
    
    
    // Projects Tab
    if (tabs == 1)
    {
        Engine_draw_rectangle_shape(250.0f, 0.0f, 800.0f, 600.0f, DARKER_GRAY_COLOR);
        Engine_draw_text_better(font, "PROJECTS", (Vector2){260.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 32.0f, 2.0f, WHITE);
        if (GuiButton((Rectangle){590.0f, 10.0f, 190.0f, 40.0f}, "NEW PROJECT")) 
        {
            Learn_tab(); 
        }   
    }

    // Learn Tab
    if (tabs == 2)
    {
        Engine_draw_rectangle_shape(250.0f, 0.0f, 800.0f, 600.0f, DARKER_GRAY_COLOR);
        Engine_draw_text_better(font, "LEARN", (Vector2){260.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 32.0f, 2.0f, WHITE);
    }

    // Settings Tab
    if (tabs == 3)
    {
        Engine_draw_rectangle_shape(250.0f, 0.0f, 800.0f, 600.0f, DARKER_GRAY_COLOR);
        Engine_draw_text_better(font, "SETTINGS", (Vector2){260.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 32.0f, 2.0f, WHITE);
        Engine_draw_text_better(font, "FONT", (Vector2){300.0f, 50.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 32.0f, 2.0f, WHITE);

        static int currentDropdownItem = 0;
        static bool dropdownEditMode = false;

        GuiSetStyle(DEFAULT, BACKGROUND_COLOR, 0x282828FF);
        

        GuiSetStyle(DROPDOWNBOX, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
        GuiSetStyle(DROPDOWNBOX, BASE_COLOR_NORMAL, 0x323232FF);
        GuiSetStyle(DROPDOWNBOX, TEXT_COLOR_FOCUSED, ColorToInt(WHITE));
        GuiSetStyle(DROPDOWNBOX, BASE_COLOR_PRESSED, 0x1E1E1EFF);
        GuiSetStyle(DROPDOWNBOX, BASE_COLOR_FOCUSED, 0x3C3C3CFF);
        GuiSetStyle(DROPDOWNBOX, BORDER_WIDTH, 0);
        GuiSetStyle(DROPDOWNBOX, TEXT_SIZE, 8);
        GuiSetStyle(DROPDOWNBOX, TEXT_PADDING, 3);
        GuiSetStyle(LISTVIEW, BORDER_WIDTH, 0);
        


        if (GuiDropdownBox((Rectangle){ 400.0f, 50.0f, 190.0f, 30.0f }, "sound wave;super jello;Russo_One;Roboto-Black;Quicksilver;Peace Sans;moon_get-Heavy;CODE Bold;BebasNeue", &currentDropdownItem, dropdownEditMode)) {
            dropdownEditMode = !dropdownEditMode;

            Font oldFont = font;
            bool fontLoaded = true;

            switch (currentDropdownItem) {
                case 0:
                    font = LoadFont("src/Engine Data/fonts/Super Jello.ttf");
                    break;
                case 1:
                    font = LoadFont("src/Engine Data/fonts/SoundWave-Regular.ttf");
                    break;
                case 2:
                    font = LoadFont("src/Engine Data/fonts/Russo_One.ttf");
                    break;
                case 3:
                    font = LoadFont("src/Engine Data/fonts/Roboto-Black.ttf");
                    break;
                 case 4:
                    font = LoadFont("src/Engine Data/fonts/Quicksilver.ttf");
                    break;
                case 5:
                    font = LoadFont("src/Engine Data/fonts/Peace Sans.otf");
                    break;
                case 6:
                    font = LoadFont("src/Engine Data/fonts/moon_get-Heavy.ttf");
                    break;
                case 7:
                    font = LoadFont("src/Engine Data/fonts/CODE Bold.otf");
                    break;
                case 8:
                    font = LoadFont("src/Engine Data/fonts/BebasNeue-Regular.ttf");
                    break;
                default:
                    fontLoaded = false;
                    break;
            }
        
            if (fontLoaded) {
                UnloadFont(oldFont);
            }
        }
    }
}