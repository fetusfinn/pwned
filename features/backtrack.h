/*
 *  backtrack.h
 */
#pragma once

#include <deque>

#define TIME_TO_TICKS(time) ((int)(0.5f + ((float)time) / g_globals->m_interval_per_tick ))
#define BACKTRACK_MAX_TICKS 12

/*
 *  Backtrack record
 */
struct backtrack_record_t
{
    backtrack_record_t(player_t* player = nullptr, backtrack_record_t* prev = nullptr);
    
    bool is_valid();
    
    float m_tick;
    float m_lby;
    float m_sim_time;
    vec3_t m_origin;
    vec3_t m_head;
    vec3_t m_mins, m_maxs;
    qangle_t m_angles;
    matrix3x4_t m_matrix[128];
    
    backtrack_record_t* m_prev;
};

/*
 *
 */
struct backtrack_player_t
{
    player_t* m_player;
    std::deque<backtrack_record_t> m_records;
};

class c_backtrack
{
private:
    
    std::array<backtrack_player_t, 64> m_records;
    
public:
    
    void store();
    bool get_best_record(player_t* player, backtrack_record_t& best, int hitbox = HITBOX_NECK);
    void restore(player_t* player, const backtrack_record_t& rec);
    void backtrack();
    void draw(player_t* player);
    
    void reset(int index) { auto r = get_records(index); if(!r) return; r->m_records.clear(); }
    backtrack_player_t* get_records(int index) { try { return &m_records.at(index); } catch(exception& e) { return nullptr; } };
};

extern c_backtrack g_time_warp;
