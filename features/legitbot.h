/*
 *  legitbot.h
 */
#pragma once

class legitbot_t
{
private:
    
    player_t*   m_target;
    int         m_target_index;
    int         m_target_hitbox;
    
private:
    
    void    find_closest_target();
    int     find_closest_hitbox(player_t* player);
    vec3_t  get_aim_position(player_t* player, int hitbox);
    bool    can_hit_target();
    
public:
    
    void aimbot();
    
};

extern legitbot_t* g_legit;

class c_legitbot
{
private:
    
    player_t*   m_target;
    int         m_hitbox;
    qangle_t    m_aim_ang;
    vec3_t      m_aim_pos;
    bool        m_backtrack;
    backtrack_record_t m_record;
    
    bool        m_blacklist;
    
private:
    
    static std::vector<hitbox_t> get_target_hitboxes();

    bool    get_best_record(int index, backtrack_record_t& record);
    bool    get_hitbox_positions_from_record(player_t* player, backtrack_record_t& rec, std::vector<vec3_t>& points);
    bool    get_backtrack_point(vec3_t& point);
    
    float   find_closest_hitbox(player_t* player, int& hitbox);
    bool    find_target();
    bool    calculate_aim_angle(vec3_t aim_point = vec3_t(0, 0, 0));
    void    aim();
    
public:
    
    c_legitbot() : m_target(nullptr), m_hitbox(-1), m_aim_ang({0, 0, 0}) {}
    
    void aimbot();
    
    inline player_t* get_target() { return m_target;  }
    inline vec3_t get_aim_point() { return m_aim_pos; }
    
};

extern c_legitbot g_legitbot;
