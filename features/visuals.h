/*
 *  visuals.h
 */
#pragma once

class visuals_t
{
private:
    
    vector<float> m_player_alpha;
    
private:
    
    void draw_esp_box(player_box_t box, color_t color);
    void draw_heath_bar(player_box_t box, int value, color_t color);
    void draw_bottom_bar(player_box_t box, int value, int max, color_t color);
    
public:
    
    visuals_t()
    {
        m_player_alpha.resize(64);
    }
    
    void draw_player_esp();
    void draw_other_esp();
    
    void draw_hitmarkers();
    
};

extern visuals_t* g_visuals;
