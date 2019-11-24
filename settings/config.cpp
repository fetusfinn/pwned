/*      config.cpp
 *
 *
 */
#include "common.h"
#include "config.h"
#include <nlohmann/json.hpp>
#include <dirent.h>

using json = nlohmann::json;

config_manager_t g_config;

static std::string g_config_ext     = "";
static std::string g_config_folder  = "";

/*
 *  does_file_exist
 *  Returns true if given file exists
 */
inline bool does_file_exist(const string& path)
{
    fstream f(path);
    return  f.good();
}

/*
 *  find_files
 *
 */
std::vector<std::string> find_files(const std::string& path, const std::string& extention = "")
{
    std::vector<std::string> found = {};
    
    DIR* dir = opendir(path.c_str());
    
    if(!dir)
        return {};
    
    dirent* ent;
    
    // iterate thru all files in dir
    while((ent = readdir(dir)))
    {
        if(ent->d_type == DT_DIR)
            continue;
        
        std::string name = ent->d_name;
        
        // if its the skin file then skip
        if(name == "skins" + g_config_ext)
            continue;
        
        // no extention given so save all
        if(extention.empty())
        {
            found.push_back(name);
        }
        else
        {
            // only save extention
            if(name.find(g_config_ext) != std::string::npos)
            {
                name.resize(name.size() - extention.size());
                found.push_back(name);
            }
        }
    }
    
    return found;
}

/*
 *  init
 *  Sets up the config manager
 */
void config_manager_t::init()
{
    // set the folder path, /Users/username/pwned/
    g_config_folder = std::string(getenv("HOME")) + "/pwned/";
    g_config_ext    = ".txt";
    
    // create the config folder if not exists
    if(!does_file_exist(g_config_folder))
        mkdir(g_config_folder.c_str(), 0755);
    
    // check the config folder for configs
    m_configs = find_files(g_config_folder, g_config_ext);
    
    // no configs found
    if(m_configs.empty())
    {
        // create the default config
        m_configs.push_back("default");
        
        // create the new config
        save();
    }
    
    // load the config
    load();
    
    // resave it to update it incase new settings added
    save();
    
    // create the initial skins file if not already created
    // moved to skinchanger.cpp
    // init_skin_file();
}

/*
 *  set_color_value
 *  Saves an ImColor to the config
 */
void set_color_value(json& config, const string& key, ImColor color)
{
    config["colors"][key]["r"] = color.Value.x;
    config["colors"][key]["g"] = color.Value.y;
    config["colors"][key]["b"] = color.Value.z;
    config["colors"][key]["a"] = color.Value.w;
}

/*
 *  save
 *  Saves the selected config
 */
void config_manager_t::save()
{
    json config;
    string section;
    
    section = "menu";
    config[section]["key"]              = set.menu.key;
    
    section = "legit";
    config[section]["aimbot"]           = set.legit.aimbot;
    config[section]["fov"]              = set.legit.fov;
    
    section = "rage";
    
    section = "antiaim";
    
    section = "misc";
    
    section = "colors";
    set_color_value(config, "menu", set.colors.menu);
    set_color_value(config, "player_box", set.colors.players.box);
    
    std::string current = m_configs.at(set.config);
    
    ofstream f;
    f.open(g_config_folder + current + g_config_ext);
    f << config.dump(2, ' ');
    f.close();
}

/*
 *  get_value
 *  Gets and sets the given value from the config
 */
template<class T>
void get_value(json config, string section, string key, T* value)
{
    try
    {
        *value = config[section][key];
    }
    catch(exception& e)
    {
        
    }
}

/*
 *  get_color_value
 *  Gets and sets the given color value from the config
 */
void get_color_value(json config, string key, ImColor* value)
{
    try
    {
        value->Value.x = config["colors"][key]["r"];
        value->Value.y = config["colors"][key]["g"];
        value->Value.z = config["colors"][key]["b"];
        value->Value.w = config["colors"][key]["a"];
    }
    catch(exception& e)
    {
        
    }
}

/*
 *  load
 *  Loads the selected configs settings
 */
void config_manager_t::load()
{
    std::string current = m_configs.at(set.config);
    
    string buffer, line;
    
    if(!does_file_exist(g_config_folder + current + g_config_ext))
    {
        skeep("Cant find config");
        return;
    }
    
    ifstream f(g_config_folder + current + g_config_ext);
    
    // read the config into "buffer"
    while(getline(f, line))
        buffer += line;
    
    f.close();
    
    json config = json::parse(buffer);
    
    string section;
    
    section = "menu";
    get_value(config, section, "key", &set.menu.key);
    
    section = "legit";
    get_value(config, section, "aimbot", &set.legit.aimbot);
    get_value(config, section, "fov", &set.legit.fov);
    
    section = "colors";
    get_color_value(config, "menu", &set.colors.menu);
    get_color_value(config, "player_box", &set.colors.players.box);
}

