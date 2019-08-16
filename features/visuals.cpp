/*  visuals.cpp
 *
 *
 */
#include "common.h"
#include "visuals.h"
#include "renderer.h"
#include "ragebot.h" // g_rage->get_target();

visuals_t* g_visuals = new visuals_t;

/*
 *
 *
 */
static void draw_esp_box(player_box_t box, color_t color)
{
    g_render->draw_box(box.x - 1, box.y - 1, box.w + 2, box.h + 2, color_t::black);
    g_render->draw_box(box.x + 1, box.y + 1, box.w - 2, box.h - 2, color_t::black);
    g_render->draw_box(box.x, box.y, box.w, box.h, color);
}

/*
 *  draw_health_bar
 *
 */
static void draw_heath_bar(player_box_t box, int value, color_t color)
{
    value = util_clamp(value, 0, 100);
    
    int fill = box.h - (box.h * value) / 100;
    
    g_render->draw_box_filled(box.x - 5, box.y - 1, 3, box.h + 2, color_t(0, 0, 0, 120));
    g_render->draw_box_filled(box.x - 5, box.y + fill - 1, 3, box.h - fill + 2, color);
    g_render->draw_box(box.x - 5, box.y - 1, 3, box.h + 2, color_t(0, 0, 0, 200));
}

/*
 *
 *
 */
static void draw_bottom_bar(player_box_t box, int value, int max, color_t color)
{
    value = util_clamp(value, 0, max);
    
    int fill = box.w - (box.w * value) / 100;
    
    g_render->draw_box_filled(box.x, box.y + box.h + 2, box.w, 3, color_t(0, 0, 0, 120));
    g_render->draw_box_filled(box.x, box.y + box.h + 2, box.w + fill - 1, 3, color);
    g_render->draw_box(box.x, box.y + box.h + 2, box.w + 2, 3, color_t(0, 0, 0, 200));
}



/*
 *
 *
 */
static void draw_offscreen(player_t* player)
{
    // todo
}

/*
 *
 *
 */
static void draw_bomb_timer(planted_c4_t* bomb)
{
    if(set.visuals.other.bomb_timer)
        return;
    
    float flBlow  = bomb->get_blow_time();
          flBlow -= g_globals->m_interval_per_tick * global::local->get_tick_base();
    
    int screenx = set.screen.w, screeny = set.screen.h;
    
    screenx = screenx / 2;
    screeny = screeny - 100;
    
    if (flBlow <= 0.0)
        flBlow = 0.0;
    
    if (flBlow < 40.f)
    {
        float ptc = flBlow / 40.f;
        
        g_render->draw_box_filled(screenx - 150, screeny - 4, 300, 8, color_t(0, 0, 0, 110));
        g_render->draw_box_filled(screenx - 150, screeny - 4, 300 * ptc, 8, color_t(194, 244, 66, 110));
        
        if(flBlow > 5.f)
            g_render->draw_box_filled(screenx - 150, screeny - 4, 300 * 0.125f, 8, color_t(27, 120, 214, 110));
        else
            g_render->draw_box_filled(screenx - 150, screeny - 4, 300 * ptc, 8, color_t(27, 120, 214, 110));
        
        g_render->draw_box_filled(screenx - 150, screeny - 4, 300, 8, color_t(0, 0, 0, 110));
        
        char buf[16];
        sprintf(buf, "%.1f", flBlow);
        std::string str = buf;
        
        auto ts = g_render->get_text_size(renderer_t::verdana12, str);
        
        g_render->draw_string(screenx - ts.x / 2, screeny - ts.y / 2 - 15, renderer_t::verdana12, str, color_t(255, 255, 255, 110));
        
        if(bomb->get_defuser() > 0)
        {
            float flCountdown = bomb->get_defuse_countdown() - (global::local->get_tick_base() * g_globals->m_interval_per_tick);
            
            float ptc2 = flCountdown / 10;
            
            char buf2[16];
            sprintf(buf2, "%.1f", flBlow);
            str = buf2;
            
            g_render->draw_box_filled(screenx - 150, screeny - 4 + 30, 300, 8, color_t(0, 0, 0, 110));
            g_render->draw_box_filled(screenx - 150, screeny - 4 + 30, 300 * ptc2, 8, color_t(84, 169, 255, 110));
            g_render->draw_box_filled(screenx - 150, screeny - 4 + 30, 300, 8, color_t(0, 0, 0, 110));
            
            ts = g_render->get_text_size(renderer_t::verdana12, str);
            
            g_render->draw_string(screenx - ts.x / 2, screeny - ts.y / 2 - 15 + 30, renderer_t::verdana12, str, color_t(84, 169, 255, 110));
            
            if (flCountdown > flBlow)
            {
                str = "cant be defused";
                ts  = g_render->get_text_size(renderer_t::verdana12, str);
                
                g_render->draw_string(screenx - ts.x / 2, screeny - ts.y / 2 - 15 + 60, renderer_t::verdana12, str, color_t(255,48,79,110));
            }
        }
    }
}

/*
 *
 *
 */
void visuals_t::remove_flash()
{
    // todo : if !alive then get the player we spectating
    if(!global::local || !global::local->is_alive())
        return;
    
    static float last_val = set.visuals.other.flash_alpha;
    
    // only do all this when the value has been changed
    if(last_val != set.visuals.other.flash_alpha)
    {
        float step = 255.f / 100.f;
        float alpha = (float)set.visuals.other.flash_alpha * step;
        
        *global::local->get_flash_alpha() = alpha;
        
        last_val = set.visuals.other.flash_alpha;
    }
}

