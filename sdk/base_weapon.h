/*
 * base_weapon.h
 */
#pragma once

class base_weapon_t : public base_entity_t
{
public:
    
    weapon_info_t* get_weapon_info()
    {
        // todo
        return nullptr;
    }
    
};

typedef base_weapon_t weapon_t;
