/*
 * ragebot.h
 */
#pragma once

class rage_bot_t
{
private:
    
    player_t*   m_target;
    int         m_target_index;
    int         m_target_hitbox;
    
private:
    
    std::vector<hitbox_t> get_target_hitboxes();
    
    int find_target_hitbox(player_t* player);
    
public:
    
    void aimbot();
    int  get_damage(const vec3_t& point, bool team = false, player_t* target = nullptr);
    
};

extern rage_bot_t* g_rage;
