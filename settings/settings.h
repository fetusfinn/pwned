/*
 *  settings.h
 */
#pragma once

#include "imgui.h"

typedef std::vector<bool> multi;

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
        int  team_flags = 0;     // 0 = enemy only, 1 = team only, 2 = all
        
        // player visuals
        struct
        {
            bool box        = false;
            bool name       = false;
            bool health     = false;
            int  bot_bar    = 0;     // 0 = off, 1 = armor, 2 = ammo... todo
            bool armor      = false;
            bool equipment  = false;
        }player;
        
        struct
        {
            bool players        = false;
            bool behind_walls   = false;    // same as visible flag, todo : remove
            int  player_type    = 0;        // 0 = flat, 1 = textured... todo
        }chams;
        
        struct
        {
            multi   hitmarkers; // crosshair, sound, damage
            bool    bomb_timer  = false;
            
            // removals
            float 	flash_alpha = 0.f;
            bool    remove_smoke= false;
            bool    remove_scope= false;
        }other;
    }visuals;
    
    struct
    {
        struct
        {
            // color_t box = color_t::white, offscreen = color_t::blue;
            ImColor box = ImColor(255, 255, 255);
        }players;
        
        struct
        {
            ImColor players         = ImColor(255, 255, 255, 255);
            ImColor behind_walls    = ImColor(255, 255, 255, 255);
        }chams;
    }colors;
    
    struct
    {
        int  fov = 0;
        
        bool bhop = false;
        bool strafe = false;
        
        bool thirdperson = false;
        
        bool remove_view_punch  = false;
        bool remove_aim_punch   = false;
    }misc;
    
    struct
    {
        bool  aimbot    = false;
        multi hitboxes  = {};
        int   fov       = 0;    // 0 - 180
        int   smooth    = 0;    // 0 - 100, percent, 0 = off
        int   rcs_x     = 0;    // 0 - 100, percent, 0 = off
        int   rcs_y     = 0;
    }legit;
    
};
