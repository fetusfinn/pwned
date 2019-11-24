/*
 *  misc
 */
#include "common.h"
#include "misc.h"

misc_t* g_misc = new misc_t();

template<class T>
void change_convar(std::string con_name, T value)
{
    convar_t* cvar = g_cvar->find_var(con_name.c_str());
    *(int*)((uintptr_t)&cvar->m_change_callback_fn + 0x15) = 0;
    cvar->set_value(value);
}

void change_skybox(std::string skybox)
{
    convar_t* sv_skybox = g_cvar->find_var("sv_skybox");
    
    static std::string orig_skybox = sv_skybox->m_string;
    
    *(int*)((uintptr_t)&sv_skybox->m_change_callback_fn + 0x15) = 0;
    
    if(skybox.empty())
        skybox = orig_skybox;
    
    sv_skybox->set_value(skybox.c_str());
}

/*
 *
 *
 */
void misc_t::transparent_props(float override_transparency)
{
    if(!g_engine->is_in_game() || !global::local)
        return;
    
    static float last_set = 0.f;
    
    if(set.misc.prop_alpha == last_set)
        return;
    
    last_set = set.misc.prop_alpha;
    
    // disable fast path
    static convar_t* r_drawspecificstaticprop = g_cvar->find_var("r_drawspecificstaticprop");
    
    if(set.misc.prop_alpha == 100.f)
        r_drawspecificstaticprop->set_value(-1);
    else
        r_drawspecificstaticprop->set_value(0);
    
    float translucency = set.misc.prop_alpha / 100.f;
    
    if(override_transparency > 0.f)
        translucency = override_transparency / 100.f;
    
    for(int i = g_mat_system->first_material(); i != g_mat_system->invalid_material(); i = g_mat_system->next_material(i))
    {
        material_t* mat = g_mat_system->get_material(i);
        
        if(!mat || std::strstr(mat->get_name(), "flashlight"))
            continue;
        
        if(std::strstr(mat->get_texture_group_name(), "StaticProp"))
            mat->alpha_modulate(translucency);
    }
}

/*
 
 skybox names
 
 "cs_baggage_skybox_",
 "cs_tibet",
 "embassy",
 "italy",
 "jungle",
 "office",
 "nukeblank",
 "sky_venice",
 "sky_cs15_daylight01_hdr",
 "sky_cs15_daylight02_hdr",
 "sky_cs15_daylight03_hdr",
 "sky_cs15_daylight04_hdr",
 "sky_csgo_cloudy01",
 "sky_csgo_night_flat",
 "sky_csgo_night02",
 "sky_csgo_night02b",
 "sky_day02_05",
 "sky_day02_05_hdr",
 "sky_dust",
 "vertigo",
 "vertigo_hdr",
 "vertigoblue_hdr",
 "vietnam"
 
 */
