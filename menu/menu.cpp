/*      menu.cpp
 *
 *
 */
#include "common.h"
#include "menu.h"

namespace
{
    ImColor col_background(14, 14, 14, 255), col_border1(70, 70, 70, 255), col_border2(41, 42, 42, 255);
}

menu_t::menu_t()
{
    draw = new im_renderer_t();
    
    draw->init_fonts();
    
    x = y = 100;
    w = 500;
    h = 400;
    tab = 2;
    
    reset_offset();
}

void menu_t::render()
{
    draw->start();
    
    draw_window();
    draw_tabs();
    reset_offset();
    
    draw->finish();
}

void menu_t::move()
{
    bool down = ImGui::GetIO().MouseDown[0];
    static std::vector<bool> down_last = {};
    const int magic = 15;
            
    if(draw->in_area(x + 10, y + 10, 125, h - 20) && (down || (down_last.size() > 0 && down_last.size() < magic)))
    {
        ImVec2 delta = ImGui::GetIO().MouseDelta;
        x += delta.x;
        y += delta.y;
    }

    if(down || down_last.size() < magic)
        down_last.push_back(true);
}

void menu_t::draw_window()
{
    // window
    draw->draw_box_outlined(x - 4, y - 4, w + 8, h + 8, 2, col_border1, col_border2);
    draw->draw_box_filled(x, y, w, h, col_background);
    
    // tab box
    draw->draw_box(x + 10, y + 10, 125, h - 20, col_border1);
    
    // controls
    draw->draw_box(x + 10 + 125 + 10, y + 10, 345, h - 20, col_border1);
}

void menu_t::draw_tabs()
{
    const std::vector<std::string> tab_names = {"rage", "legit", "visuals", "movement", "misc", "skins", "players"};
    
    for(int i = 0; i < tab_names.size(); i++)
    {
        ImColor col = ImColor(140, 140, 140, 255);
        
        // if active then use active col
        if(tab == i)
            col = ImColor(157, 209, 70, 255);
            // col = set.menu.color;
        
        // draw label
        draw->draw_string(x + 22, y + 20 + (i * 15), tab_names.at(i).c_str(), Fonts::small, col);
        
        // clickable area
        // draw->draw_box(x + 19, y + 17 + (i * 15), 75, 15, ImColor(255, 0 ,0 ,255));
        
        // change to this tab if clicked
        if(draw->in_area(x + 19, y + 17 + (i * 15), 75, 15) && ImGui::GetIO().MouseClicked[0])
            tab = i;
    }
    
    // render tab accordingly
    
    if(tab == 0)
        tab_rage();
    else if(tab == 1)
        tab_legit();
    else if(tab == 2)
        tab_visuals();
    else if(tab == 3)
        tab_movement();
    else if(tab == 4)
        tab_misc();
    else if(tab == 5)
        tab_skins();
    else if(tab == 6)
        tab_players();
    
    render_combos();
}

void menu_t::tab_rage()
{
    
}

void menu_t::tab_legit()
{
    
}

void menu_t::tab_visuals()
{
    set_side(side_left);
    combo("team flags", {"enemy", "teammates", "all"}, &set.visuals.team_flags, &opened.team_flags);
    checkbox("visible", &set.visuals.visible, opened.team_flags);
    checkbox("box", &set.visuals.player.box, opened.team_flags);
    checkbox("name", &set.visuals.player.name);
    checkbox("health", &set.visuals.player.health);
    
    set_side(side_right);
    combo_multi("hitmarkers", {"crosshair", "sound", "damage"}, &set.visuals.other.hitmarkers, &opened.hitmarkers);
    checkbox("bomb timer", &set.visuals.other.bomb_timer, opened.hitmarkers);
    checkbox("remove smoke", &set.visuals.other.remove_smoke, opened.hitmarkers);
    slider_f("flashbang effect", {0.f, 100.f}, &set.visuals.other.flash_alpha, false, "%", 0);
}

void menu_t::tab_movement()
{
    
}

void menu_t::tab_misc()
{
    set_side(side_left);
    slider_i("override fov", {0, 100}, &set.misc.fov);
    checkbox("remove view punch", &set.misc.remove_view_punch);
    
    set_side(side_right);
}

void menu_t::tab_skins()
{
    
}

void menu_t::tab_players()
{
    
}
