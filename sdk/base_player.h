/*
 *  base_player.h
 */
#pragma once

#define ret_offset(type, table, netvar) (type*)((uintptr_t)this + g_offsets.table.netvar);

class base_player_t : public base_entity_t
{
public:
    
    unsigned int get_tick_base()
    {
        return *ret_offset(unsigned int, base_player, m_tick_base);
    }
    
    bool is_player()
    {        
        return !strcmp(get_client_class()->m_network_name, "CCSPlayer");
    }
    
    int get_health()
    {
        return *(int*)((uintptr_t)this + g_offsets.base_player.m_health);
    }
    
    byte get_life_state()
    {
        return *(unsigned char*)((uintptr_t)this + g_offsets.base_player.m_lifestate);
    }
    
    bool is_alive()
    {
        return get_health() > 0 && get_life_state() == 0;
    }
    
    vec3_t get_view_offset()
    {
        return *ret_offset(vec3_t, base_player, m_view_offset);
    }
    
    vec3_t get_eye_position()
    {
        return get_origin() + get_view_offset();
    }
    
    anim_state_t* get_anim_state()
    {
        return *(anim_state_t**)((uintptr_t)this + g_offsets.player_anim_state);
    }
};

typedef base_player_t player_t;
