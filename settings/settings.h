/*
 *  settings.h
 */
#pragma once

struct settings_t
{
    struct
    {
        bool    open    = false;
        int     key     = -1;
        color_t color   = color_t::white;
    }menu;
    
    struct
    {
        int w, h;
    }screen;
    
    struct
    {
        // flags
        bool visible    = false; // visible check
        bool team       = false; // show my team, always showing enemy team
        int  team_flags = 0;     // 0 = enemy only, 1 = team only, 2 = all
        
        // player visuals
        struct
        {
            bool box        = false;
            bool name       = false;
            bool health     = false;
            bool armor      = false;
            int  bot_bar    = 0;     // 0 = off, 1 = armor, 2 = ammo
            bool offscreen  = false;
            
            bool radar      = false; // idk if player or not
        }player;
        
        struct
        {
            // cham related
            bool players    = false;
        }chams;
        
        struct
        {
            std::vector<bool> hitmarkers; // crosshair, sound, damage
            bool bomb_timer = false;;
        }other;
    }visuals;
    
    struct
    {
        struct
        {
            color_t box = color_t::white, offscreen = color_t::blue;
        }players;
        
        struct
        {
            color_t players = color_t::white;
        }chams;
    }colors;
};
