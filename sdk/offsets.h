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
        uintptr_t m_simulation_time;
        uintptr_t m_move_type;
        uintptr_t m_model_index;
        uintptr_t m_view_model;
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
        uintptr_t m_velocity;
    }base_player;
    
    struct
    {
        uintptr_t m_flash_alpha;
        uintptr_t m_is_scoped;
        uintptr_t m_lower_body_yaw;
        uintptr_t m_armor;
        uintptr_t m_has_helmet;
        uintptr_t m_immune;
        uintptr_t m_eye_angles;
    }cs_player;
    
    struct
    {
        uintptr_t m_active_weapon;
        uintptr_t m_my_weapon;
    }base_combat_character;
    
    struct
    {
        uintptr_t m_clip1;
        uintptr_t m_next_primary_attack;
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
        uintptr_t m_item_definition_index;
        uintptr_t m_account_id;
        uintptr_t m_item_id_high;
        uintptr_t m_item_id_low;
        uintptr_t m_entity_quality;
        uintptr_t m_custom_name;
        uintptr_t m_fallback_paint_kit;
        uintptr_t m_fallback_seed;
        uintptr_t m_fallback_wear;
        uintptr_t m_fallback_stattrack;
    }base_attributable_item;
    
    struct
    {
        uintptr_t m_weapon;
        uintptr_t m_owner;
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
