/*  visuals.cpp
 *
 *
 */
#include "common.h"
#include "visuals.h"
#include "renderer.h"

visuals_t* g_visuals = new visuals_t;

/*
 *
 *
 */
void visuals_t::draw_esp_box(player_box_t box, color_t color)
{
    g_render->draw_box(box.x - 1, box.y - 1, box.w + 2, box.h + 2, color_t::black);
    g_render->draw_box(box.x + 1, box.y + 1, box.w - 2, box.h - 2, color_t::black);
    g_render->draw_box(box.x, box.y, box.w, box.h, color);
}

/*
 *  draw_health_bar
 *
 */
void visuals_t::draw_heath_bar(player_box_t box, int value, color_t color)
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
void visuals_t::draw_bottom_bar(player_box_t box, int value, int max, color_t color)
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
    
}

/*
 *
 *
 */
static void draw_bomb_timer(planted_c4_t* bomb)
{
    float blow = bomb->get_blow_time();
    blow -= g_globals->m_interval_per_tick * global::local->get_tick_base();
    
    int screenx = set.screen.w / 2;
    int screeny = set.screen.h - 100;
    
    if (blow <= 0.0)
        blow = 0.0;
    
    if (blow < 40.f)
    {
        float ptc = blow / 40.f;
        
        g_render->draw_box_filled(screenx - 150, screeny - 4, 300, 8, color_t(0, 0, 0, 110.f));
        g_render->draw_box_filled(screenx - 150, screeny - 4, 300 + (300 * ptc), 8, color_t(194.f, 244.f, 66.f, 110.f));
        
        if (blow > 5.f)
            g_render->draw_box_filled(screenx - 150, screeny - 4, 300 + (300 * 0.125), 8, color_t(27.f, 120.f, 214.f, 110.f));
        else
            g_render->draw_box_filled(screenx - 150, screeny - 4, 300 + (300 * ptc), 8, color_t(27.f, 120.f, 214.f, 110.f));
        
        g_render->draw_box_filled(screenx - 150, screeny - 4, 300, 4, color_t(0, 0, 0, 110.f/255.f));
        
        char _buf[16];
        sprintf(_buf, "%.1f", blow);
        
        string str = _buf;
        
        vec2_t tex_size = g_render->get_text_size(renderer_t::verdana12, str);
        
        g_render->draw_string(screenx - tex_size.x / 2, screeny - tex_size.y / 2 - 15, renderer_t::verdana12, str, color_t(255, 255, 255, 110));
        
        if(bomb->get_defuser() > 0)
        {
            float count_down = bomb->get_defuse_countdown() - (global::local->get_tick_base() * g_globals->m_interval_per_tick);
            float ptc2 = count_down / 10;
            
            char _buf[16];
            sprintf(_buf, "%.1f", count_down);
            
            std::string ss = _buf;
            
            g_render->draw_box_filled(screenx - 150, screeny - 4 + 30, 300, 8, color_t(0, 0, 0, 110));
            g_render->draw_box_filled(screenx - 150, screeny - 4 + 30, 300 * ptc2, 8, color_t(84, 169, 255, 110));
            
            g_render->draw_box(screenx - 150, screeny - 4 + 30, 300, 8, color_t(0, 0, 0, 110));
            
            vec2_t ts = g_render->get_text_size(renderer_t::verdana12, ss);
            
            g_render->draw_string(screenx - ts.x / 2, screeny - ts.y, renderer_t::verdana12, ss, color_t(84, 169, 255, 110));
            
            if (count_down > blow)
            {
                std::string cant_defuse = "can't be defused";
                vec2_t _ts = g_render->get_text_size(renderer_t::verdana12, cant_defuse);
                g_render->draw_string(screenx - _ts.x / 2, screeny - _ts.y / 2 - 15 + 60, renderer_t::verdana12, cant_defuse,color_t(255,48,79,110));
            }
        }
    }
}

/*
 *
 *
 */
