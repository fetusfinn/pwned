/*  antiaim.cpp
 *
 *
 */
#include "common.h"
#include "antiaim.h"

float get_max_desync_delta()
{
    return 0.f;
}

void desync(float& angle, const float& old_angle, bool& bSendPacket)
{
    /*
    float side = 1.0f;
    float SpawnTime = 0.0f;
    int max_choke_ticks = 15;
    int latency_ticks = 0;
    float fl_latency = g_engine->get_net_channel_info()->get_latency(FLOW_OUTGOING);
    int latency = TIME_TO_TICKS(fl_latency);
            
    //its not for yu m8
    if (global::choked <= 0)
    {
        latency_ticks = latency;
    }
    else
    {
        latency_ticks = max(latency, latency_ticks);
    }
    
    //its not for yu m8
    if (m_game_rules->valve_ds())
    {
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
    
    if (*(float_t*)((uintptr_t)game::localdata.localplayer() + 0xA360) != SpawnTime)
    {
        SpawnTime = *(float_t*)((uintptr_t)game::localdata.localplayer() + 0xA360);
    }
    
    float next_lby = 0.f;
    bool broke_lby = false;
    
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
    
    for (int i = 0; i <= m_globals->maxClients; i++)
    {
        i_client_entity* m_entity = m_entity_list->get_client_entity(i);
        
        if (is_viable_target(m_entity))
        {
            float fov = fov_to_player(viewoffset, view, m_entity, 0);
            if (fov < mfov)
            {
                mfov = fov;
                target = i;
            }
        }
    }
    
    q_angle at_target_angle;
    
    static bool jitter = false;
    jitter = !jitter;
    
    if (Menu::Window.AntiAimTab.DesyncAA.GetState())
    {
        if (target)
        {
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
                
                if (left_two > right_two)
                {
                    side = 1;
                }
                else if (right_two > left_two)
                {
                    side = -1;
                }
                
                if (std::fabsf(*(float_t*)((uintptr_t)game::localdata.localplayer() + 0xA360) - m_globals->curtime) > 1.0f)
                {
                    //balance
                    if (Menu::Window.AntiAimTab.DesynCtPYE.GetIndex() == 1)
                    {
                        float minimal_move = 2.0f;
                        if (game::localdata.localplayer()->getflags() & FL_DUCKING)
                            minimal_move *= 3.f;
                        
                        if (game::globals.UserCmd->buttons & IN_WALK)
                            minimal_move *= 3.f;
                        
                        bool should_move = game::localdata.localplayer()->velocity().Length2D() <= 0.0f || std::fabsf(game::localdata.localplayer()->velocity().z) <= 100.0f;
                        
                        if ((game::globals.UserCmd->command_number % 2) == 1)
                        {
                            angle += 120.0f * side;
                            if (should_move)
                                game::globals.UserCmd->sidemove -= minimal_move;
                            bSendPacket = false;
                        }
                        else if (should_move)
                        {
                            game::globals.UserCmd->sidemove += minimal_move;
                        }
                    }
                    //static
                    if (Menu::Window.AntiAimTab.DesynCtPYE.GetIndex() == 0)
                    {
                        if (next_lby >= m_globals->curtime)
                        {
                            if (!broke_lby && bSendPacket && m_client_state->chokedcommands > 0)
                                return;
                            
                            broke_lby = false;
                            bSendPacket = false;
                            angle += 120.0f * side;
                        }
                        else
                        {
                            broke_lby = true;
                            bSendPacket = false;
                            angle += 120.0f * -side;
                        }
                    }
                }
                
                angle = std::remainderf(angle, 360.0f);
                
                if (m_client_state->chokedcommands >= max_choke_ticks)
                {
                    bSendPacket = true;
                }
                
                if (anim_state)
                {
                    IAnimState anim_state_backup = *anim_state;
                    *(q_angle*)((uintptr_t)game::localdata.localplayer() + UTILS::netvar_hook_manager.GetOffset("DT_BasePlayer", "deadflag") + 0x4) = game::globals.UserCmd->viewangles;
                    //game::localdata.localplayer()->update_anims();
                    
                    //SetupVelocity
                    if (anim_state->speed_2d > 0.1f || std::fabsf(anim_state->flUpVelocity))
                    {
                        next_lby = m_globals->curtime + 0.22f;
                    }
                    else if (m_globals->curtime > next_lby)
                    {
                        if (std::fabsf(game::math.angle_diff(anim_state->m_flGoalFeetYaw, anim_state->m_flEyeYaw)) > 35.0f)
                        {
                            next_lby = m_globals->curtime + 1.1f;
                        }
                    }
                    
                    *anim_state = anim_state_backup;
                }
            }
            else
            {
                angle -= jitter ? 180 : 0;
            }
        }
    }
    
    //legit
    if (Menu::Window.AntiAimTab.DesyncAA.GetState() && Menu::Window.AntiAimTab.DesynCtPYE.GetIndex() == 2)
    {
        if (bSendPacket && !m_engine->get_net_channel_info()->chokedPackets)
            bSendPacket = false;
        
        if (bSendPacket && m_engine->get_net_channel_info()->chokedPackets && !(game::globals.UserCmd->buttons & (IN_ATTACK | IN_ATTACK2)))
        {
            auto absMaxDesyncAngle = fabsf(m_entity_list->get_client_entity(m_engine->GetLocalPlayer())->get_max_desync_delta());
            
            if (angle - old_angle == 0.0f)
                angle += absMaxDesyncAngle;
            else
                angle = old_angle + clamp(angle - old_angle, -absMaxDesyncAngle, absMaxDesyncAngle);
        }
    }
     */
}

