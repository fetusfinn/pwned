/*
 *  legitbot.cpp
 *  todo : recode
 */
#include "common.h"
#include "backtrack.h"
#include "legitbot.h"

c_legitbot g_legitbot;

std::vector<hitbox_t> c_legitbot::get_target_hitboxes()
{
    std::vector<hitbox_t> hitboxes;
    
    if(set.legit.hitboxes.at(0))
    {
        hitboxes.push_back(HITBOX_HEAD);
        hitboxes.push_back(HITBOX_NECK);
    }
    
    if(set.legit.hitboxes.at(1))
    {
        hitboxes.push_back(HITBOX_CHEST);
        hitboxes.push_back(HITBOX_UPPER_CHEST);
    }
    
    if(set.legit.hitboxes.at(2))
    {
        hitboxes.push_back(HITBOX_PELVIS);
        hitboxes.push_back(HITBOX_BODY);
    }
    
    if(set.legit.hitboxes.at(3))
    {
        hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
        hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
    }
    
    if(set.legit.hitboxes.at(4))
    {
        hitboxes.push_back(HITBOX_LEFT_THIGH);
        hitboxes.push_back(HITBOX_RIGHT_THIGH);
        hitboxes.push_back(HITBOX_LEFT_CALF);
        hitboxes.push_back(HITBOX_RIGHT_CALF);
    }
    
    // nothing selected so just default
    if(hitboxes.empty())
    {
        hitboxes.push_back(HITBOX_HEAD);
        hitboxes.push_back(HITBOX_CHEST);
        hitboxes.push_back(HITBOX_BODY);
        hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
        hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
        hitboxes.push_back(HITBOX_LEFT_CALF);
        hitboxes.push_back(HITBOX_RIGHT_CALF);
    }
    
    return hitboxes;
}

/*
 *
 *  Returns the distance to the hitbox
 */
float c_legitbot::find_closest_hitbox(player_t* player, int& hitbox)
{
    float best_dist = 9999999.f;
    auto  hitboxes = get_target_hitboxes();
    
    for(auto hit : hitboxes)
    {
        if(!util_is_hitbox_visible(player, hit))
            continue;
        
        vec3_t hit_pos = get_hitbox_position(player, hit), screen_pos;
        
        if(!world_to_screen(hit_pos, screen_pos))
            continue;
        
        float dist = set.screen.mid.dist_to(screen_pos);
        if(dist < 0)
            dist *= -1;
        
        if(dist < best_dist)
        {
            best_dist = dist;
            hitbox = hit;
        }
    }
    
    return best_dist;
}

/*
 *
 *
 */
bool c_legitbot::find_target()
{
    // const int reset = 100;
    
    float best_dist = 9999999.f;
    player_t* best_player = nullptr;
    int best_hitbox = -1;
    
    for(int i = 0; i < g_globals->m_max_clients; i++)
    {
        player_t* player = g_ent_list->get_player(i);
        
        if(!player || !player->is_player())
            continue;
        
        if(!player->is_alive() || player->is_dormant() || player->is_immune())
            continue;
        
        int hitbox = -1;
        float dist = find_closest_hitbox(player, hitbox);
        
        if(hitbox < 0)
            continue;
        
        if(dist < best_dist)
        {
            best_dist   = dist;
            best_player = player;
            best_hitbox = hitbox;
        }
    }
    
    m_target = best_player;
    m_hitbox = best_hitbox;
    
    return m_target != nullptr && m_target != global::local && m_hitbox > -1;
}

/*
 *
 *
 */
bool c_legitbot::get_best_record(int index, backtrack_record_t& record)
{
    auto player_records = g_time_warp.get_records(index);
    auto records = player_records->m_records;
    
    records.erase(std::find_if(records.begin(), records.end(), [](backtrack_record_t& record) {
        return !record.is_valid();
    }), records.end());
    
    records.erase(std::unique(records.begin(), records.end(), [](backtrack_record_t& a, backtrack_record_t& b) {
        return (a.m_angles == b.m_angles && a.m_origin == b.m_origin) || a.m_origin.dist_to(b.m_origin) < 15.f;
    }), records.end());
    
    // all the bad records should be gone now
    // so find the closest
    
    float best_dist = 9999999.f;
    
    for(int i = 0; i < records.size(); i++)
    {
        vec3_t head = records.at(i).m_head, screen;
        
        if(!util_is_point_visible(head))
            continue;
        
        if(!world_to_screen(head, screen))
            continue;
        
        float dist = set.screen.mid.dist_to(screen);
        
        if(dist < 0.f)
            dist *= -1;
        
        if(dist > best_dist)
            record = records.at(i);
    }
    
    return record.is_valid();
}