void visuals_t::draw_player_esp()
{
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
            m_player_alpha.at(i) = util_clamp(m_player_alpha.at(i), 0.f, 255.f);
            
            if(player->is_dormant())
            {
                // no alpha so dont draw
                if(m_player_alpha.at(i) == 0)
                    continue;
                // got alpha so decrease
                if(m_player_alpha.at(i) > 0)
                    m_player_alpha.at(i) -= 10.f;
            }
            else // not dormant
            {
                // not full so increase
                if(m_player_alpha.at(i) < 255)
                    m_player_alpha.at(i) += 20.f;
            }            
        }
        
        int my_team = global::local->get_team();
        
        if(set.visuals.team_flags == 0 && my_team == team)
            continue;
        else if(set.visuals.team_flags == 1 && my_team != team)
            continue;
        // else if == 2 draw all
        
        // todo :
        // if(set.visuals.player.radar)
        //    *player->get_spotted() = true;
        
        // offscreen players
        if(set.visuals.player.offscreen)
            draw_offscreen(player);
        
        // only how visible players?
        if(set.visuals.visible && !util_is_player_visible(player))
            continue;
        
        color_t box_col  = set.colors.players.box;
        player_box_t box = get_player_box(player);
        
        if(!box.valid)
            continue;
        
        box_col.set_a(m_player_alpha.at(i));
        
        player_info_t info;
        g_engine->get_player_info(i, &info);
        
        // draw bounding box
        if(set.visuals.player.box)
            draw_esp_box(box, box_col);
        
        // draw name on top
        if(set.visuals.player.name)
            g_render->draw_string(box.x + (box.w / 2), box.y - 15, renderer_t::verdana12, info.name, color_t(255, 255, 255, m_player_alpha.at(i)));
        
        if(set.visuals.player.health)
            draw_heath_bar(box, player->get_health(), color_t::green);
        
        if(set.visuals.player.bot_bar)
        {
            int value = 0;
            int max   = 100;
            
            switch(set.visuals.player.bot_bar)
            {
                case 1:
                    // value = player->get_armor();
                    break;
                case 2:
                    // weapon   = player->get_weapon();
                    // value    = weapon->get_ammo();
                    // max      = weapon->get_weapon_info()->m_clip_size;
                    break;
            }
            
            draw_bottom_bar(box, value, max, color_t::blue);
        }
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

