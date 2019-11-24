/*  paint_traverse.cpp
 *
 *
 */
#include "common.h"
#include "renderer.h"
#include "visuals.h"
#include "notifications.h"
#include "backtrack.h" // need for legitbot.h
#include "legitbot.h"
#include "skinchanger.h"

void paint_traverse_hook(void* thisptr, VPANEL panel, bool repaint, bool allow_force)
{
    print_hook();
    
    if(set.visuals.other.remove_scope && !strcmp(g_panel->get_name(panel), "HudZoom"))
        return;
    
    panel_vmt->get_original_method<paint_traverse_fn>(INDEX_PAINT_TRAVERSE)(thisptr, panel, repaint, allow_force);
    
    static VPANEL focus_panel = 0;
    
    if(!focus_panel)
    {
        if(strstr(g_panel->get_name(panel), "FocusOverlayPanel"))
        {
            focus_panel = panel;
            
            renderer_t::verdana12   = g_render->create_font("Verdana Bold", 12, FONTFLAG_DROPSHADOW);
            renderer_t::tahoma12    = g_render->create_font("Tahoma", 11, FONTFLAG_DROPSHADOW, 100);
        }
    }
    
    init_g_item_def_index_map1();
    init_g_item_def_index_map2();
    
    if(panel == focus_panel)
    {
        if(g_engine->is_in_game())
        {
            if(global::_send_packet)
            {
                // draw choked packets
                for(int i = 0; i < 16; i++)
                    g_render->draw_box_filled(10 + (i * 11), 250, 10, 10, color_t(250, 160, 50, (global::choked > i) ? 225 : 100));
            }
            
            // features
            g_visuals->draw_player_esp();
            g_visuals->draw_other_esp();
            g_visuals->draw_hitmarkers();
            g_visuals->draw_scope();
            g_visuals->draw_spectator_list();
            
            vec3_t aim_point = g_legitbot.get_aim_point(), screen;
            
            if(world_to_screen(aim_point, screen))
                g_render->draw_box(screen.x, screen.y, 4, 4, color_t::blue);
        }
        else
        {
            static int  alpha = 0;
            static bool up    = true;
            
            if(up)
                alpha += 3;
            else
                alpha -= 3;
            
            if(alpha > 255)
            {
                alpha = 255;
                up = false;
            }
            else if(alpha < 0)
            {
                alpha = 0;
                up = true;
            }
            
            g_render->draw_string(10, 10, renderer_t::verdana12, "pwned", color_t(230, 40, 240, alpha));
        }
    }
}