/*
 *
 *
 */
bool c_legitbot::calculate_aim_angle(vec3_t aim_pos)
{
    qangle_t view_angles;
    g_engine->get_view_angles(view_angles);

    // the point that we want to aim at
    // vec3_t aim_pos = vec3_t(0, 0, 0);

    if(aim_pos.is_zero())
        aim_pos = get_hitbox_position(m_target, m_hitbox);

    // todo : prediction

    // extrapolate
    // todo : make better
    //if(!aim_pos.is_zero() && !m_backtrack)
    //    aim_pos += m_target->get_velocity() * g_globals->m_interval_per_tick;

    m_aim_pos = aim_pos;
    m_aim_ang = calculate_angle(global::local->get_eye_position(), aim_pos);
//    m_aim_ang = calc_angle(global::local->get_eye_position(), aim_pos);
    // m_aim_ang.clamp();

    return get_fov(view_angles, m_aim_ang) <= set.legit.fov;
}

/*
 *
 *
 */
void c_legitbot::aim()
{
    qangle_t aim_ang = m_aim_ang;
    qangle_t view_angles;
    g_engine->get_view_angles(view_angles);
    
    // smoothing
    // https://www.unknowncheats.me/forum/c-and-c/151887-doing-better-aim-smoothing.html
    // https://github.com/stevemk14ebr/BF4-AtomBot/blob/47168a85ab4d3311cff8756539740f7c0dd7c52f/BF4%20AtomBot/Hack%20Core/AimbotSmoother.h
    if(set.legit.smooth > 0)
        aim_ang = view_angles + (m_aim_ang - view_angles) / set.legit.smooth;
    
    // when we shoot
    if(global::cmd->m_buttons & IN_ATTACK)
    {
        // backtrack the player
        if(m_backtrack)
            g_time_warp.restore(m_target, m_record);
        
        // then aim at them
        global::cmd->m_view_angles = aim_ang;
        g_engine->set_view_angles(global::cmd->m_view_angles);
    }
}

/*
 *
 *
 */
bool c_legitbot::get_hitbox_positions_from_record(player_t* player, backtrack_record_t& rec, std::vector<vec3_t>& points)
{
    if(!player)
        return {};
    
    studio_hdr_t* hdr = g_model_info->get_studio_model(player->get_model());
    
    if(!hdr)
        return {};
    
    auto hitboxes = get_target_hitboxes();
    
    for(int i = 0; i < hitboxes.size(); i++)
    {
        int h = hitboxes.at(i);
        auto* bbox = hdr->get_hitbox(h, 0);
        
        // philip015's old hack
        float mod = bbox->m_radius != -1.f ? bbox->m_radius : 0.f;
        
        vec3_t max, min;
        vector_transform(bbox->m_bbmin - mod, rec.m_matrix[bbox->m_bone], min);
        vector_transform(bbox->m_bbmax + mod, rec.m_matrix[bbox->m_bone], max);
        auto center = (min + max) / 2.f;
        
        points.push_back(center);
    }
    
    return !points.empty();
}

/*
 *
 *
 */
bool c_legitbot::get_backtrack_point(vec3_t& out)
{
    if(get_best_record(m_target->get_index(), m_record))
    {
        std::vector<vec3_t> hitbox_points;
        
        if(get_hitbox_positions_from_record(m_target, m_record, hitbox_points))
        {
            float best_dist = 99999.f;
            vec3_t best_point = vec3_t(0, 0, 0);
            
            // try find closest point
            for(auto point : hitbox_points)
            {
                vec3_t screen;
                
                if(!world_to_screen(point, screen))
                    continue;
                
                if(!util_is_point_visible(point))
                    continue;
                
                float dist = set.screen.mid.dist_to(screen);
                
                if(dist > best_dist)
                {
                    best_dist = dist;
                    best_point = point;
                }
            }
            
            if(best_point.is_zero())
                return false;
            
            out = best_point;
            
            return true;
        }
    }
    
    return false;
}

/*
 *
 *
 */
void c_legitbot::aimbot()
{
    if(!set.legit.aimbot)
        return;
    
    if(!find_target())
        return;
    
    // m_blacklist = true;
    
    // skeep("aimbot target : " + std::string(util_get_player_info(m_target).name));
    
    if(/* DISABLES CODE */ (false) && set.legit.backtrack)
    {
        if(get_backtrack_point(m_aim_pos))
        {
            m_backtrack = true;
            skeep("got backtrack point");
        }
    }
    else
    {
        m_backtrack = false;
        m_aim_pos = vec3_t(0, 0, 0);
    }
        
    if(!calculate_aim_angle(m_aim_pos))
        return;
    
    // auto shoot
    
    aim();
}