/*
 *
 *  Changes to wireframe
 */
void visuals_t::remove_smoke()
{
    static const std::vector<const char*> smoke_mats =
    {
        "particle/vistasmokev1/vistasmokev1_fire",
        "particle/vistasmokev1/vistasmokev1_smokegrenade",
        "particle/vistasmokev1/vistasmokev1_emods",
        "particle/vistasmokev1/vistasmokev1_emods_impactdust",
    };

    // FRAME_NET_UPDATE_POSTDATAUPDATE_END
    
    static bool last_val = set.visuals.other.remove_smoke;
    
    if(last_val != set.visuals.other.remove_smoke)
    {
        if(set.visuals.other.remove_smoke)
        {
            for (auto mat_name : smoke_mats)
            {
                material_t* mat = g_mat_system->find_material(mat_name, TEXTURE_GROUP_OTHER);
                mat->set_material_var_flag(MATERIAL_VAR_WIREFRAME, set.visuals.other.remove_smoke);
            }
        }
        else
        {
            for (auto mat_name : smoke_mats)
            {
                material_t* mat = g_mat_system->find_material(mat_name, TEXTURE_GROUP_OTHER);
                mat->set_material_var_flag(MATERIAL_VAR_WIREFRAME, false);
            }
        }
        
        last_val = set.visuals.other.remove_smoke;
    }
}

/*
 *
 *
 */
void visuals_t::draw_player_esp()
{
    if(!global::local)
        return;
    
    for(int i = 1; i < g_globals->m_max_clients; i++)
    {
        player_t* player = (player_t*)g_ent_list->get_entity(i);

        if(!player)
            continue;

        if(!player->is_player())
            continue;
        
        if(!player->is_alive())
            continue;
        
        int team = player->get_team();
        
        // if not an actual player then
        if(team != TEAM_TERRORIST && team != TEAM_COUNTER_TERRORIST)
            continue;
        
        // esp fade in/out
        {
            float& alpha = m_player_alpha.at(i);
            alpha = util_clamp(alpha, 0.f, 255.f);
            
            if(player->is_dormant())
            {
                // no alpha so dont draw
                if(alpha <= 0)
                    continue;
                // got alpha so decrease
                if(alpha > 0)
                    alpha -= 7.f;
            }
            else // not dormant
            {
                // not full so increase
                if(alpha < 255)
                    alpha += 15.f;
            }            
        }
        
        int my_team = global::local->get_team();
        
        if(set.visuals.team_flags == 0 && my_team == team)
            continue;
        else if(set.visuals.team_flags == 1 && my_team != team)
            continue;
        // else if == 2 draw all
        
        // todo
        // if(set.visuals.player.radar)
        //    *player->get_spotted() = true;
        
        // todo
        // if(set.visuals.player.offscreen)
        //    draw_offscreen(player);
        
        // only how visible players?
        if(set.visuals.visible && !util_is_player_visible(player))
            continue;
        
        player_box_t box = get_player_box(player);
        
        if(!box.valid)
            continue;
        
        color_t box_col  = set.colors.players.box.to_color();
        box_col.set_a(m_player_alpha.at(i));
        
        color_t white = color_t(255, 255, 255, m_player_alpha.at(i));
        
        player_info_t info;
        g_engine->get_player_info(i, &info);
        
        // draw bounding box
        if(set.visuals.player.box)
            draw_esp_box(box, box_col);
        
        // draw name on top
        if(set.visuals.player.name)
            g_render->draw_string(box.x + (box.w / 2), box.y - 15, renderer_t::verdana12, info.name, white, true);
        
        if(set.visuals.player.health)
            draw_heath_bar(box, player->get_health(), color_t::green);
        
        if(set.visuals.player.bot_bar)
        {
            int value = 0;
            int max   = 100;
            
            switch(set.visuals.player.bot_bar)
            {
                case 1:
                    value = player->get_armor();
                    break;
                case 2:
                    auto weapon   = player->get_weapon();
                    if(weapon)
                    {
                        value    = weapon->get_ammo();
                        max      = weapon->get_weapon_info()->m_clip_size;
                    }
                    break;
            }
            
            draw_bottom_bar(box, value, max, color_t::blue);
        }
        
        std::string right_text = "";
        
        if(set.visuals.player.equipment)
        {
            if(player->has_helmet())
                right_text += "H";
            
            if(player->get_armor() > 0)
                right_text += "K";
            
            // if(player->has_defuser())
            //     right_text += "D";
        }
        
        if(!right_text.empty())
            g_render->draw_string(box.x + box.w + 2, box.y, renderer_t::verdana12, right_text, white);
    }
}

/*
 *
 *
 */
void visuals_t::draw_other_esp()
{
    for(int i = 64; i < g_ent_list->get_highest_index(); i++)
    {
        entity_t* entity = g_ent_list->get_entity(i);

        if(!entity)
            continue;

        client_class_t* cc = entity->get_client_class();
        
        if(!cc)
            continue;
        
        if(cc->m_class_id == class_id_t::CPlantedC4)
            draw_bomb_timer((planted_c4_t*)entity);
    }
}
