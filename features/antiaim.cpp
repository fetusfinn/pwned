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

antiaim_manager_t* g_antiaim = new antiaim_manager_t();

/*
 *  Antiaim
 */

float antiaim_manager_t::get_max_desync_delta()
{
    if(!global::local)
        return 0.f;
    
    anim_state_t* anim = global::local->get_anim_state();
    
    if(!anim)
        return 0.f;
    
    float speed_fraction = std::max(0.0f, std::min(anim->feet_shuffle_speed, 1.0f));
    
    float speed_factor = std::max(0.0f, std::min(1.0f, anim->feet_shuffle_Speed2));
    
    float unk1 = ((anim->running_accel_progress * -0.30000001) - 0.19999999) * speed_fraction;
    float unk2 = unk1 + 1.0f;
    float delta;
    
    if (anim->duck_progress > 0)
        unk2 += ((anim->duck_progress * speed_factor) * (0.5f - unk2));
    
    delta = *(float*)((uintptr_t)anim + 0x3A4) * unk2;
    
    return abs(delta);
}

bool will_lby_update()
{
    if(!global::local)
        return false;
    
    static float next_update = 0;
    
    float curtime = util_curtime_fixed();
    anim_state_t* anim = global::local->get_anim_state();
    
    if (!anim || !(global::local->get_flags() & FL_ONGROUND))
        return false;
    
    if (anim->speed_2d > 0.1f)
        next_update = curtime + 0.22f;
    
    if (next_update < curtime)
    {
        next_update = curtime + 1.1f;
        return true;
    }
    
    return false;
}

bool break_lby()
{
    const float lby_delta = 120;
    
    if(will_lby_update())
    {
        // *global::send_packet = false;
        
        global::cmd->m_view_angles.y += lby_delta;
        
        // flick
        return true;
    }
    
    return false;
}

float normalise_yaw(float yaw)
{
    if (yaw > 180)
        yaw -= (round(yaw / 360) * 360.f);
    else if (yaw < -180)
        yaw += (round(yaw / 360) * -360.f);
    
    return yaw;
}

void antiaim_manager_t::desync()
{
    float max_delta = get_max_desync_delta(), yaw = 0;
    
    yaw = global::cmd->m_view_angles.y + max_delta;
    yaw = normalise_yaw(yaw);
    
    // GFakeAngle.y = yaw;
    global::cmd->m_view_angles.y = yaw;
}

float get_pitch()
{
    return global::cmd->m_view_angles.x;
}

void real()
{
    float yaw = global::cmd->m_view_angles.y;
    global::cmd->m_view_angles.y = yaw;
}

void antiaim_manager_t::anti_aim()
{
    // desync only works if moving or breaking, this moves side to side
    if(global::local->get_flags() & FL_ONGROUND && global::cmd->m_side_move < 3 && global::cmd->m_side_move > -3)
    {
        static bool _switch = false;
        if (_switch)
            global::cmd->m_side_move = 2;
        else
            global::cmd->m_side_move = -2;
        _switch = !_switch;
    }
    
    if(*global::send_packet)
    {
        desync();
        *global::send_packet = false;
    }
    else
    {
        real();
    }
    
    global::cmd->m_view_angles.x = get_pitch();
    
    if(will_lby_update())
    {
        // *global::send_packet = true;
        // view_angles += lby_delta; // 120
        // m_broke_lby_this_tick = true;
    }
    else if(!global::choked && !*global::send_packet)
    {
        // real
        // view_angles -= delta;
    }
}

void desync2(float& angle, const float& old_angle, bool& bSendPacket)
{
    /*
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
    */
}

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
