/*
 *  offsets.h
 */
#pragma once

struct offsets_t
{
    void init();
    
    uintptr_t player_anim_state;
    
    struct
    {
        uintptr_t m_team;
        uintptr_t m_collision;
        uintptr_t m_origin;
    }base_entity;
    
    struct
    {
        uintptr_t m_health;
        uintptr_t m_lifestate;
        uintptr_t m_view_offset;
        uintptr_t m_tick_base;
        uintptr_t m_flags;
        uintptr_t m_aim_punch_angle;
        uintptr_t m_view_punch_angle;        
    }base_player;
    
    struct
    {
        uintptr_t m_flash_alpha;
        uintptr_t m_is_scoped;
    }cs_player;
    
    struct
    {
        
    }base_combat_character;
    
    struct
    {
        uintptr_t m_clip1;
    }base_combat_weapon;
    
    struct
    {
        uintptr_t m_bomb_ticking;
        uintptr_t m_blow_time;
        uintptr_t m_bomb_defused;
        uintptr_t m_bomb_defuser;
        uintptr_t m_defuse_count_down;
    }planted_c4;
    
    struct
    {
        
    }base_attributable_item;
    
    struct
    {
        
    }base_view_model;
    
    struct
    {
        
    }weapon_cs_base;
    
    struct
    {
        
    }weapon_c4;
    
    struct
    {
        
    }base_cs_grenade;
    
    struct
    {
        // todo
        // DT_CSGameRulesProxy
    }game_rules;
};

extern offsets_t g_offsets;
