/*
 *  legitbot.h
 */
#pragma once

class legitbot_t
{
private:
    
    player_t*   m_target;
    int         m_target_index;
    
private:
    
    
    
public:
    
    void aimbot();
    
};

extern legitbot_t* g_legit;
