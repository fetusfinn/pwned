/*
 *  skinchanger
 */
#include "common.h"
#include "skinchanger.h"
#include "config.h"

skinchanger_t g_skins;

std::unordered_map<int, item_t> g_item_def_index_map;

void init_g_item_def_index_map1()
{
    static bool _done = false;
    
    if(_done)
        return;
    
    
    g_item_def_index_map = {
        std::make_pair(WEAPON_NONE, item_t("All", "weapon_all", "", "all", "", "")),
        std::make_pair(WEAPON_DEAGLE, item_t("Desert Eagle", "weapon_deagle", "models/weapons/v_pist_deagle.mdl", "deagle", "", "")),
        std::make_pair(WEAPON_ELITE, item_t("Dual Berettas", "weapon_elite", "models/weapons/v_pist_elite.mdl", "elite", "", "")),
        std::make_pair(WEAPON_FIVESEVEN, item_t("Five-Seven", "weapon_fiveseven", "models/weapons/v_pist_fiveseven.mdl", "fiveseven", "", "")),
        std::make_pair(WEAPON_GLOCK, item_t("Glock-18", "weapon_glock", "models/weapons/v_pist_glock18.mdl", "glock", "", "")),
        std::make_pair(WEAPON_AK47, item_t("AK-47", "weapon_ak47", "models/weapons/v_rif_ak47.mdl", "ak47", "", "")),
        std::make_pair(WEAPON_AUG, item_t("AUG", "weapon_aug", "models/weapons/v_rif_aug.mdl", "aug", "", "")),
        std::make_pair(WEAPON_AWP, item_t("AWP", "weapon_awp", "models/weapons/v_snip_awp.mdl", "awp", "", "")),
        std::make_pair(WEAPON_FAMAS, item_t("FAMAS", "weapon_famas", "models/weapons/v_rif_famas.mdl", "famas", "", "")),
        std::make_pair(WEAPON_G3SG1, item_t("G3SG1", "weapon_g3sg1", "models/weapons/v_snip_g3sg1.mdl", "g3sg1", "", "")),
        std::make_pair(WEAPON_GALILAR, item_t("Galil AR", "weapon_galilar", "models/weapons/v_rif_galilar.mdl", "galilar", "", "")),
        std::make_pair(WEAPON_M249, item_t("M249", "weapon_m249", "models/weapons/v_mach_m249para.mdl", "m249", "", "")),
        std::make_pair(WEAPON_M4A1, item_t("M4A4", "weapon_m4a1", "models/weapons/v_rif_m4a1.mdl", "m4a1", "", "")),
        std::make_pair(WEAPON_MAC10, item_t("MAC-10", "weapon_mac10", "models/weapons/v_smg_mac10.mdl", "mac10", "", "")),
        std::make_pair(WEAPON_P90, item_t("P90", "weapon_p90", "models/weapons/v_smg_p90.mdl", "p90", "", "")),
        std::make_pair(WEAPON_MP5, item_t("MP5 SD", "weapon_mp5sd", "models/weapons/v_smg_mp5sd.mdl", "mp5sd", "models/weapons/w_smg_mp5sd.mdl", "models/weapons/w_smg_mp5sd_dropped.mdl")),
        std::make_pair(WEAPON_UMP45, item_t("UMP-45", "weapon_ump45", "models/weapons/v_smg_ump45.mdl", "ump45", "", "")),
        std::make_pair(WEAPON_XM1014, item_t("XM1014", "weapon_xm1014", "models/weapons/v_shot_xm1014.mdl", "xm1014", "", "")),
        std::make_pair(WEAPON_BIZON, item_t("PP-Bizon", "weapon_bizon", "models/weapons/v_smg_bizon.mdl", "bizon", "", "")),
        /*
         // knives
         std::make_pair(WEAPON_KNIFE_BAYONET, item_t("Bayonet", "weapon_bayonet", "models/weapons/v_knife_bayonet.mdl", "bayonet", "", "")),
         std::make_pair(WEAPON_KNIFE_FLIP, item_t("Flip", "weapon_knife_flip", "models/weapons/v_knife_flip.mdl", "knife_flip", "", "")),
         std::make_pair(WEAPON_KNIFE_GUT, item_t("Gut", "weapon_knife_gut", "models/weapons/v_knife_gut.mdl", "knife_gut", "", "")),
         std::make_pair(WEAPON_KNIFE_KARAMBIT, item_t("Karambit", "weapon_knife_karambit", "models/weapons/v_knife_karam.mdl", "knife_karambit", "", "")),
         std::make_pair(WEAPON_KNIFE_M9_BAYONET, item_t("M9 Bayonet", "weapon_knife_m9_bayonet", "models/weapons/v_knife_m9_bay.mdl", "knife_m9_bayonet", "", "")),
         std::make_pair(WEAPON_KNIFE_TACTICAL, item_t("Huntsman", "weapon_knife_tactical", "models/weapons/v_knife_tactical.mdl", "knife_tactical", "", "")),
         std::make_pair(WEAPON_KNIFE_FALCHION, item_t("Falchion", "weapon_knife_falchion", "models/weapons/v_knife_falchion_advanced.mdl", "knife_falchion", "", "")),
         std::make_pair(WEAPON_KNIFE_SURVIVAL_BOWIE, item_t("Bowie","weapon_knife_survival_bowie", "models/weapons/v_knife_survival_bowie.mdl","knife_survival_bowie","", "")),
         std::make_pair(WEAPON_KNIFE_BUTTERFLY, item_t("Butterfly", "weapon_knife_butterfly", "models/weapons/v_knife_butterfly.mdl", "knife_butterfly", "", "")),
         std::make_pair(WEAPON_KNIFE_PUSH, item_t("Shadow Daggers", "weapon_knife_push", "models/weapons/v_knife_push.mdl", "knife_push", "", "")),
         // new knives
         std::make_pair(WEAPON_KNIFE_URSUS, item_t("Ursus", "weapon_knife_ursus", "models/weapons/v_knife_ursus.mdl", "knife_ursus")),
         std::make_pair(WEAPON_KNIFE_GYPSY_JACKKNIFE, item_t("Navaja", "weapon_knife_gypsy_jackknife", "models/weapons/v_knife_gypsy_jackknife.mdl", "knife_gypsy_jackknife", "", "")),
         std::make_pair(WEAPON_KNIFE_STILETTO, item_t("Stiletto", "weapon_knife_stiletto", "models/weapons/v_knife_stiletto.mdl", "knife_stiletto", "", "")),
         std::make_pair(WEAPON_KNIFE_WIDOWMAKER, item_t("Talon", "weapon_knife_widowmaker", "models/weapons/v_knife_widowmaker.mdl", "knife_widowmaker", "", "")),
         // gloves
         std::make_pair(GLOVE_STUDDED_BLOODHOUND, item_t("Bloodhound Gloves", "studded_bloodhound_gloves", "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl", "bloodhound", "", "")),
         std::make_pair(GLOVE_T_SIDE, item_t("Terrorists Gloves", "glove_t", "", "default_ct", "", "")),
         std::make_pair(GLOVE_CT_SIDE, item_t("Counter-Terrorists Gloves", "glove_ct", "", "default_t", "", "")),
         std::make_pair(GLOVE_SPORTY, item_t("Sporty Gloves", "sporty_gloves", "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl", "sport", "", "")),
         std::make_pair(GLOVE_SLICK, item_t("Driver Gloves", "slick_gloves", "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl", "driver", "", "")),
         std::make_pair(GLOVE_LEATHER_WRAP, item_t("Hand Wraps", "leather_handwraps", "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl", "handwrap", "", "")),
         std::make_pair(GLOVE_MOTORCYCLE, item_t("Motocycle Gloves", "motorcycle_gloves", "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl", "motocycle", "", "")),
         std::make_pair(GLOVE_SPECIALIST, item_t("Specialist Gloves", "specialist_gloves", "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl", "specialist", "", "")),
         std::make_pair(GLOVE_HYDRA, item_t("Hydra Gloves", "studded_hydra_gloves", "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl", "hydra", "", "")),
         // grenades
         std::make_pair(WEAPON_FLASHBANG, item_t("Flashbang", "weapon_flashbang", "models/weapons/v_eq_flashbang.mdl", "flashbang", "", "")),
         std::make_pair(WEAPON_HEGRENADE, item_t("HE Grenade", "weapon_hegrenade", "models/weapons/v_eq_fraggrenade.mdl", "hegrenade", "", "")),
         std::make_pair(WEAPON_SMOKEGRENADE, item_t("Smoke Grenade", "weapon_smokegrenade", "models/weapons/v_eq_smokegrenade.mdl", "smokegrenade", "", "")),
         std::make_pair(WEAPON_MOLOTOV, item_t("Molotov", "weapon_molotov", "models/weapons/v_eq_molotov.mdl", "inferno", "", "")),
         std::make_pair(WEAPON_DECOY, item_t("Decoy Grenade", "weapon_decoy", "models/weapons/v_eq_decoy.mdl", "decoy", "", "")),
         std::make_pair(WEAPON_INCGRENADE, item_t("Incendiary Grenade", "weapon_incgrenade", "models/weapons/v_eq_incendiarygrenade.mdl", "inferno", "", "")),
         std::make_pair(WEAPON_C4, item_t("C4 Explosive", "weapon_c4", "models/weapons/v_ied.mdl", "", "")),
         */
    };

    _done = true;
}

