/*
 *  base_player.h
 */
#pragma once

#define sdk_get_offset(type, table, netvar) *(type*)((uintptr_t)this + g_offsets.table.netvar);
#define sdk_get_pointer(type, table, netvar) (type*)((uintptr_t)this + g_offsets.table.netvar);

class base_player_t : public base_entity_t
{
public:
    
    unsigned int get_tick_base()
    {
        return sdk_get_offset(unsigned int, base_player, m_tick_base);
    }
    
    bool is_player()
    {        
        return !strcmp(get_client_class()->m_network_name, "CCSPlayer");
    }
    
    int get_health()
    {
        return sdk_get_offset(int, base_player, m_health);
    }
    
    byte get_life_state()
    {
        return sdk_get_offset(byte, base_player, m_lifestate);
    }
    
    bool is_alive()
    {
        return get_health() > 0 && get_life_state() == 0;
    }
    
    vec3_t get_view_offset()
    {
        return sdk_get_offset(vec3_t, base_player, m_view_offset);
    }
    
    vec3_t get_eye_position()
    {
        return get_origin() + get_view_offset();
    }
    
    int get_flags()
    {
        return sdk_get_offset(int, base_player, m_flags);
    }
    
    float* get_flash_alpha()
    {
        return sdk_get_pointer(float, cs_player, m_flash_alpha);
    }
    
    bool is_scoped()
    {
        return sdk_get_offset(bool, cs_player, m_is_scoped);
    }
    
    qangle_t* get_aim_punch_angle()
    {
        return sdk_get_pointer(qangle_t, base_player, m_aim_punch_angle);
    }
    
    qangle_t* get_view_punch_angle()
    {
        return sdk_get_pointer(qangle_t, base_player, m_view_punch_angle);
    }
    
    anim_state_t* get_anim_state()
    {
        return *(anim_state_t**)((uintptr_t)this + g_offsets.player_anim_state);
    }
};

typedef base_player_t player_t;
