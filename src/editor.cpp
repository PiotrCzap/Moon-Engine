#include "include/main.hpp"
#include "imgui/imgui.h"
#include "imgui/rlImGui.h"
New_GameObject all_objs[1000];
int count = 0;

bool show_object = false;

void inspector()
{
    Engine_draw_rectangle_shape(0.0f, 0.0f, 300.0f, 700.0f, GRAY_COLOR);
    Engine_draw_text_better(font, "INSPECTOR", (Vector2){10.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 24.0f, 0.0f, WHITE);

    if (selected_object_index >= 0 && selected_object_index < count) 
    {
        GameObject *obj = &all_objs[selected_object_index].data;

        // imgui window
        ImGui::SetNextWindowPos(ImVec2(10.0f, 45.0f));
        ImVec2 contentSize = ImVec2(300.0f, 650.0f);
        ImGui::SetNextWindowSize(contentSize);
        
        // imgui styles

        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.35f, 0.35f, 0.35f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

        ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
        
        // object name
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "Object: object_%d", selected_object_index + 1);
        ImGui::Text("%s", buffer);
        ImGui::Spacing();

        ImGui::Text("Name");
        ImGui::InputText("##ObjectName", obj->name, sizeof(obj->name));
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        // object position x
        ImGui::Text("Position X");
        ImGui::DragFloat("##PosX", &obj->transform.pos_x, 1.0f, -10000.0f, 10000.0f, "%.1f");

        // object position y
        ImGui::Text("Position Y");
        ImGui::DragFloat("##PosY", &obj->transform.pos_y, 1.0f, -10000.0f, 10000.0f, "%.1f");

        // object size x
        ImGui::Spacing();
        ImGui::Text("Width");
        ImGui::DragFloat("##Width", &obj->transform.size_x, 1.0f, 1.0f, 5000.0f, "%.1f");

        // object size y
        ImGui::Text("Height");
        ImGui::DragFloat("##Height", &obj->transform.size_y, 1.0f, 1.0f, 5000.0f, "%.1f");

        ImGui::PopStyleColor(4);

        ImGui::End();
    }
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
    
    // styles
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
    
    // ==========================================
    // ADD BUTTON AND OBJECT CREATEING
    // ==========================================
    static double last_click_time = 0.0;
    
    if (GuiButton((Rectangle){1660.0f, 40.0f, 50.0f, 25.0f}, "ADD")) 
    {
        double current_time = GetTime();
        
        if (current_time - last_click_time > 0.10)
        {
            last_click_time = current_time;
            
            if (count < 1000) 
            {
                int objects_per_row = 5;
                float spacing = 110.0f;
                
                int row = count / objects_per_row;
                int col = count % objects_per_row;

                float start_spawn_x = 800.0f; 
                float start_spawn_y = 300.0f; 

                float pos_x = start_spawn_x + (col * spacing);
                float pos_y = start_spawn_y + (row * spacing);
                
                // Creates object
                all_objs[count].data = (GameObject){
                    "object_", 
                    false, 
                    {pos_x, pos_y, 100.0f, 100.0f, 0.0f}, 
                    {null_txt, WHITE, 1}, 
                    {0}
                };
                
                snprintf(all_objs[count].data.name, sizeof(all_objs[count].data.name), "object_%d", count + 1);
                count++;
            }
        }
    }

    // ===========================================
    // STRONICOWANIE and SCROLLING
    // ==========================================
    static int page_offset = 0;
    const int items_per_page = 34;
    const float start_y = 80.0f; 
    float item_height = 16.0f;

    static int dragged_index = -1; 

    Rectangle panelRect = {1650.0f, 0.0f, 300.0f, 700.0f};
    Vector2 mousePos = GetMousePosition();
    
    if (CheckCollisionPointRec(mousePos, panelRect))
    {
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            page_offset -= (int)wheel * items_per_page;
            if (page_offset < 0) page_offset = 0;
            if (page_offset >= count && count > 0)
            {
                page_offset = ((count - 1) / items_per_page) * items_per_page;
            }
        }
    }

    // ==========================================
    // DRAG & DROP
    // ==========================================
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        if (dragged_index != -1)
        {
            for (int i = 0; i < items_per_page; i++)
            {
                int global_index = page_offset + i;
                if (global_index >= count) break;
                
                float c_y = start_y + (i * (item_height + 2.0f));
                Rectangle targetRect = {1660.0f, c_y, 280.0f, item_height};
                
                if (CheckCollisionPointRec(mousePos, targetRect) && dragged_index != global_index)
                {
                    New_GameObject temp = all_objs[dragged_index];
                    all_objs[dragged_index] = all_objs[global_index];
                    all_objs[global_index] = temp;

                    if (selected_object_index == dragged_index) {
                        selected_object_index = global_index;
                    } else if (selected_object_index == global_index) {
                        selected_object_index = dragged_index;
                    }
                    break;
                }
            }
            dragged_index = -1;
        }
    }

    // ==========================================
    // hierarchy rows
    // ==========================================
    int drop_indicator_index = -1;
    bool insert_below = false;

    for (int i = 0; i < items_per_page; i++)
    {
        int global_index = page_offset + i;
        if (global_index >= count) break; 

        float current_y = start_y + (i * (item_height + 2.0f));
        Rectangle itemRect = {1660.0f, current_y, 280.0f, item_height};
        bool hovered = CheckCollisionPointRec(mousePos, itemRect);

        if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            selected_object_index = global_index;
            dragged_index = global_index; 
        }

        if (dragged_index != -1 && hovered)
        {
            drop_indicator_index = global_index;
            if (mousePos.y > (current_y + item_height / 2.0f)) {
                insert_below = true;
            } else {
                insert_below = false;
            }
        }

        // colored rows
        Color rowColor;
        if (dragged_index == global_index) {
            rowColor = (Color){ 70, 70, 90, 150 };
        } else if (hovered) {
            rowColor = (Color){ 60, 60, 60, 255 };
        } else {
            rowColor = (Color){ 42, 42, 42, 255 };
        }

        Engine_draw_rectangle_shape(itemRect.x, itemRect.y, itemRect.width, itemRect.height, rowColor);

        char name_buffer[128];
        snprintf(name_buffer, sizeof(name_buffer), "%s", all_objs[global_index].data.name);
        Engine_draw_text_better(font, name_buffer, (Vector2){itemRect.x + 16.0f, itemRect.y + 2.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 12.0f, 0.0f, WHITE);
    }

    // ==========================================
    // VISUALIZATION (drag line and floating name)
    // ==========================================
    if (dragged_index != -1)
    {
        if (drop_indicator_index != -1)
        {
            int relative_i = drop_indicator_index - page_offset;
            if (relative_i >= 0 && relative_i < items_per_page)
            {
                float line_y = start_y + (relative_i * (item_height + 2.0f));
                if (insert_below) {
                    line_y += item_height + 2.0f;
                }
                Engine_draw_rectangle_shape(1660.0f, line_y - 1.0f, 280.0f, 2.0f, (Color){ 0, 160, 255, 255 });
            }
        }

        // draws floating name near mouse
        char drag_name[128];

        snprintf(drag_name, sizeof(drag_name), "%s", all_objs[dragged_index].data.name);  
        Vector2 cursor_pos = { mousePos.x + 15.0f, mousePos.y + 10.0f };
        Engine_draw_rectangle_shape(cursor_pos.x - 4.0f, cursor_pos.y - 2.0f, 100.0f, 18.0f, (Color){ 30, 30, 30, 200 });
        Engine_draw_text_better(font, drag_name, cursor_pos, (Vector2){0.0f, 0.0f}, 0.0f, 12.0f, 0.0f, WHITE);
    }
}

void viewport()
{
    Engine_draw_rectangle_shape(300.0f, 0.0f, 1350.0f, 700.0f, BLACK_COLOR);
    Engine_draw_text_better(font, "VIEWPORT", (Vector2){310.0f, 10.0f}, (Vector2){0.0f, 0.0f}, 0.0f, 24.0f, 0.0f, WHITE);

    bool is_something_dragging = false;

    // object dragging
    for (int i = 0; i < count; i++)
    {
        if (all_objs[i].data.isDragging)
        {
            is_something_dragging = true;
            break;
        }
    }

    for (int i = count - 1; i >= 0; i--)
    {
        all_objs[i].Update(is_something_dragging, i);
        all_objs[i].Draw(debug_mode);
    }
}