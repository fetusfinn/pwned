/*
 *  client_state.h
 */
#pragma once

class client_state_t
{
public:
    
    char    _pad0[0x214];
    int     m_delta_tick;
    bool 	m_paused;
    char    _pad1[0x3];
    int     m_view_entity;
    char    _pad2[0x8];
    char    m_level_name[260];
    char    m_level_name_short[40];
    
    
    void force_full_update()
    {
        m_delta_tick = -1;
    }
};

typedef client_state_t* (*get_local_client_fn)(int);