/*
 void desync(float& angle, const float& old_angle, bool& bSendPacket)
 {
 float side = 1.0f;
 float SpawnTime = 0.0f;
 int max_choke_ticks = 15;
 int latency_ticks = 0;
 float fl_latency = m_engine->get_net_channel_info()->GetLatency(FLOW_OUTGOING);
 int latency = TIME_TO_TICKS(fl_latency);
 if (m_client_state->chokedcommands <= 0) { //its not for yu m8
 latency_ticks = latency;
 }
 else {
 latency_ticks = max(latency, latency_ticks);
 }
 
 if (m_game_rules->valve_ds()) { //its not for yu m8
 if (fl_latency >= m_globals->interval_per_tick)
 max_choke_ticks = 11 - latency_ticks;
 else
 max_choke_ticks = 11;
 }
 else
 {
 max_choke_ticks = 13 - latency_ticks;
 }
 
 auto anim_state = game::localdata.localplayer()->GetAnimState();
 
 if (*(float_t*)((uintptr_t)game::localdata.localplayer() + 0xA360) != SpawnTime) {
    SpawnTime = *(float_t*)((uintptr_t)game::localdata.localplayer() + 0xA360);
 }
 
 /*esketit/ float next_lby = 0.f;
/*esketit/ bool broke_lby = false;

auto fov_to_player = [](vector_t view_offset, q_angle view, i_client_entity* m_entity, int hitbox)
{
    CONST FLOAT MaxDegrees = 180.0f;
    q_angle Angles = view;
    vector_t Origin = view_offset;
    vector_t Delta(0, 0, 0);
    vector_t Forward(0, 0, 0);
    game::math.angle_vectors(Angles, Forward);
    vector_t AimPos = game::functions.get_hitbox_location(m_entity, hitbox);
    game::math.vector_subtract(AimPos, Origin, Delta);
    game::math.normalize(Delta, Delta);
    FLOAT DotProduct = Forward.Dot(Delta);
    return (acos(DotProduct) * (MaxDegrees / PI));
};

int target = -1;
float mfov = 50;

vector_t viewoffset = game::localdata.localplayer()->origin() + game::localdata.localplayer()->GetViewOffset();
q_angle view; m_engine->get_view_angles(view);

for (int i = 0; i <= m_globals->maxClients; i++) {
    i_client_entity* m_entity = m_entity_list->get_client_entity(i);
    
    if (is_viable_target(m_entity)) {
        
        float fov = fov_to_player(viewoffset, view, m_entity, 0);
        if (fov < mfov) {
            mfov = fov;
            target = i;
        }
    }
}

q_angle at_target_angle;

static bool jitter = false;
jitter = !jitter;

if (Menu::Window.AntiAimTab.DesyncAA.GetState()) {
    if (target) {
        auto m_entity = m_entity_list->get_client_entity(target);
        
        vector_t head_pos_screen;
        if (is_viable_target(m_entity) && game::functions.world_to_screen(m_entity->GetHeadPos(), head_pos_screen)) {
            game::math.calculate_angle(game::localdata.localplayer()->origin(), m_entity->origin(), at_target_angle);
            at_target_angle.x = 0;
            
            vector_t src3D, dst3D, forward, right, up, src, dst;
            float back_two, right_two, left_two;
            trace_t tr;
            Ray_t ray, ray2, ray3, ray4, ray5;
            CTraceFilter filter;
            
            const q_angle to_convert = at_target_angle;
            game::math.angle_vectors(to_convert, &forward, &right, &up);
            
            filter.pSkip = game::localdata.localplayer();
            src3D = game::localdata.localplayer()->GetEyePosition();
            dst3D = src3D + (forward * 384); //Might want to experiment with other numbers, incase you don't know what the number does, its how far the trace will go. Lower = shorter.
            
            ray.Init(src3D, dst3D);
            m_trace->TraceRay(ray, MASK_SHOT, &filter, &tr);
            back_two = (tr.endpos - tr.startpos).Length();
            
            ray2.Init(src3D + right * 35, dst3D + right * 35);
            m_trace->TraceRay(ray2, MASK_SHOT, &filter, &tr);
            right_two = (tr.endpos - tr.startpos).Length();
            
            ray3.Init(src3D - right * 35, dst3D - right * 35);
            m_trace->TraceRay(ray3, MASK_SHOT, &filter, &tr);
            left_two = (tr.endpos - tr.startpos).Length();
            
            if (left_two > right_two) {
                side = 1;
            }
            else if (right_two > left_two) {
                side = -1;
            }
            
            if (std::fabsf(*(float_t*)((uintptr_t)game::localdata.localplayer() + 0xA360) - m_globals->curtime) > 1.0f) {
                if (Menu::Window.AntiAimTab.DesynCtPYE.GetIndex() == 1) { //balance
                    float minimal_move = 2.0f;
                    if (game::localdata.localplayer()->getflags() & FL_DUCKING)
                        minimal_move *= 3.f;
                        
                        if (game::globals.UserCmd->buttons & IN_WALK)
                            minimal_move *= 3.f;
                            
                            bool should_move = game::localdata.localplayer()->velocity().Length2D() <= 0.0f
                            || std::fabsf(game::localdata.localplayer()->velocity().z) <= 100.0f;
                            
                            if ((game::globals.UserCmd->command_number % 2) == 1) {
                                angle += 120.0f * side;
                                if (should_move)
                                    game::globals.UserCmd->sidemove -= minimal_move;
                                    bSendPacket = false;
                                    }
                            else if (should_move) {
                                game::globals.UserCmd->sidemove += minimal_move;
                            }
                }
                if (Menu::Window.AntiAimTab.DesynCtPYE.GetIndex() == 0) { //static
                    if (next_lby >= m_globals->curtime) {
                        if (!broke_lby && bSendPacket && m_client_state->chokedcommands > 0)
                            return;
                        
                        broke_lby = false;
                        bSendPacket = false;
                        angle += 120.0f * side;
                    }
                    else {
                        broke_lby = true;
                        bSendPacket = false;
                        angle += 120.0f * -side;
                    }
                }
            }
            
            angle = std::remainderf(angle, 360.0f);
            
            if (m_client_state->chokedcommands >= max_choke_ticks) {
                bSendPacket = true;
            }
            
            if (anim_state) {
                IAnimState anim_state_backup = *anim_state;
                *(q_angle*)((uintptr_t)game::localdata.localplayer() + UTILS::netvar_hook_manager.GetOffset("DT_BasePlayer", "deadflag") + 0x4) = game::globals.UserCmd->viewangles;
                //game::localdata.localplayer()->update_anims();
                
                if (anim_state->speed_2d > 0.1f || std::fabsf(anim_state->flUpVelocity)) { //SetupVelocity
                    next_lby = m_globals->curtime + 0.22f;
                }
                else if (m_globals->curtime > next_lby) {
                    if (std::fabsf(game::math.angle_diff(anim_state->m_flGoalFeetYaw, anim_state->m_flEyeYaw)) > 35.0f) {
                        next_lby = m_globals->curtime + 1.1f;
                    }
                }
                
                *anim_state = anim_state_backup;
            }
            
            
        }
        else {
            angle -= jitter ? 180 : 0;
        }
    }
}
if (Menu::Window.AntiAimTab.DesyncAA.GetState() && Menu::Window.AntiAimTab.DesynCtPYE.GetIndex() == 2) { //legit
    if (bSendPacket && !m_engine->get_net_channel_info()->chokedPackets)
        bSendPacket = false;
        
        if (bSendPacket && m_engine->get_net_channel_info()->chokedPackets && !(game::globals.UserCmd->buttons & (IN_ATTACK | IN_ATTACK2))) {
            auto absMaxDesyncAngle = fabsf(m_entity_list->get_client_entity(m_engine->GetLocalPlayer())->get_max_desync_delta());
            if (angle - old_angle == 0.0f)
                angle += absMaxDesyncAngle;
                else
                    angle = old_angle + clamp(angle - old_angle, -absMaxDesyncAngle, absMaxDesyncAngle);
                    }
}

}
*/
