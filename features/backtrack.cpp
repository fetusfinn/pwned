/*      backtrack.cpp
 *
 *  https://www.unknowncheats.me/forum/counterstrike-global-offensive/352759-properly-backtracking-entity.html
 *
 */
#include "common.h"
#include "renderer.h"
#include "backtrack.h"

c_backtrack g_time_warp;

/*
 *
 *
 */
backtrack_record_t::backtrack_record_t(player_t* player, backtrack_record_t* prev)
{
    if(player)
    {
        m_tick      = g_globals->m_tick_count;
        m_lby       = player->get_lower_body_yaw();
        m_sim_time  = player->get_simulation_time();
        m_origin    = player->get_origin();
        m_head      = get_hitbox_position(player, HITBOX_NECK);
        m_angles    = *player->get_angles();
        m_mins      = player->get_collidable()->obb_min();
        m_maxs      = player->get_collidable()->obb_max();
        
        player->setup_bones(m_matrix, 128, 256);
    }
    
    m_prev = prev;
}

/*
 *
 *
 */
bool backtrack_record_t::is_valid()
{
    net_channel_info_t* net = g_engine->get_net_channel_info();
    
    if(!net)
        return false;
    
    float max_unlag = 0.2f;
    static auto sv_maxunlag = g_cvar->find_var("sv_maxunlag");
    
    if(sv_maxunlag)
        max_unlag = sv_maxunlag->get_float();
    
    // use normal curtime here, we filter using predicted curtime in ragebot
    float curtime = g_globals->m_cur_time;
    
    // correct for latency.
    float correct = net->get_latency(FLOW_OUTGOING) + net->get_latency(FLOW_INCOMING);
    
    // get difference between tick sent by player and the latency tick.
    long c = util_clamp(correct, 0.f, max_unlag) - (curtime - m_sim_time);
    return std::abs(c) <= 0.2f;
}

/*
 *
 *
 */
void c_backtrack::store()
{
    for(int i = 0; i < g_globals->m_max_clients; i++)
    {
        player_t* player = g_ent_list->get_player(i);
        
        if(!player || player == global::local)
            continue;
        
        if(!player->is_player() || player->is_dormant() || player->is_immune())
            continue;
        
        if(player->get_team() == global::local->get_team())
            continue;
        
        if(!player->is_alive())
        {
            reset(i);
            continue;
        }
        
        auto rec = get_records(i);
        
        if(!rec)
            continue;
        
        backtrack_record_t* prev = rec->m_records.empty() ? nullptr : &rec->m_records.at(0);
        
        rec->m_records.push_front(backtrack_record_t(player, prev));
        
        if(rec->m_records.size() > BACKTRACK_MAX_TICKS)
            rec->m_records.resize(BACKTRACK_MAX_TICKS);
    }
}

/*
 *
 *  Gets the best record to backtrack/aim at
 */
bool c_backtrack::get_best_record(player_t* player, backtrack_record_t& best, int hitbox)
{
    if(!player)
        return {};
    
    auto records = get_records(player->get_index());
    
    float best_dist = 9999.f;
    
    for(auto rec : records->m_records)
    {
        if(!rec.is_valid())
            continue;
        
        auto prev = rec.m_prev;
        
        if(!prev)
            continue;
        
        if(set.rage.backtrack)
        {
            // lby update this tick, this is the best record
            if(rec.m_lby != prev->m_lby)
            {
                best = rec;
                break;
            }
        }
        
        // get closest to crosshair
        
        vec3_t point_pos = rec.m_head, screen_pos;
        
        // legitbot, only get visible records
        if(set.legit.backtrack && !set.rage.backtrack)
        {
            if(!util_is_point_visible(point_pos))
                continue;
        }
        
        // not on screen so dont aim at
        if(!world_to_screen(point_pos, screen_pos))
            continue;
        
        float dist = set.screen.mid.dist_to(screen_pos);
        
        if(dist < 0.f)
            dist *= -1;
        
        if(dist < best_dist)
        {
            best_dist = dist;
            best = rec;
        }
    }
    
    return !best.m_origin.is_zero();
}

/*
 *
 *  Restores the given player to the given record
 */
void c_backtrack::restore(player_t* player, const backtrack_record_t& rec)
{
    // only need to add the lerp if we disabling interp
    float lerp_time = 0.f;
    
    global::cmd->m_tick_count = TIME_TO_TICKS(rec.m_sim_time + lerp_time);
    
    *player->get_angles() = rec.m_angles;
    player->get_origin()  = rec.m_origin;
    player->get_collidable()->obb_min() = rec.m_mins;
    player->get_collidable()->obb_max() = rec.m_maxs;
}

/*
 *
 *  Backtracks all players if possible
 */
void c_backtrack::backtrack()
{
    if(!(global::cmd->m_buttons & IN_ATTACK))
        return;
    
    for(int i = 0; i < g_globals->m_max_clients; i++)
    {
        player_t* player = g_ent_list->get_player(i);
        
        if(!player)
            continue;
        
        if(!player->is_player() || !player->is_alive() || player->is_dormant() || player->is_immune())
            continue;
        
        backtrack_record_t rec;
        
        if(!get_best_record(player, rec))
            continue;
        
        restore(player, rec);
    }
}

/*
 *
 *  Draws the backtrack records for the player
 */
void c_backtrack::draw(player_t* player)
{
    auto records = get_records(player->get_index())->m_records;
    
    size_t size = records.size();
    
    if(size < 1)
        return;
    
    skeep("c_backtrack::draw()");
    
    for(int i = -1; i < size; i++)
    {
        if(i < 0)
        {
            vec3_t this_point = get_hitbox_position(player, HITBOX_NECK), this_screen, next_screen;
            
            if(!world_to_screen(this_point, this_screen) || !world_to_screen(records.at(0).m_head, next_screen))
                continue;
            
            g_render->draw_line(this_screen.x, this_screen.y, next_screen.x, next_screen.y, color_t(0, 0, 255, 255));
        }
        else
        {
            if(i + 1 >= size)
                break;
            
            auto this_rec = records.at(i), next_rec = records.at(i + 1);
            color_t col = this_rec.is_valid() ? color_t(0, 0, 255, 255) : color_t(255, 0, 0, 255);
            
            vec3_t this_screen, next_screen;
            
            if(!world_to_screen(this_rec.m_head, this_screen) || !world_to_screen(next_rec.m_head, next_screen))
                continue;
            
            g_render->draw_line(this_screen.x, this_screen.y, next_screen.x, next_screen.y, col);
        }
    }
}
