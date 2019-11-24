/*
 *  base_attributable_item.h
 */
#pragma once

class base_attributable_item_t : public base_entity_t
{
public:
    
    short* get_item_definition_index_pointer()
    {
        return sdk_get_pointer(short, base_attributable_item, m_item_definition_index);
    }
    
    short get_item_definition_index()
    {
        return *get_item_definition_index_pointer();
    }
    
    int* get_account_id()
    {
        return sdk_get_pointer(int, base_attributable_item, m_account_id);
    }
    
    int* get_item_id_low()
    {
        return sdk_get_pointer(int, base_attributable_item, m_item_id_low);
    }
    
    int* get_item_id_high()
    {
        return sdk_get_pointer(int, base_attributable_item, m_item_id_high);
    }
    
    int* get_entity_quality()
    {
        return sdk_get_pointer(int, base_attributable_item, m_entity_quality);
    }
    
    char* get_custom_name()
    {
        return sdk_get_pointer(char, base_attributable_item, m_custom_name);
    }
    
    int* get_fallback_paint_kit()
    {
        return sdk_get_pointer(int, base_attributable_item, m_fallback_paint_kit);
    }
    
    int* get_fallback_seed()
    {
        return sdk_get_pointer(int, base_attributable_item, m_fallback_seed);
    }
    
    float* get_fallback_wear()
    {
        return sdk_get_pointer(float, base_attributable_item, m_fallback_wear);
    }
    
    int* get_fallback_stattrack()
    {
        return sdk_get_pointer(int, base_attributable_item, m_fallback_stattrack);
    }
    
    uintptr_t m_account_id;
    uintptr_t m_item_id_high;
    uintptr_t m_item_id_low;
    uintptr_t m_entity_quality;
    uintptr_t m_custom_name;
    uintptr_t m_fallback_paint_kit;
    uintptr_t m_fallback_seed;
    uintptr_t m_fallback_wear;
    uintptr_t m_fallback_stattrack;
    
    bool is_knife()
    {
        switch (get_item_definition_index())
        {
            case WEAPON_KNIFE:
            case WEAPON_KNIFE_T:
            case WEAPON_KNIFE_GUT:
            case WEAPON_KNIFE_FLIP:
            case WEAPON_KNIFE_BAYONET:
            case WEAPON_KNIFE_M9_BAYONET:
            case WEAPON_KNIFE_KARAMBIT:
            case WEAPON_KNIFE_TACTICAL:
            case WEAPON_KNIFE_BUTTERFLY:
            case WEAPON_KNIFE_SURVIVAL_BOWIE:
            case WEAPON_KNIFE_FALCHION:
            case WEAPON_KNIFE_PUSH:
                return true;
            default:
                return false;
        }
    }
    
    bool is_grenade()
    {
        switch (get_item_definition_index())
        {
            case WEAPON_SMOKEGRENADE:
            case WEAPON_HEGRENADE:
            case WEAPON_INCGRENADE:
            case WEAPON_FLASHBANG:
            case WEAPON_MOLOTOV:
            case WEAPON_DECOY:
                return true;
            default:
                return false;
        }
    }
    
    bool is_bomb()
    {
        return get_item_definition_index() == WEAPON_C4;
    }
    
};

typedef base_attributable_item_t attributable_item_t;