void init_g_item_def_index_map2()
{
    static bool _done = false;
    
    if(_done)
        return;
    
    g_item_def_index_map.insert(std::make_pair(WEAPON_MAG7, item_t("MAG-7", "weapon_mag7", "models/weapons/v_shot_mag7.mdl", "mag7", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_NEGEV, item_t("Negev", "weapon_negev", "models/weapons/v_mach_negev.mdl", "negev", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_SAWEDOFF, item_t("Sawed-Off", "weapon_sawedoff", "models/weapons/v_shot_sawedoff.mdl", "sawedoff", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_TEC9, item_t("Tec-9", "weapon_tec9", "models/weapons/v_pist_tec9.mdl", "tec9", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_TASER, item_t("Zeus x27", "weapon_taser", "models/weapons/v_eq_taser.mdl", "taser", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_HKP2000, item_t("P2000", "weapon_hkp2000", "models/weapons/v_pist_hkp2000.mdl", "hkp2000", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_MP7, item_t("MP7", "weapon_mp7", "models/weapons/v_smg_mp7.mdl", "mp7", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_MP9, item_t("MP9", "weapon_mp9", "models/weapons/v_smg_mp9.mdl", "mp9", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_NOVA, item_t("Nova", "weapon_nova", "models/weapons/v_shot_nova.mdl", "nova", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_P250, item_t("P250", "weapon_p250", "models/weapons/v_pist_p250.mdl", "p250", "", "")));
    
    g_item_def_index_map.insert(std::make_pair(WEAPON_SCAR20, item_t("SCAR-20", "weapon_scar20", "models/weapons/v_snip_scar20.mdl", "scar20", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_SG556, item_t("SG 556", "weapon_sg556", "models/weapons/v_rif_sg556.mdl", "sg556", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_SSG08, item_t("SSG 08", "weapon_ssg08", "models/weapons/v_snip_ssg08.mdl", "ssg08", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE, item_t("Counter-Terrorists Knife", "weapon_knife", "models/weapons/v_knife_default_ct.mdl", "knife_default_ct", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_T, item_t("Terrorists Knife", "weapon_knife_t", "models/weapons/v_knife_default_t.mdl", "knife_t", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_M4A1_SILENCER, item_t("M4A1-S", "weapon_m4a1_silencer", "models/weapons/v_rif_m4a1_s.mdl", "m4a1_silencer", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_USP_SILENCER, item_t("USP-S", "weapon_usp_silencer", "models/weapons/v_pist_223.mdl", "usp_silencer", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_CZ75A, item_t("CZ75 Auto", "weapon_cz75a", "models/weapons/v_pist_cz_75.mdl", "cz75a", "", "")));
    g_item_def_index_map.insert(std::make_pair(WEAPON_REVOLVER, item_t("R8 Revolver", "weapon_revolver", "models/weapons/v_pist_revolver.mdl", "revolver", "", "")));
    
    _done = true;
}

void skinchanger_t::init()
{
    g_item_def_index_map;
    
    g_config.init_skin_file();
    
    _init = true;
}

void skinchanger_t::run()
{
    if(!set.skins.enabled)
        return;
    
    if(!_init)
        init();
    
    if(!_init)
        return;
    
    if(!global::local || !global::local->is_alive())
        return;
    
    apply();
}

void skinchanger_t::update()
{
    g_config.save_skins();
}

void skinchanger_t::apply()
{
    weapon_t* weapon = global::local->get_weapon();
    
    if(!weapon)
        return;
    
    int* my_weapons = global::local->get_my_weapons();
    
    if(!my_weapons)
        return;
    
    player_info_t info = util_get_player_info(global::local);
    
    for(int i = 0; my_weapons[i]; i++)
    {
        base_attributable_item_t* item = (base_attributable_item_t*)g_ent_list->get_entity_from_handle(my_weapons[i]);
        
        if(!item)
            continue;
        
        short item_def_index = item->get_item_definition_index();
        
        if(!item_def_index)
            continue;
        
        skin_config_t config = g_config.get_skin_config(item_def_index);
        
        if(config.item_definition_index == -1)
            continue;
        
        try
        {
            *weapon->get_model_index() = g_model_info->get_model_index(g_item_def_index_map.at(config.item_definition_index).model);
        }
        catch(std::exception& e)
        {
            
        }
        
        
        // if its a knife then change the model
        if(item_def_index == WEAPON_KNIFE || item_def_index == WEAPON_KNIFE_T)
            *item->get_item_definition_index_pointer() = config.item_definition_index;
        
        *weapon->get_item_id_high() = -1;
        *weapon->get_account_id()   = info.xuidlow;
        
        if(config.fallback_paint_kit)
            *weapon->get_fallback_paint_kit()   = config.fallback_paint_kit;
        
        if(config.fallback_seed)
            *weapon->get_fallback_seed()        = config.fallback_seed;
        
        if(config.fallback_wear)
            *weapon->get_fallback_wear()        = config.fallback_wear;
        
        if(config.fallback_stattrak)
            *weapon->get_fallback_stattrack()   = config.fallback_stattrak; // -1; // -1 is no stattrack
    }
    
    base_view_model_t* view_model = (base_view_model_t*)global::local->get_view_model();
    
    if(!view_model)
        return;
    
    base_handle_t view_model_handle = view_model->get_weapon();
    
    if(view_model_handle == INVALID_EHANDLE_INDEX)
        return;
    
    base_attributable_item_t* view_model_weapon = (base_attributable_item_t*)g_ent_list->get_entity_from_handle(view_model_handle);
    
    if(!view_model_weapon)
        return;
    
    try
    {
        if(g_item_def_index_map.find(view_model_weapon->get_item_definition_index()) != g_item_def_index_map.end())
        {
            const item_t& override_weapon = g_item_def_index_map.at(view_model_weapon->get_item_definition_index());
            *view_model->get_model_index() = g_model_info->get_model_index(override_weapon.model);
        }
    }
    catch(std::exception& e)
    {
        
    }
}

std::vector<skinchanger_weapon_t> skinchanger_t::weapons = {
    
};

std::vector<skinchanger_weapon_t> skinchanger_t::knives = {
    
};