#include "skinchanger.h"

// path to the skin file
static std::string g_skin_file = "";

/*
 *  init_skin_file
 *  Creates the skins file if it doesnt exist
 */
void config_manager_t::init_skin_file()
{
    g_skin_file = g_config_folder + "skins" + g_config_ext;
    
    if(does_file_exist(g_skin_file))
        return;
    
    json config;
    
    for(const auto& _item : g_item_def_index_map)
    {
        auto item = _item.second;
        
        std::string section = item.entity_name;
        
        config[section]["paint_kit"]    = -1;
        config[section]["seed"]         = -1;
        config[section]["wear"]         = -1;
        config[section]["stattrack"]    = -1;
    }
    
    ofstream f;
    f.open(g_skin_file);
    f << config.dump(2, ' ');
    f.close();
}

/*
 *  save_skin
 *  Updates the skin config for the given weapon
 */
void config_manager_t::save_skin(int weapon_id, skin_config_t skin_config)
{
    // load in the skin config
    ifstream f(g_skin_file);
    
    string buffer, line;
    
    while(getline(f, line))
        buffer += line;
    
    f.close();
    
    if(buffer.empty())
    {
        skeep("Unable to save skin");
        return;
    }
    
    json config = json::parse(buffer);
    
    // save the new skin config for the given weapon
    std::string section = g_item_def_index_map.at(weapon_id).entity_name;
    
    config[section]["paint_kit"]    = skin_config.fallback_paint_kit;
    config[section]["seed"]         = skin_config.fallback_seed;
    config[section]["wear"]         = skin_config.fallback_wear;
    config[section]["stattrack"]    = skin_config.fallback_stattrak;
    
    ofstream of;
    of.open(g_skin_file);
    of << config.dump(2, ' ');
    of.close();
}

/*
 *  save_skin
 *  Updates the skin config for the given weapon
 */
void config_manager_t::save_skins()
{
    // load in the skin config
    ifstream f(g_skin_file);
    
    string buffer, line;
    
    while(getline(f, line))
        buffer += line;
    
    f.close();
    
    if(buffer.empty())
    {
        skeep("Unable to save skins");
        return;
    }
    
    json config = json::parse(buffer);
    
    for(const auto& item : g_item_def_index_map)
    {
        std::string section = item.second.entity_name;
        
        auto skin_config = set.skins.skins.at(item.first);
        
        config[section]["paint_kit"]    = skin_config.fallback_paint_kit;
        config[section]["seed"]         = skin_config.fallback_seed;
        config[section]["wear"]         = skin_config.fallback_wear;
        config[section]["stattrack"]    = skin_config.fallback_stattrak;
    }
    
    ofstream of;
    of.open(g_skin_file);
    of << config.dump(2, ' ');
    of.close();
}

/*
 *  get_skin_config
 *  Returns the current skin config for the given weapon
 */
skin_config_t config_manager_t::get_skin_config(short item_def_index)
{
    skin_config_t ret;
    
    ret.item_definition_index = -1;
    
    if(!does_file_exist(g_skin_file))
        return ret;
    
    ifstream f(g_skin_file);
    
    std::string line, buffer;
    
    // read the config into "buffer"
    while(getline(f, line))
        buffer += line;
    
    f.close();
    
    json config = json::parse(buffer);
    
    short _index = 0;
    
    if(item_def_index >= WEAPON_KNIFE_BAYONET && item_def_index <= WEAPON_KNIFE_WIDOWMAKER)
        _index = (global::local == nullptr ? (WEAPON_KNIFE) : (global::local->get_team() == TEAM_COUNTER_TERRORIST?WEAPON_KNIFE_T:WEAPON_KNIFE));
    
    std::string section = g_item_def_index_map.at(_index).entity_name;
    
    get_value(config, section, "seed",      &ret.fallback_seed);
    get_value(config, section, "paint_kit", &ret.fallback_paint_kit);
    get_value(config, section, "stattrack", &ret.fallback_stattrak);
    get_value(config, section, "wear",      &ret.fallback_wear);
    get_value(config, section, "item_definition_index", &ret.item_definition_index);
    get_value(config, section, "name",      &ret.custom_name);
    
    return ret;
}
