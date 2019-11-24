/*
 *  base_player.h
 */
#pragma once

class anim_state_t;
class base_weapon_t;

class base_player_t : public base_entity_t
{
public:
    
    unsigned int get_tick_base()
    {
        return sdk_get_offset(unsigned int, base_player, m_tick_base);
    }
    
    bool is_player()
    {        
        return strcmp(get_client_class()->m_network_name, "CCSPlayer") == 0;
    }
    
    bool is_immune()
    {
        return sdk_get_offset(bool, cs_player, m_immune);
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
    
    sdk_netvar(int, get_flags_raw, "DT_BasePlayer", "m_fFlags");
    
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
    
    vec3_t get_velocity()
    {
        return sdk_get_offset(vec3_t, base_player, m_velocity);
    }
    
    float get_lower_body_yaw()
    {
        return sdk_get_offset(float, cs_player, m_lower_body_yaw);
    }
    
    int get_armor()
    {
        return sdk_get_offset(int, cs_player, m_armor);
    }
    
    bool has_helmet()
    {
        return sdk_get_offset(bool, cs_player, m_has_helmet);
    }
    
    void* get_weapon_handle()
    {
        return sdk_get_pointer(void, base_combat_character, m_active_weapon);
    }
    
    anim_state_t* get_anim_state()
    {
        return *(anim_state_t**)((uintptr_t)this + g_offsets.player_anim_state);
    }
    
    base_weapon_t* get_weapon();
    
    sdk_netvar(base_handle_t, get_observer_target, "DT_CSPlayer", "m_hObserverTarget");
    // sdk_netvar(vec3_t, get_angles, "DT_CSPlayer", "m_angEyeAngles");
    
    qangle_t* get_angles()
    {
        return sdk_get_pointer(qangle_t, cs_player, m_eye_angles);
    }
    
    int* get_my_weapons()
    {
        return sdk_get_pointer(int, base_combat_character, m_my_weapon);
    }
};

typedef base_player_t player_t;
