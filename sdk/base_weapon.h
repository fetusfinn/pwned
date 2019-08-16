/*
 * base_weapon.h
 */
#pragma once

// C_BaseCombatWeapon
class base_weapon_t : public base_attributable_item_t
{
public:
    
    int get_ammo()
    {
        return sdk_get_offset(int, base_combat_weapon, m_clip1);
    }
    
    weapon_info_t* get_weapon_info()
    {
        return nullptr;
        // todo : get the right index
        typedef weapon_info_t*(*o_get_weapon_info)(void*);
        return getvfunc<o_get_weapon_info>(this, 522)(this);
    }    
};

typedef base_weapon_t weapon_t;