/*
bool get_multipoints(player_t* player, std::vector<int> hitboxes, matrix3x4_t* matrix, std::vector<vec3_t>& points, const std::deque<backtrack_record_t>& sorted_records, size_t record_idx, float scale)
{
    if(!player)
        return false;
    
    studio_hdr_t* studiohdr = g_model_info->get_studio_model(player->get_model());
    
    if(!studiohdr)
        return false;
    
    auto local = global::local;
    
    if(!local)
        return false;
    
    try
    {
        for(size_t idx = 0; idx < hitboxes.size(); ++idx)
        {
            int h = hitboxes.at(idx);
            auto* bbox = studiohdr->get_hitbox(h, 0);
            
            // philip015's old hack
            float mod = bbox->m_radius != -1.f ? bbox->m_radius : 0.f;
            
            vec3_t max, min;
            vector_transform(bbox->m_bbmin - mod, matrix[bbox->m_bone], min);
            vector_transform(bbox->m_bbmax + mod, matrix[bbox->m_bone], max);
            auto center = (min + max) / 2.f;
            
            points.push_back(center);
            
            auto angle = calculate_angle(center, local->get_eye_position());
            
            vec3_t forward;
            angle_vectors(angle, forward);
            
            vec3_t right = forward.cross(vec3_t(0, 0, 1));
            vec3_t left = vec3_t(-right.x, -right.y, right.z);
            
            vec3_t top = vec3_t(0, 0, 1);
            vec3_t bot = vec3_t(0, 0, -1);
            
            // don't bother multipointing if body/head is visible.
            if(g_vars.rage.dynamic_hitbox)
            {
                if(g_cl.m_under_tickrate && m_last_target)
                {
                    // check if we're aiming at the same target and only multipoint this target.
                    if(e != m_last_target)
                    {
                        continue;
                    }
                }
                
                if(hitboxes.empty() || points.empty())
                    return false;
                
                if(points.size() >= hitboxes.size())
                {
                    switch(h)
                    {
                        case head:
                        case neck:
                        case l_chest:
                        case u_chest:
                        case thorax:
                        case pelvis:
                            break;
                        default:
                            continue;
                    }
                    
                    if(e->is_visible( e, local->eye_pos( ), points.at( head ), MASK_SHOT, local) ||
                       e->is_visible( e, local->eye_pos( ), points.at( pelvis ), MASK_SHOT, local))
                        return true;
                }
            }
            
            if( g_vars.rage.bodyaim_lethal && e->health( ) < local->get_active_weapon( )->get_weapon_info( )->damage )
                hitboxes.at( 0 ) = pelvis;
            
            if( g_vars.rage.prefer_bodyaim )
            {
                if( !( e->flags( ) & FL_ONGROUND ) || e->health( ) < 50 )
                    hitboxes.at( 0 ) = pelvis;
            }
            
            if( scale == 0.f )
                continue;
            
            // optimize points on certain records.
            bool should_multipoint = true;
            if( g_vars.rage.selectively_multipoint_records )
            {
                // only use multipoint settings on the first/last 2 records.
                const auto records_size = sorted_records.size( );
                if( records_size > 5 )
                {
                    // first two
                    if( record_idx == 0 || record_idx == 1 )
                        should_multipoint = true;
                    // last two
                    else if( record_idx == records_size - 1 || record_idx == records_size - 2 )
                        should_multipoint = true;
                    else
                        should_multipoint = false;
                }
            }
            
            switch( h )
            {
                case head:
                    if( !g_vars.rage.head || !should_multipoint )
                        continue;
                    break;
                case l_chest:
                case u_chest:
                case pelvis:
                    if( !g_vars.rage.pelvis || !should_multipoint ) // should always multipoint the torso regardless of the selective multipoint option.
                        continue;
                    break;
                case l_upperarm:
                case r_upperarm:
                    if( !g_vars.rage.arms || !should_multipoint )
                        continue;
                    break;
                case l_thigh:
                case r_thigh:
                    if( !g_vars.rage.legs || !should_multipoint )
                        continue;
                    break;
                default:
                    continue;
            }
            
            float rs = bbox->m_flRadius * scale;
            
            if( bbox->m_flRadius == -1.f )
            {
                
            }
            else if( bbox->m_flRadius > 0.f )
            {
                //// pill.
                if( h == head )
                    points.push_back( center + top * rs );
                
                points.push_back( center + right * rs );
                points.push_back( center + left * rs );
            }
        }
    }
    catch(const std::exception& e)
    {
        
    }
    
    return true;
}
*/
