/*
 *  menu.h
 */
#include <array>
#include <vector>
#include <string>
#include "imrenderer.h"

enum menu_side_t
{
    side_left  = 0,
    side_right = 1,
};

enum menu_item_type_t
{
    item_checkbox   = 0,
    item_slider     = 1,
    item_combo      = 2,
    item_combo_multi    = 3,
    item_color_picker   = 4,
    item_button     = 5,
};

class menu_t
{
private:
    
    // general vars
    im_renderer_t* draw;
    int x, y, w, h;
    int tab;
    
    // menu item vars
    // 2 = num cols
    std::array<ImVec2, 2> m_offsets;
    menu_side_t m_side;
    int m_item_index;
    
    struct
    {
        bool team_flags = false;
        bool hitmarkers = false;
    }opened;
    
private:
    
    void draw_window();
    void draw_tabs();
    void tab_rage();
    void tab_legit();
    void tab_visuals();
    void tab_movement();
    void tab_misc();
    void tab_skins();
    void tab_players();
    
    // controls
    
    void    set_offset(int x, int y);
    ImVec2  get_offset();
    void    reset_offset();
    
    void    set_side(menu_side_t new_side);
    
    ImVec2  add_menu_item(menu_item_type_t item_type);
    void    checkbox(std::string label, bool*   val, bool cancel = false);
    void    slider_i(std::string label, ImVec2 bounds, int*   val, bool cancel = false, std::string suffix = "");
    void    slider_f(std::string label, ImVec2 bounds, float* val, bool cancel = false, std::string suffix = "", int precision = 2);
    void    render_combos();
    void    combo(std::string label, std::vector<std::string> items, int* value, bool* open, bool cancel = false);
    void    combo_multi(std::string label, std::vector<std::string> items, std::vector<bool>* value, bool* open, bool cancel = false);
    // todo : button
    bool    button(std::string label, bool* val = nullptr);
    
public:
    
    menu_t();
    
    // functions
    
    void render();
    void move();
    
public:
    
    // variables
    
};
