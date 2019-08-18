/*  ragebot.cpp
 *
 *
 */
#include "common.h"
#include "ragebot.h"

// todo : rewrite everything

rage_bot_t* g_rage = new rage_bot_t();

/*
 *
 *  Returns the hitboxes we want to aim at
 */
std::vector<hitbox_t> rage_bot_t::get_target_hitboxes()
{
     std::vector<hitbox_t> hitboxes;
     
     if(set.rage.hitboxes.at(0))
     {
         hitboxes.push_back(HITBOX_HEAD);
         hitboxes.push_back(HITBOX_NECK);
     }
     
     if(set.rage.hitboxes.at(1))
     {
         hitboxes.push_back(HITBOX_CHEST);
         hitboxes.push_back(HITBOX_UPPER_CHEST);
     }
     
     if(set.rage.hitboxes.at(2))
     {
         hitboxes.push_back(HITBOX_PELVIS);
         hitboxes.push_back(HITBOX_BODY);
     }
     
     if(set.rage.hitboxes.at(3))
     {
         hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
         hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
     }
     
     if(set.rage.hitboxes.at(4))
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
 *  Finds the best hitbox to aim at
 *
int rage_bot_t::find_target_hitbox(player_t* player)
{
    // todo : if autowall then get best damage, else get first visible
    
    std::vector<hitbox_t> hitboxes = get_target_hitboxes();
    for(hitbox_t hitbox : hitboxes)
    {
        if(set.rage.autowall)
        {
            vec3_t hitbox_pos = get_hitbox_position(player, hitbox);
            
            int damage = get_damage(player, hitbox_pos);
            
            if(damage < set.rage.min_damage)
                continue;
            
            return hitbox;
        }
        else
        {
            if(util_is_hitbox_visible(player, hitbox))
                return hitbox;
        }
    }
}

/*
 *
 *  Returns the position that we should aim at
 *
vec3_t rage_bot_t::get_aim_position(player_t* player, int hitbox)
{
    vec3_t aim_pos = vec3_t(0, 0, 0);
    
    // if backtrack
    //     get_best_record // try get lby update tick
    
    if(aim_pos.is_zero())
        aim_pos = get_hitbox_position(player, hitbox);
    
    // todo : prediction
    
    // extrapolate
    if(!aim_pos.is_zero())
        aim_pos += player->get_velocity() * g_globals->m_interval_per_tick;
    
    return aim_pos;
}

/*
 *  find_target
 *  Finds the closest player to the crosshair and stores in m_target_index
 *
void rage_bot_t::find_target()
{
    static int m_tick = 0;
    
    if(++m_tick > 50)
    {
        // reset target and look for a new one
        reset_target();
        m_tick = 0;
    }
    
    float m_best_fov = 0.f;
    
    vec3_t eye_pos = global::local->get_eye_position();
    qangle_t view_angles;
    g_engine->get_view_angles(view_angles);
    
    // index 0 is the world
    for(int i = 1; i < g_globals->m_max_clients; i++)
    {
        if(i == m_target_index)
            continue;
        
        player_t* player = g_ent_list->get_player(i);
        
        if(!player)
            continue;
        
        if(!player->is_player())
            continue;
        
        if(player->get_team() == global::local->get_team())
            continue;
        
        if(!player->is_alive() || player->is_dormant() || player->is_immune())
            continue;
        
        int target_hitbox   = find_target_hitbox(player);
        vec3_t aim_pos      = get_aim_position(player, target_hitbox);
        int fov             = get_fov(view_angles, calculate_angle(eye_pos, aim_pos));
        
        if(fov >= m_best_fov)
            continue;
        
        // found a new target
        m_best_fov      = fov;
        m_target_index  = i;
        m_target_hitbox = target_hitbox;
        skeep("new target : " + std::to_string(i));
    }
    
    // m_tick = 0;
}

/*
 *
 *  Returns true if we can hit the target player in the target hitbox
 *
bool rage_bot_t::can_hit_target()
{
    if(!m_target)
        return false;
    
    if(!m_target->is_alive() || m_target->is_dormant() || m_target->is_immune())
        return false;
    
    if(set.rage.autowall)
    {
        vec3_t hitbox_pos = get_hitbox_position(m_target, m_target_hitbox);
        
        int damage = get_damage(m_target, hitbox_pos);
        
        if(damage >= set.rage.min_damage)
            return true;
    }
    else
    {
        return util_is_hitbox_visible(m_target, m_target_hitbox);
    }
    
    return false;
}

/*
 *
 *  Aimbot function
 *
void rage_bot_t::aimbot()
{
    if(!set.rage.aimbot)
        return;
    
    if(!global::local || !global::weapon)
        return;
    
    int  def   = global::weapon->get_item_definition_index();
    bool knife = global::weapon->is_knife();
    bool bomb  = global::weapon->is_bomb();
    bool nade  = global::weapon->is_grenade();
    int  ammo  = global::weapon->get_ammo();  // for some reason this is returning the wrong value
    
    if(knife || bomb || nade) // || ammo < 1)
        return;
    
    // if we cant hit our current target then we need a new one
    if(!can_hit_target())
        find_target();
    
    if(m_target_index > 0)
        m_target = g_ent_list->get_player(m_target_index);
    
    if(!m_target)
        return;
    
    skeep("have target : " + std::to_string(m_target_index));
    
    // note : the player will be the target until they are out of fov
    
    qangle_t view_angles;
    g_engine->get_view_angles(view_angles);
    
    vec3_t   aim_pos = get_aim_position(m_target, m_target_hitbox);
    qangle_t aim_ang = calculate_angle(global::local->get_eye_position(), aim_pos);
    
    int fov = get_fov(view_angles, aim_ang);
    
    if(fov > set.rage.fov)
        return;

    // if(vars.aimbot.autoshoot)
    //     AutoShoot(local, weapon, pCmd);
    
    // if(vars.aimbot.autocock)
    //     AutoCock(pCmd, weapon);
    
    // if(vars.aimbot.autoscope && weapon->GetCSWpnData()->m_iZoomLevels > 0) // && !local->IsScoped())
    //     pCmd->buttons |= IN_ATTACK2;
    
    // if(smoothing)
    //     QAngle smooth = currentAngles + (newAngles - currentAngles) / smoothAmount;
    // https://www.unknowncheats.me/forum/c-and-c/151887-doing-better-aim-smoothing.html
    // https://github.com/stevemk14ebr/BF4-AtomBot/blob/47168a85ab4d3311cff8756539740f7c0dd7c52f/BF4%20AtomBot/Hack%20Core/AimbotSmoother.h
    
    if(global::cmd->m_buttons & IN_ATTACK)
    {
        if(!aim_pos.is_zero())
        {
            if(!set.rage.silent)
            {
                global::cmd->m_view_angles = aim_ang;
                g_engine->set_view_angles(global::cmd->m_view_angles);
            }
            else
            {
                global::cmd->m_view_angles = aim_ang;
            }
        }
    }
}
*/
