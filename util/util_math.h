/*
 *  util_math.h
 */
#pragma once

bool world_to_screen(vec3_t& in, vec3_t& out);
player_box_t get_player_box(base_entity_t* entity);



template<class T>
T util_clamp(T in, T min, T max)
{
    if(in < min)
        return min;
    if(in > max)
        return max;
    return in;
}
