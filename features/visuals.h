/*
 *  visuals.h
 */
#pragma once

class visuals_t
{
private:
    
    vector<float> m_player_alpha;
    
public:
    
    visuals_t()
    {
        reset_player_alpha();
    }
    
    inline void reset_player_alpha() { m_player_alpha.clear(); m_player_alpha.resize(64); }
    
    void draw_player_esp();
    void draw_other_esp();
    
    void draw_hitmarkers();
    void draw_scope();
    void draw_spectator_list();
    
    void remove_flash();
    void remove_smoke();
};

extern visuals_t* g_visuals;
