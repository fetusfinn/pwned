/*
 *  skinchanger.h
 */
#pragma once

#include <unordered_map>

void init_g_item_def_index_map1();
void init_g_item_def_index_map2();

extern std::unordered_map<int, item_t> g_item_def_index_map;



struct skinchanger_weapon_t
{
    std::string m_name;
    int         m_id;
};

class skinchanger_t
{
private:
    
    bool _init = false;
    
private:
    
    void apply();
    
public:
    
    void init();
    void run();
    void update();

public:
    
    static std::vector<skinchanger_weapon_t> weapons, knives;
    
};

extern skinchanger_t g_skins;

/*
 g_item_def_index_map.insert(std::make_pair(WEAPON_NONE, item_t("All", "weapon_all", "", "all", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_DEAGLE, item_t("Desert Eagle", "weapon_deagle", "models/weapons/v_pist_deagle.mdl", "deagle", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_ELITE, item_t("Dual Berettas", "weapon_elite", "models/weapons/v_pist_elite.mdl", "elite", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_FIVESEVEN, item_t("Five-Seven", "weapon_fiveseven", "models/weapons/v_pist_fiveseven.mdl", "fiveseven", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_GLOCK, item_t("Glock-18", "weapon_glock", "models/weapons/v_pist_glock18.mdl", "glock", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_AK47, item_t("AK-47", "weapon_ak47", "models/weapons/v_rif_ak47.mdl", "ak47", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_AUG, item_t("AUG", "weapon_aug", "models/weapons/v_rif_aug.mdl", "aug", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_AWP, item_t("AWP", "weapon_awp", "models/weapons/v_snip_awp.mdl", "awp", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_FAMAS, item_t("FAMAS", "weapon_famas", "models/weapons/v_rif_famas.mdl", "famas", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_G3SG1, item_t("G3SG1", "weapon_g3sg1", "models/weapons/v_snip_g3sg1.mdl", "g3sg1", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_GALILAR, item_t("Galil AR", "weapon_galilar", "models/weapons/v_rif_galilar.mdl", "galilar", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_M249, item_t("M249", "weapon_m249", "models/weapons/v_mach_m249para.mdl", "m249", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_M4A1, item_t("M4A4", "weapon_m4a1", "models/weapons/v_rif_m4a1.mdl", "m4a1", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_MAC10, item_t("MAC-10", "weapon_mac10", "models/weapons/v_smg_mac10.mdl", "mac10", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_P90, item_t("P90", "weapon_p90", "models/weapons/v_smg_p90.mdl", "p90", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_MP5, item_t("MP5 SD", "weapon_mp5sd", "models/weapons/v_smg_mp5sd.mdl", "mp5sd", "models/weapons/w_smg_mp5sd.mdl", "models/weapons/w_smg_mp5sd_dropped.mdl")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_UMP45, item_t("UMP-45", "weapon_ump45", "models/weapons/v_smg_ump45.mdl", "ump45", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_XM1014, item_t("XM1014", "weapon_xm1014", "models/weapons/v_shot_xm1014.mdl", "xm1014", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_BIZON, item_t("PP-Bizon", "weapon_bizon", "models/weapons/v_smg_bizon.mdl", "bizon", "", "")));
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
 g_item_def_index_map.insert(std::make_pair(WEAPON_FLASHBANG, item_t("Flashbang", "weapon_flashbang", "models/weapons/v_eq_flashbang.mdl", "flashbang", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_HEGRENADE, item_t("HE Grenade", "weapon_hegrenade", "models/weapons/v_eq_fraggrenade.mdl", "hegrenade", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_SMOKEGRENADE, item_t("Smoke Grenade", "weapon_smokegrenade", "models/weapons/v_eq_smokegrenade.mdl", "smokegrenade", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_MOLOTOV, item_t("Molotov", "weapon_molotov", "models/weapons/v_eq_molotov.mdl", "inferno", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_DECOY, item_t("Decoy Grenade", "weapon_decoy", "models/weapons/v_eq_decoy.mdl", "decoy", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_INCGRENADE, item_t("Incendiary Grenade", "weapon_incgrenade", "models/weapons/v_eq_incendiarygrenade.mdl", "inferno", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_C4, item_t("C4 Explosive", "weapon_c4", "models/weapons/v_ied.mdl", "", "")));
 
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_T, item_t("Terrorists Knife", "weapon_knife_t", "models/weapons/v_knife_default_t.mdl", "knife_t", "", "")));
 
 g_item_def_index_map.insert(std::make_pair(WEAPON_M4A1_SILENCER, item_t("M4A1-S", "weapon_m4a1_silencer", "models/weapons/v_rif_m4a1_s.mdl", "m4a1_silencer", "", "")));
 //
 g_item_def_index_map.insert(std::make_pair(WEAPON_USP_SILENCER, item_t("USP-S", "weapon_usp_silencer", "models/weapons/v_pist_223.mdl", "usp_silencer", "", "")));
 //
 g_item_def_index_map.insert(std::make_pair(WEAPON_CZ75A, item_t("CZ75 Auto", "weapon_cz75a", "models/weapons/v_pist_cz_75.mdl", "cz75a", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_REVOLVER, item_t("R8 Revolver", "weapon_revolver", "models/weapons/v_pist_revolver.mdl", "revolver", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_BAYONET, item_t("Bayonet", "weapon_bayonet", "models/weapons/v_knife_bayonet.mdl", "bayonet", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_FLIP, item_t("Flip", "weapon_knife_flip", "models/weapons/v_knife_flip.mdl", "knife_flip", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_GUT, item_t("Gut", "weapon_knife_gut", "models/weapons/v_knife_gut.mdl", "knife_gut", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_KARAMBIT, item_t("Karambit", "weapon_knife_karambit", "models/weapons/v_knife_karam.mdl", "knife_karambit", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_M9_BAYONET, item_t("M9 Bayonet", "weapon_knife_m9_bayonet", "models/weapons/v_knife_m9_bay.mdl", "knife_m9_bayonet", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_TACTICAL, item_t("Huntsman", "weapon_knife_tactical", "models/weapons/v_knife_tactical.mdl", "knife_tactical", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_FALCHION, item_t("Falchion", "weapon_knife_falchion", "models/weapons/v_knife_falchion_advanced.mdl", "knife_falchion", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_SURVIVAL_BOWIE, item_t("Bowie","weapon_knife_survival_bowie", "models/weapons/v_knife_survival_bowie.mdl","knife_survival_bowie","", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_BUTTERFLY, item_t("Butterfly", "weapon_knife_butterfly", "models/weapons/v_knife_butterfly.mdl", "knife_butterfly", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_PUSH, item_t("Shadow Daggers", "weapon_knife_push", "models/weapons/v_knife_push.mdl", "knife_push", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_URSUS, item_t("Ursus", "weapon_knife_ursus", "models/weapons/v_knife_ursus.mdl", "knife_ursus")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_GYPSY_JACKKNIFE, item_t("Navaja", "weapon_knife_gypsy_jackknife", "models/weapons/v_knife_gypsy_jackknife.mdl", "knife_gypsy_jackknife", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_STILETTO, item_t("Stiletto", "weapon_knife_stiletto", "models/weapons/v_knife_stiletto.mdl", "knife_stiletto", "", "")));
 g_item_def_index_map.insert(std::make_pair(WEAPON_KNIFE_WIDOWMAKER, item_t("Talon", "weapon_knife_widowmaker", "models/weapons/v_knife_widowmaker.mdl", "knife_widowmaker", "", "")));
 g_item_def_index_map.insert(std::make_pair(GLOVE_STUDDED_BLOODHOUND, item_t("Bloodhound Gloves", "studded_bloodhound_gloves", "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl", "bloodhound", "", "")));
 g_item_def_index_map.insert(std::make_pair(GLOVE_T_SIDE, item_t("Terrorists Gloves", "glove_t", "", "default_ct", "", "")));
 g_item_def_index_map.insert(std::make_pair(GLOVE_CT_SIDE, item_t("Counter-Terrorists Gloves", "glove_ct", "", "default_t", "", "")));
 g_item_def_index_map.insert(std::make_pair(GLOVE_SPORTY, item_t("Sporty Gloves", "sporty_gloves", "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl", "sport", "", "")));
 g_item_def_index_map.insert(std::make_pair(GLOVE_SLICK, item_t("Driver Gloves", "slick_gloves", "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl", "driver", "", "")));
 g_item_def_index_map.insert(std::make_pair(GLOVE_LEATHER_WRAP, item_t("Hand Wraps", "leather_handwraps", "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl", "handwrap", "", "")));
 g_item_def_index_map.insert(std::make_pair(GLOVE_MOTORCYCLE, item_t("Motocycle Gloves", "motorcycle_gloves", "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl", "motocycle", "", "")));
 g_item_def_index_map.insert(std::make_pair(GLOVE_SPECIALIST, item_t("Specialist Gloves", "specialist_gloves", "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl", "specialist", "", "")));
 g_item_def_index_map.insert(std::make_pair(GLOVE_HYDRA, item_t("Hydra Gloves", "studded_hydra_gloves", "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl", "hydra", "", "")));
 */
