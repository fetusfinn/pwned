/*
 * 	config.h
 */
#pragma once

class config_manager_t
{
private:
    
    int         m_config;
    std::string m_configs;
    
public:
    
    void load();
    void save();
    
    // todo 
};

extern config_manager_t g_config;
