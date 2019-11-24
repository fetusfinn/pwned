/*
 *  config.h
 */
#pragma once

using namespace std;

struct skin_config_t
{
    int entity_quality      = -1;
    int fallback_seed       = -1;
    int fallback_paint_kit  = -1;
    int fallback_stattrak   = -1;
    float fallback_wear     = 0.000001f;
    short item_definition_index = -1;
    std::string custom_name = "";
};

class config_manager_t
{
private:
    
    std::vector<std::string> m_configs;
    
public:
    
    void init();
    void load();
    void save();
    
    void init_skin_file();
    void save_skin(int weapon_id, skin_config_t skin_config);
    void save_skins();
    skin_config_t get_skin_config(short item_def_index);
    
    vector<std::string> get_configs() { return m_configs; }
};

extern config_manager_t g_config;
