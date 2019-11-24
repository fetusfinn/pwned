/*
 *  antiaim.h
 */
#pragma once

// pretty much just rage movement
class antiaim_manager_t
{
private:
    
    bool m_broke_last = false;
    
private:

    
public:
    
    void anti_aim();
    
    
    void slow_walk();
    void fake_duck();
    // todo : fakewalk if its still a thing
    
};

extern antiaim_manager_t* g_antiaim;
