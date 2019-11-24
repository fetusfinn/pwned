/*      create_move.cpp
 *
 *
 */
#include "common.h"
#include "antiaim.h"
#include "ragebot.h"
#include "movement.h"
#include "backtrack.h"
#include "legitbot.h"

void fix_movement(user_cmd_t* cmd, vec3_t wish_angle)
{
    vec3_t view_fwd, view_right, view_up, cmd_fwd, cmd_right, cmd_up;
    qangle_t viewangles = cmd->m_view_angles;
    
    angle_vectors(wish_angle, view_fwd, view_right, view_up);
    angle_vectors(viewangles, cmd_fwd, cmd_right, cmd_up);
    
    const float v8  = sqrtf(view_fwd.x * view_fwd.x + view_fwd.y * view_fwd.y);
    const float v10 = sqrtf(view_right.x * view_right.x + view_right.y * view_right.y);
    const float v12 = sqrtf(view_up.z * view_up.z);
    
    const vec3_t norm_view_fwd(1.f / v8 * view_fwd.x, 1.f / v8 * view_fwd.y, 0.f);
    const vec3_t norm_view_right( 1.f / v10 * view_right.x, 1.f / v10 * view_right.y, 0.f);
    const vec3_t norm_view_up(0.f, 0.f, 1.f / v12 * view_up.z);
    
    const float v14 = sqrtf(cmd_fwd.x * cmd_fwd.x + cmd_fwd.y * cmd_fwd.y);
    const float v16 = sqrtf(cmd_right.x * cmd_right.x + cmd_right.y * cmd_right.y);
    const float v18 = sqrtf(cmd_up.z * cmd_up.z);
    
    const vec3_t norm_cmd_fwd(1.f / v14 * cmd_fwd.x, 1.f / v14 * cmd_fwd.y, 0.f);
    const vec3_t norm_cmd_right(1.f / v16 * cmd_right.x, 1.f / v16 * cmd_right.y, 0.f);
    const vec3_t norm_cmd_up(0.f, 0.f, 1.f / v18 * cmd_up.z);
    
    const float v22 = norm_view_fwd.x * cmd->m_forward_move;
    const float v26 = norm_view_fwd.y * cmd->m_forward_move;
    const float v28 = norm_view_fwd.z * cmd->m_forward_move;
    const float v24 = norm_view_right.x * cmd->m_side_move;
    const float v23 = norm_view_right.y * cmd->m_side_move;
    const float v25 = norm_view_right.z * cmd->m_side_move;
    const float v30 = norm_view_up.x * cmd->m_up_move;
    const float v27 = norm_view_up.z * cmd->m_up_move;
    const float v29 = norm_view_up.y * cmd->m_up_move;
    
    cmd->m_forward_move = (norm_cmd_fwd.x * v24 + norm_cmd_fwd.y * v23 + norm_cmd_fwd.z * v25)
                        + (norm_cmd_fwd.x * v22 + norm_cmd_fwd.y * v26 + norm_cmd_fwd.z * v28)
                        + (norm_cmd_fwd.y * v30 + norm_cmd_fwd.x * v29 + norm_cmd_fwd.z * v27);
    
    cmd->m_side_move    = (norm_cmd_right.x * v24 + norm_cmd_right.y * v23 + norm_cmd_right.z * v25)
                        + (norm_cmd_right.x * v22 + norm_cmd_right.y * v26 + norm_cmd_right.z * v28)
                        + (norm_cmd_right.x * v29 + norm_cmd_right.y * v30 + norm_cmd_right.z * v27);
    
    cmd->m_up_move      = norm_cmd_up.x * v23 + norm_cmd_up.y * v24 + norm_cmd_up.z * v25
                        + (norm_cmd_up.x * v26 + norm_cmd_up.y * v22 + norm_cmd_up.z * v28)
                        + (norm_cmd_up.x * v30 + norm_cmd_up.y * v29 + norm_cmd_up.z * v27);
    
    cmd->m_forward_move = util_clamp(cmd->m_forward_move, -450.f, 450.f);
    cmd->m_side_move    = util_clamp(cmd->m_side_move, -450.f, 450.f);
    cmd->m_up_move      = util_clamp(cmd->m_up_move, -320.f, 320.f);
}

// todo : clean up
bool create_move_hook(void* thisptr, float sample, user_cmd_t* cmd)
{
    print_hook();
    
    bool ret = client_mode_vmt->get_original_method<create_move_fn>(INDEX_CREATE_MOVE)(thisptr, sample, cmd);
    
    if(!cmd)
        return ret;
    
    if(!cmd->m_command_number)
        return ret;
    
    global::cmd = cmd;
    user_cmd_t orig_cmd = *cmd;
    
    if(!global::local)
        global::local = (player_t*)g_ent_list->get_entity(g_engine->get_local_player());
    
    if(!global::weapon)
        global::weapon = global::local->get_weapon();
    
    // cancel crouch delay
    cmd->m_buttons |= IN_BULLRUSH;
    
    qangle_t wish = cmd->m_view_angles;
    
    // features
    if(global::local)
    {
        // code that affects movement is called before predition
        
        g_client_state;
        
        g_movement->bhop();
        
        g_movement->strafe();
        
        // g_antiaim->slow_walk();
        
        // g_antiaim->fake_duck();
        
        // prediction start
        
        // maybe move to framestage        
        
        if(global::weapon)
        {
            g_rage->aimbot();
            
            g_legitbot.aimbot();
            
            g_time_warp.backtrack();
        }
        
        // g_backtrack->backtrack_player(nullptr);
        
        // prediction end
    }
    
    if(global::_send_packet)
    {
        if(global::send_packet)
            global::choked++;
        else
            global::choked = 0;
    }
    
    fix_movement(cmd, wish);
    
    cmd->m_view_angles.clamp();
    
    *global::_send_packet = global::send_packet;
    
    if(global::choked > 14)
        *global::_send_packet = true;    
    
    return ret;
}
