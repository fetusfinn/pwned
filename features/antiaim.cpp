/*  antiaim.cpp
 *
 *
 */
#include "common.h"
#include "antiaim.h"

// https://github.com/EternityX/DEADCELL-CSGO/blob/master/csgo/features/anti-aim/antiaim.cpp
// https://www.unknowncheats.me/forum/counterstrike-global-offensive/317456-detecting-desync.html
// https://www.unknowncheats.me/forum/counterstrike-global-offensive/267534-breaking-lby-below-100-delta.html
// https://www.unknowncheats.me/forum/counterstrike-global-offensive/325128-desync-send.html
// https://www.unknowncheats.me/forum/counterstrike-global-offensive/328355-balance-desync.html
// https://github.com/sstokic-tgm/Gladiatorcheatz-v2/blob/master/features/Resolver.cpp#L96-L99
// https://www.unknowncheats.me/forum/counterstrike-global-offensive/244310-animation-resolver.html // disable interp

antiaim_manager_t* g_antiaim = new antiaim_manager_t();

/*
 *  Antiaim
 */

/*
    Here's the snippet all of you are fumbling over, ACT_CSGO_IDLE_TURN_BALANCEADJUST is activity 979.
    In short, don't snap by over 120 when you fake lby and you won't trigger balance adjust.
 */

/*
 *
 *
 */
float get_max_desync_delta()
{
    return 0.f;
}

bool can_anti_aim()
{
    if(!set.antiaim.enabled)
        return false;
    
    if(!global::local || !global::cmd)
        return false;
    
    if(!global::local->is_alive() || (global::local->get_flags() & FL_FROZEN))
        return false;
    
    move_type_t move_type = global::local->get_move_type();
    
    if(move_type == MOVETYPE_NOCLIP || move_type == MOVETYPE_LADDER)
        return false;
    
    if(global::cmd->m_buttons & IN_USE)
        return false;
    
    weapon_t* weapon = global::local->get_weapon();
    
    if(!weapon)
        return false;
    
    weapon_info_t* weapon_info = weapon->get_weapon_info();
    
    if(!weapon_info)
        return false;
    
    if(weapon_info->m_weapon_type == WEAPONTYPE_KNIFE)
    {
        float next_secondary_attack = 0.f; // weapon->next_sec_attack() - g_globals->m_cur_time;
        float next_primary_attack   = weapon->get_next_attack() - g_globals->m_cur_time;
        
        if((global::cmd->m_buttons & IN_ATTACK && next_primary_attack <= 0.f) || (global::cmd->m_buttons & IN_ATTACK2 && next_secondary_attack<=0.f))
            return false;
    }
    
    /*
    if(global::cmd->m_buttons & IN_ATTACK && global::local->can_shoot(weapon))
    {
        // m_desync_next_tick = true;
        *global::send_packet = false;
        return false;
    }
    
    if(global::local->get_active_weapon()->is_being_thrown())
        return false;
     */
    
    return true;
}

/*
 *
 *
 */
void antiaim_manager_t::anti_aim()
{
    
}


/*
 *  Misc
 */

void LegitPeek(user_cmd_t* pCmd, player_t* pLocalPlayer, bool& bSendPacket, int choke_factor)
{
    // fake lag on peek
    /*
    if (!pLocalPlayer)
        return;
    
    static bool m_bIsPeeking = false;
    
    if (m_bIsPeeking)
    {
        bSendPacket = !(global::choked < choke_factor);
        if (bSendPacket)
            m_bIsPeeking = false;
        return;
    }
    
    float speed = pLocalPlayer->get_velocity().length();
    
    if (speed <= 100.0f)
        return;
    
    collidable_t* pCollidable = pLocalPlayer->get_collidable();
    
    if (!pCollidable)
        return;
    
    vec3_t min, max;
    min = pCollidable->obb_max();
    max = pCollidable->obb_max();
    
    min += pLocalPlayer->get_origin();
    max += pLocalPlayer->get_origin();
    
    vec3_t center = (min + max) * 0.5f;
    
    for (int i = 0; i <= g_ent_list->get_highest_index(); i++)
    {
        player_t* pEntity = g_ent_list->get_player(i);
        
        if(!!pEntity)
            continue;
        
        if(!pEntity->is_alive() || pEntity->is_dormant())
            continue;
        
        if (pEntity == pLocalPlayer || pLocalPlayer->get_team() == pEntity->get_team())
            continue;
        
        weapon_t* pWeapon = pLocalPlayer->get_weapon();
        
        if (!pWeapon)
            continue;
        
        if (pWeapon->get_ammo() <= 0)
            continue;
        
        weapon_info_t* pWeaponInfo = pWeapon->get_weapon_info();
        
        if (!pWeaponInfo)
            continue;
        
        if (pWeaponInfo->iWeaponType <= CSWeaponType::WEAPONTYPE_KNIFE || pWeaponInfo->iWeaponType >= CSWeaponType::WEAPONTYPE_C4)
            continue;
        
        Vector eye_pos = pEntity->GetEyePosition();
        
        Vector direction;
        pMatch->AngleVectors(pEntity->GetEyeAnglesXY(), &direction);
        direction.NormalizeInPlace();
        
        Vector hit_point;
        
        bool hit = IntersectionBoundingBox(eye_pos, direction, min, max, &hit_point);
        
        if (hit && eye_pos.DistTo(hit_point) <= pWeaponInfo->flRange)
        {
            Ray_t ray;
            trace_t tr;
            CTraceFilter filter((CBaseEntity*)pEntity);
            ray.Init(eye_pos, hit_point);
            
            I::EngineTrace()->TraceRay(ray, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &tr);
            
            if (tr.contents & CONTENTS_WINDOW) //skip windows XPPPP
            {                                                                                         // at this moment, we dont care about local player
                filter.pSkip = tr.m_pEnt;
                ray.Init(tr.endpos, hit_point);
                I::EngineTrace()->TraceRay(ray, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &tr);
            }
            
            if (tr.fraction == 1.0f || tr.m_pEnt == pLocalPlayer)
            {
                m_bIsPeeking = true;
                break;
            }
        }
    }
     */
}

/*
 *  Movement
 */

void antiaim_manager_t::slow_walk()
{
    if(!set.antiaim.slow_walk || !g_input_system->is_button_down(KEY_LSHIFT))
        return;
    
    if (!global::local || !global::weapon || !global::cmd)
        return;
    
    weapon_info_t* weapon_info = global::weapon->get_weapon_info();
    
    if(!weapon_info)
        return;
    
    float setings_val = 50; // 0 - 100
    float amount = 0.0034f * setings_val;
    
    vec3_t velocity = global::local->get_velocity();
    qangle_t direction;
    
    vector_angles(velocity, direction);
    
    float speed = velocity.length_2d( );
    
    direction.y = global::cmd->m_view_angles.y - direction.y;
    
    vec3_t forward;
    
    angle_vectors(direction, forward);
    
    vec3_t source = forward * -speed;
    
    if (speed >= (weapon_info->m_max_speed * amount))
    {
        global::cmd->m_forward_move = source.x;
        global::cmd->m_side_move = source.y;
    }
}

void antiaim_manager_t::fake_duck()
{
    if(!set.antiaim.fake_duck)
    
    if(!global::cmd)
        return;
    
    global::cmd->m_buttons |= IN_BULLRUSH;
    
    if (global::choked > 7)
        global::cmd->m_buttons |= IN_DUCK;
    else
        global::cmd->m_buttons &= ~IN_DUCK;
}
