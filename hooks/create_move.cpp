/*      create_move.cpp
 *
 *
 */
#include "common.h"

bool create_move_hook(void* thisptr, float sample, user_cmd_t* cmd)
{
    print_hook();
    
    bool   ret = client_mode_vmt->get_original_method<create_move_fn>(INDEX_CREATE_MOVE)(thisptr, sample, cmd);
    
    if(!cmd)
        return ret;
    
    if(!cmd->m_command_number)
        return ret;
    
    global::cmd = cmd;
    
    if(!global::local)
        global::local = (player_t*)g_ent_list->get_entity(g_engine->get_local_player());
    
    global::cmd->m_buttons |= IN_BULLRUSH;
        
    
    // if(!global::weapon)
        // global::weapon = global::local->get_weapon();
    
    {
        
    }
    
    
    return ret;
}
